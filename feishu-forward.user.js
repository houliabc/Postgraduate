// ==UserScript==
// @name         飞书消息转发 - 安妮群 → 测试群
// @namespace    https://github.com/feishu-forward
// @version      2.5.0
// @description  监控飞书「安妮」群聊的新消息，自动转发到「测试群」，支持去重、时间窗口、多段排版
// @author       Custom
// @match        https://*.feishu.cn/next/messenger*
// @icon         https://www.feishu.cn/favicon.ico
// @grant        GM_xmlhttpRequest
// @grant        GM_setValue
// @grant        GM_getValue
// @grant        GM_addStyle
// @connect      open.feishu.cn
// ==/UserScript==

(function () {
  'use strict';

  // ============================================================
  //  🔧 配置区 —— Ctrl+F 搜 "TODO" 定位所有可修改项
  // ============================================================
  const CONFIG = {
    // TODO: 修改 — 测试群的飞书自定义机器人 Webhook 地址（必填）
    // 获取方式：测试群 → 设置 → 群机器人 → 添加机器人 → 自定义机器人 → 复制 Webhook 地址
    webhookUrl: 'https://open.feishu.cn/open-apis/bot/v2/hook/c485de46-874c-4750-a5df-eb5de71dc735',

    // TODO: 修改 — 源群聊名称（要监听的群）
    sourceChat: '安妮',

    // TODO: 修改 — 目标群聊名称（转发到的群）
    targetChat: '测试群',

    // ---- 时间窗口 ----
    // TODO: 修改 — 只转发最近 N 分钟内的消息，超过的直接跳过
    // 设为 0 则不做时间限制（不推荐）
    maxMessageAgeMinutes: 5,

    // ---- 转发模式 ----
    // TODO: 修改 — 转发模式：
    //   'all'        — 转发所有人的发言（排除 skipSenders）
    //   'sender'     — 只转发 senderFilter 列表里的人
    //   'only_annie' — 只转发「安妮」本人的话（排除她转贴的提问）
    forwardMode: 'all',

    // TODO: 修改 — forwardMode='sender' 时生效，只转发这些发送者
    senderFilter: ['飞书机器人助手', '自定义机器人','用户925690'],

    // TODO: 修改 — 跳过这些发送者的消息（不转发）
    skipSenders: ['账号安全中心', '管理员小助手', '审批'],

    // TODO: 修改 — 是否跳过含有 "问:" 前缀的转发提问
    skipForwardedQuestions: false,

    // ---- 其他 ----
    // TODO: 修改 — 轮询间隔（毫秒），建议 3000~15000
    pollInterval: 10000,
    // TODO: 修改 — 控制台调试日志，不需要时改 false
    debug: true,
    // TODO: 修改 — 去重记录最多保存多少条
    maxSeenIds: 800,

    // ---- 图片转发 ----
    // TODO: 修改 — 是否转发图片
    enableImageForwarding: true,
    // TODO: 修改 — 图片转发模式：
    //   'auto'           — 优先 post 富文本（图文合并），失败回退到分开发送，最后回退到纯文字
    //   'post'           — 强制用 post 富文本合并图文（一条消息）
    //   'separate'       — 文字和图片分开发送（文字一条，每张图片各一条）
    //   'text_fallback'  — 不转发图片，仅在文字中用 [图片] 占位
    imageForwardMode: 'auto',
    // TODO: 修改 — 连续发送多条 webhook 消息的间隔（毫秒），防止被限流（飞书约 100次/分钟）
    imageSendDelay: 800,
  };

  // ============================================================
  //  📦 去重模块
  // ============================================================
  const SEEN_KEY = 'feishu_fwd_seen_v3';

  function getSeenIds() {
    try {
      const raw = GM_getValue(SEEN_KEY, '[]');
      return new Set(JSON.parse(raw));
    } catch (e) {
      return new Set();
    }
  }

  function saveSeenIds(seenSet) {
    const arr = [...seenSet].slice(-CONFIG.maxSeenIds);
    GM_setValue(SEEN_KEY, JSON.stringify(arr));
  }

  function addSeenId(id) {
    const seen = getSeenIds();
    seen.add(id);
    saveSeenIds(seen);
  }

  // ============================================================
  //  🕐 时间解析
  // ============================================================

  /** 把消息的 .message-timestamp 文本转成 Date 对象 */
  function parseMessageTime(timeText) {
    if (!timeText) return null;

    const now = new Date();

    // "HH:MM"  — 今天的消息
    const hhmm = timeText.match(/^(\d{1,2}):(\d{2})$/);
    if (hhmm) {
      const hours = parseInt(hhmm[1], 10);
      const minutes = parseInt(hhmm[2], 10);
      const t = new Date(now.getFullYear(), now.getMonth(), now.getDate(), hours, minutes);
      // 如果解析出的时间比现在晚（如 23:00 在凌晨 01:00 解析），回退一天
      if (t > now) t.setDate(t.getDate() - 1);
      return t;
    }

    // 含中文日期的（如 "7月27日"）——肯定超过时间窗口
    if (/[月日]/.test(timeText)) {
      return new Date(0); // epoch，久远过去
    }

    return null; // 无法解析
  }

  /** 判断消息时间是否在允许窗口内 */
  function isWithinTimeWindow(msgTime) {
    if (CONFIG.maxMessageAgeMinutes <= 0) return true;   // 0 = 不做限制
    if (!msgTime) return false;                           // 无法解析 → 保守跳过
    const diffMs = Date.now() - msgTime.getTime();
    return diffMs <= CONFIG.maxMessageAgeMinutes * 60 * 1000;
  }

  // ============================================================
  //  🔍 消息提取模块
  // ============================================================
  function getCurrentChatName() {
    // 尝试多种选择器（飞书 UI 中 CSS Module 哈希类名会随版本变化）
    const selectors = [
      '.feed-item.active [class*="name"]',        // 活跃群聊中的名称元素
      '.feed-item.active [class*="title"]',       // 备选
      '[class*="chatName"]',                       // 聊天名称
      '[class*="conversationName"]',               // 另一个可能的类名
      '[class*="chat_title"]',                     // 聊天标题
    ];
    for (const sel of selectors) {
      const el = document.querySelector(sel);
      if (el) {
        const text = el.textContent.trim();
        if (text && text.length > 0 && text.length < 50) return text;
      }
    }

    // 最后兜底：在消息面板区域查找匹配的群聊名
    const panel = document.querySelector('.messagesLayout') || document.querySelector('[class*="main"]');
    if (panel) {
      const allEls = panel.querySelectorAll('*');
      for (const el of allEls) {
        const text = el.textContent.trim();
        if ((text === CONFIG.sourceChat || text === CONFIG.targetChat) && el.children.length === 0) {
          return text;
        }
      }
    }
    return null;
  }

  function extractMessage(msgEl) {
    const id = msgEl.getAttribute('data-id') || '';

    // 发送者
    const nameEl = msgEl.querySelector('.message-info-name');
    const sender = nameEl ? nameEl.textContent.trim() : '';

    // 显示时间（如 "22:35"、"7月27日"）
    const timeEl = msgEl.querySelector('.message-timestamp');
    const displayTime = timeEl ? timeEl.textContent.trim() : '';

    // --- 按段落提取内容 ---
    // 飞书每条消息中，.rich-text-paragraph 代表一个自然段
    const paragraphEls = msgEl.querySelectorAll('.rich-text-paragraph');
    const paragraphs = [];
    paragraphEls.forEach(function (p) {
      const text = p.textContent.trim();
      if (text) paragraphs.push(text);
    });

    // 兜底：如果没有 .rich-text-paragraph，回退到扁平拼接
    if (paragraphs.length === 0) {
      const textSpans = msgEl.querySelectorAll('.text-only');
      let flat = '';
      textSpans.forEach(function (s) {
        flat += s.textContent;
      });
      const trimmed = flat.trim();
      if (trimmed) paragraphs.push(trimmed);
    }

    // 先提取图片（纯图片消息没有文字，正文为空是正常的）
    var images = extractImages(msgEl);

    // 兜底2：飞书改版后上面两种选择器可能都抓不到，
    // 拿消息内容容器整体文本兜底，剔除发送者名/时间戳/头像等噪声
    if (paragraphs.length === 0) {
      var bodyEl = msgEl.querySelector('[class*="body"]') || msgEl;
      var clone = bodyEl.cloneNode(true);
      clone.querySelectorAll(
        '.message-info-name, .message-timestamp, .message-avatar, [class*="reaction"], [class*="sticker"], [class*="toolbar"]'
      ).forEach(function (n) { n.remove(); });
      var t = clone.textContent.trim();
      if (t) {
        paragraphs.push(t);
        log('🆘 内容走兜底2，抓到:', t.substring(0, 60));
      } else if (images.length > 0) {
        log('📷 纯图片消息（无正文文字），图片已提取 ' + images.length + ' 张');
      } else {
        log('⚠️ 内容与图片都提取失败，msgEl 原始文本:', msgEl.textContent.trim().substring(0, 120));
      }
    }

    const content = paragraphs.join('\n');
    const msgTime = parseMessageTime(displayTime);
    const isForwardedQuestion =
      content.includes('问:') || paragraphs.some(function (p) { return p.trim() === '问:'; });
    // fingerprint 纳入图片信息，防止纯图片消息去重遗漏
    var imgFp = images.length > 0 ? '|IMG:' + images.map(function (im) { return im.imageKey; }).join(',') : '';
    const fingerprint = sender + '|' + displayTime + '|' + content.substring(0, 200) + imgFp;

    return {
      id: id,
      sender: sender,
      displayTime: displayTime,
      content: content,
      paragraphs: paragraphs,
      msgTime: msgTime,
      fingerprint: fingerprint,
      isForwardedQuestion: isForwardedQuestion,
      images: images,
      hasImages: images.length > 0,
    };
  }

  function shouldForward(msg) {
    if (!msg.content && !msg.hasImages) {
      log('🚫 跳过：内容为空且无图片 (sender="' + msg.sender + '", time="' + msg.displayTime + '")');
      return false;
    }

    // 跳过机器人
    var hitSkip = CONFIG.skipSenders.find(function (s) { return msg.sender === s || msg.sender.includes(s); });
    if (hitSkip) {
      log('🚫 跳过：sender 命中 skipSenders["' + hitSkip + '"]');
      return false;
    }

    // 跳过转发提问
    if (CONFIG.skipForwardedQuestions && msg.isForwardedQuestion) {
      log('⏭ 跳过转发提问:', msg.content.substring(0, 40));
      return false;
    }

    // 按模式过滤
    if (CONFIG.forwardMode === 'only_annie') {
      if (msg.sender !== '安妮') { log('🚫 跳过：only_annie 模式，sender!="安妮"'); return false; }
      if (msg.content.startsWith('问:')) { log('🚫 跳过：only_annie 模式，内容以"问:"开头'); return false; }
    } else if (CONFIG.forwardMode === 'sender') {
      if (!CONFIG.senderFilter.includes(msg.sender)) {
        log('🚫 跳过：sender 模式，sender="' + msg.sender + '" 不在 senderFilter 中');
        return false;
      }
    }

    return true;
  }

  // ============================================================
  //  📤 Webhook 发送模块
  // ============================================================
  // ============================================================
  //  📤 Webhook 发送模块（新版：支持文字 + 图片）
  // ============================================================

  /** 去掉 image_key 的尺寸后缀（_MIDDLE, _ORIGINAL, _LARGE 等） */
  function stripImageKeySuffix(imageKey) {
    return imageKey.replace(/_(ORIGINAL|LARGE|MIDDLE|SMALL|THUMBNAIL)$/i, '');
  }

  /** 从消息 DOM 提取内容图片（非头像、非表情） */
  function extractImages(msgEl) {
    var images = [];
    // 多级选择器回退（飞书 CSS Module 类名可能变化）
    var selectors = [
      '.messenger-image__img--white-bg[data-image-key]',
      '.base-image__content[data-image-key]',
      'img[data-image-key]',
    ];

    for (var s = 0; s < selectors.length; s++) {
      var imgEls = msgEl.querySelectorAll(selectors[s]);
      for (var i = 0; i < imgEls.length; i++) {
        var img = imgEls[i];
        // 排除头像
        if (img.closest('.message-avatar')) continue;
        // 排除表情/sticker
        var src = img.getAttribute('src') || '';
        if (src.indexOf('sf1-scmcdn-cn.feishucdn.com/obj/feishu-static') !== -1) continue;

        var rawKey = img.getAttribute('data-image-key');
        if (!rawKey) continue;

        var stripped = stripImageKeySuffix(rawKey);
        // 同一条消息里的同一张图片去重
        if (images.some(function (item) { return item.imageKey === stripped; })) continue;

        images.push({
          imageKey: stripped,
          rawKey: rawKey,
          width: parseInt(img.getAttribute('data-lark-image-width'), 10) || 0,
          height: parseInt(img.getAttribute('data-lark-image-height'), 10) || 0,
        });
      }
      if (images.length > 0) break; // 找到就不再回退
    }

    return images;
  }

  /** 发送纯文本到 webhook */
  function sendTextViaWebhook(text) {
    if (!CONFIG.webhookUrl || CONFIG.webhookUrl.includes('YOUR-WEBHOOK-TOKEN')) {
      return Promise.reject(new Error('Webhook not configured'));
    }
    return new Promise(function (resolve, reject) {
      GM_xmlhttpRequest({
        method: 'POST',
        url: CONFIG.webhookUrl,
        headers: { 'Content-Type': 'application/json' },
        data: JSON.stringify({
          msg_type: 'text',
          content: { text: text },
        }),
        timeout: 15000,
        onload: function (res) {
          try {
            var body = JSON.parse(res.responseText);
            if (body.StatusCode === 0 || body.code === 0 || body.msg === 'ok' || body.StatusMessage === 'ok') {
              resolve(body);
            } else {
              reject(new Error(JSON.stringify(body)));
            }
          } catch (e) {
            reject(new Error('Parse: ' + res.responseText));
          }
        },
        onerror: function () { reject(new Error('Network error')); },
        ontimeout: function () { reject(new Error('Timeout')); },
      });
    });
  }

  /** 发送单张图片到 webhook */
  function sendImageViaWebhook(imageKey) {
    return new Promise(function (resolve, reject) {
      GM_xmlhttpRequest({
        method: 'POST',
        url: CONFIG.webhookUrl,
        headers: { 'Content-Type': 'application/json' },
        data: JSON.stringify({
          msg_type: 'image',
          content: { image_key: imageKey },
        }),
        timeout: 15000,
        onload: function (res) {
          try {
            var body = JSON.parse(res.responseText);
            if (body.StatusCode === 0 || body.code === 0 || body.msg === 'ok' || body.StatusMessage === 'ok') {
              resolve(body);
            } else {
              // 识别 image_key 无效错误
              var code = body.StatusCode || body.code;
              if (code === 99991663 || (body.msg && body.msg.indexOf('image_key') !== -1)) {
                reject(new Error('IMAGE_KEY_INVALID: ' + imageKey.substring(0, 40)));
              } else {
                reject(new Error(JSON.stringify(body)));
              }
            }
          } catch (e) {
            reject(new Error('Parse: ' + res.responseText));
          }
        },
        onerror: function () { reject(new Error('Network error')); },
        ontimeout: function () { reject(new Error('Timeout')); },
      });
    });
  }

  /** 发送 post 富文本（图文合并一条消息） */
  function sendPostViaWebhook(msg) {
    var title = msg.sender + '  ' + msg.displayTime;
    var content = [];

    // 每个文本段落占一个 content block（一对 []）
    for (var i = 0; i < msg.paragraphs.length; i++) {
      var p = msg.paragraphs[i].trim();
      if (p) {
        content.push([{ tag: 'text', text: p }]);
      }
    }

    // 每张图片独占一个 content block（img 不能与 text 同行）
    for (var j = 0; j < msg.images.length; j++) {
      content.push([{ tag: 'img', image_key: msg.images[j].imageKey }]);
    }

    var postContent = {
      zh_cn: { title: title, content: content },
    };

    return new Promise(function (resolve, reject) {
      GM_xmlhttpRequest({
        method: 'POST',
        url: CONFIG.webhookUrl,
        headers: { 'Content-Type': 'application/json' },
        data: JSON.stringify({
          msg_type: 'post',
          content: { post: postContent },
        }),
        timeout: 15000,
        onload: function (res) {
          try {
            var body = JSON.parse(res.responseText);
            if (body.StatusCode === 0 || body.code === 0 || body.msg === 'ok' || body.StatusMessage === 'ok') {
              resolve(body);
            } else {
              reject(new Error(JSON.stringify(body)));
            }
          } catch (e) {
            reject(new Error('Parse: ' + res.responseText));
          }
        },
        onerror: function () { reject(new Error('Network error')); },
        ontimeout: function () { reject(new Error('Timeout')); },
      });
    });
  }

  /** 按序发送多个 webhook 请求，每个间隔 delay 毫秒；单个失败不阻塞后续 */
  function sendQueued(tasks, delay) {
    delay = delay || CONFIG.imageSendDelay;
    var results = { successes: [], failures: [] };

    function runNext(index) {
      if (index >= tasks.length) return Promise.resolve(results);
      var task = tasks[index];
      return task.fn().then(function (res) {
        results.successes.push({ label: task.label, result: res });
        log('✅ ' + task.label);
      }).catch(function (err) {
        results.failures.push({ label: task.label, error: err.message });
        warn('❌ ' + task.label + ': ' + err.message);
      }).then(function () {
        return new Promise(function (resolve) {
          setTimeout(function () { resolve(runNext(index + 1)); }, delay);
        });
      });
    }

    return runNext(0);
  }

  /** 拆分发送：先文字，再逐张发图片 */
  function sendTextThenImages(msg) {
    var tasks = [];

    if (msg.paragraphs.length > 0) {
      tasks.push({
        fn: function () { return sendTextViaWebhook(formatForwardText(msg)); },
        label: '文字',
      });
    } else if (msg.images.length > 0) {
      // 纯图片消息：先发一句提示文字（含 sender + time）
      var header = msg.sender + '  ' + msg.displayTime + '\n\n[📷 图片]';
      tasks.push({
        fn: function () { return sendTextViaWebhook(header); },
        label: '图片提示',
      });
    }

    for (var i = 0; i < msg.images.length; i++) {
      (function (img, idx) {
        tasks.push({
          fn: function () { return sendImageViaWebhook(img.imageKey); },
          label: '图片 #' + (idx + 1) + ' (' + img.imageKey.substring(0, 25) + '…)',
        });
      })(msg.images[i], i);
    }

    if (tasks.length === 0) {
      return Promise.reject(new Error('No content to send'));
    }

    return sendQueued(tasks, CONFIG.imageSendDelay).then(function (results) {
      if (results.successes.length === 0) {
        throw new Error('All sends failed: ' + results.failures.map(function (f) { return f.error; }).join('; '));
      }
      return results;
    });
  }

  /**
   * 转发编排 — 根据消息内容和配置选择最佳转发策略
   *
   * 策略链（auto 模式）：
   *   post（图文合并）→ separate（分开）→ text_fallback（纯文字 + [图片] 占位）
   */
  function forwardMessage(msg) {
    // 纯文字：直接发
    if (!msg.hasImages) {
      return sendTextViaWebhook(formatForwardText(msg));
    }

    // 图片转发关闭 → 纯文字
    if (!CONFIG.enableImageForwarding) {
      return sendTextViaWebhook(formatForwardText(msg));
    }

    var mode = CONFIG.imageForwardMode;

    // text_fallback：不转发图片本体，只在文字中标出
    if (mode === 'text_fallback') {
      return sendTextViaWebhook(formatForwardText(msg));
    }

    // post 模式：强制图文合并
    if (mode === 'post') {
      return sendPostViaWebhook(msg).catch(function (err) {
        warn('Post 发送失败: ' + err.message);
        return sendTextViaWebhook(formatForwardText(msg));
      });
    }

    // separate 模式：强制拆分
    if (mode === 'separate') {
      return sendTextThenImages(msg).catch(function (err) {
        warn('拆分发送失败: ' + err.message);
        return sendTextViaWebhook(formatForwardText(msg));
      });
    }

    // auto 模式（默认）：post → separate → text_fallback
    if (mode === 'auto') {
      return sendPostViaWebhook(msg).catch(function (postErr) {
        warn('Auto: post 失败 (' + postErr.message + ')，回退到分开发送');
        return sendTextThenImages(msg).catch(function (sepErr) {
          warn('Auto: 分开发送也失败 (' + sepErr.message + ')，回退到纯文字');
          return sendTextViaWebhook(formatForwardText(msg));
        });
      });
    }

    // 未知模式
    return sendTextViaWebhook(formatForwardText(msg));
  }

  /** 向后兼容的包装器 — 供 processMessage 等旧代码使用 */
  function forwardViaWebhook(msg) {
    return forwardMessage(msg);
  }

  /**
   * 格式化转发文本 —— 多段排版，不含当前时间（飞书 UI 自会显示发送时间）
   *
   * 输出样例：
   *   安妮  22:35
   *   美股又崩了。。。
   *
   *   安妮  21:42
   *   [Emm]
   *   问:
   *   葡萄柚爱学习 :我今天把集合竞价那节课看了3遍...
   */
  function formatForwardText(msg) {
    // 头部：发送者 + 原始消息时间
    var lines = [];
    lines.push(msg.sender + '  ' + msg.displayTime);
    lines.push(''); // 空行分隔

    // 正文段落原样保留
    for (var i = 0; i < msg.paragraphs.length; i++) {
      lines.push(msg.paragraphs[i]);
    }

    // 图片占位（仅在 text_fallback 或纯图片消息时显示）
    if (msg.hasImages && !CONFIG.enableImageForwarding) {
      lines.push('');
      lines.push('[📷 图片×' + msg.images.length + ']');
    }

    return lines.join('\n');
  }

  // ============================================================
  //  📊 状态面板（可拖拽）
  // ============================================================
  var statusData = {
    running: true,
    forwarded: 0,
    images: 0,
    skipped: 0,
    lastForwardTime: '',
    lastForwardPreview: '',
    currentChat: '',
    // 面板位置（从 localStorage 恢复，默认右上角）
    panelX: parseInt(GM_getValue('feishu_panel_x', '0'), 10) || null,
    panelY: parseInt(GM_getValue('feishu_panel_y', '0'), 10) || null,
  };

  function createStatusPanel() {
    var panel = document.createElement('div');
    panel.id = 'feishu-forward-panel';
    panel.innerHTML =
      '<div class="ff-panel-header" id="ff-panel-drag-handle" title="拖拽移动面板">' +
      '<span>🔄 消息转发</span>' +
      '<button id="ff-toggle-btn" title="暂停/恢复">⏸ 暂停</button>' +
      '</div>' +
      '<div class="ff-panel-body">' +
      '<div class="ff-row"><span class="ff-label">当前群聊:</span><span id="ff-current-chat">-</span></div>' +
      '<div class="ff-row"><span class="ff-label">已转发:</span><span id="ff-count">0</span> 条 | 图片 <span id="ff-img-count">0</span> 张</div>' +
      '<div class="ff-row"><span class="ff-label">最近:</span><span id="ff-last-time">-</span></div>' +
      '<div class="ff-row"><span class="ff-label">预览:</span><span id="ff-last-preview">-</span></div>' +
      '</div>';
    document.body.appendChild(panel);

    // 恢复上次保存的位置
    if (statusData.panelX !== null && statusData.panelY !== null) {
      panel.style.left = statusData.panelX + 'px';
      panel.style.top = statusData.panelY + 'px';
      panel.style.right = 'auto';
    }

    // ---- 拖拽功能 ----
    var dragHandle = document.getElementById('ff-panel-drag-handle');
    var isDragging = false;
    var dragStartX = 0;
    var dragStartY = 0;
    var panelStartX = 0;
    var panelStartY = 0;

    dragHandle.addEventListener('mousedown', function (e) {
      // 不拦截按钮点击
      if (e.target.tagName === 'BUTTON') return;
      isDragging = true;
      dragStartX = e.clientX;
      dragStartY = e.clientY;
      var rect = panel.getBoundingClientRect();
      panelStartX = rect.left;
      panelStartY = rect.top;
      // 切换到 left/top 定位
      panel.style.right = 'auto';
      panel.style.left = panelStartX + 'px';
      panel.style.top = panelStartY + 'px';
      panel.style.transition = 'none';
      e.preventDefault();
    });

    document.addEventListener('mousemove', function (e) {
      if (!isDragging) return;
      var dx = e.clientX - dragStartX;
      var dy = e.clientY - dragStartY;
      var newX = panelStartX + dx;
      var newY = panelStartY + dy;
      // 限制在可视区域内
      var maxX = window.innerWidth - panel.offsetWidth - 10;
      var maxY = window.innerHeight - panel.offsetHeight - 10;
      newX = Math.max(0, Math.min(newX, maxX));
      newY = Math.max(0, Math.min(newY, maxY));
      panel.style.left = newX + 'px';
      panel.style.top = newY + 'px';
    });

    document.addEventListener('mouseup', function () {
      if (!isDragging) return;
      isDragging = false;
      panel.style.transition = '';
      // 保存位置到 localStorage
      var left = parseInt(panel.style.left, 10);
      var top = parseInt(panel.style.top, 10);
      if (!isNaN(left) && !isNaN(top)) {
        GM_setValue('feishu_panel_x', left);
        GM_setValue('feishu_panel_y', top);
      }
    });

    // 暂停/恢复按钮
    document.getElementById('ff-toggle-btn').addEventListener('click', function () {
      statusData.running = !statusData.running;
      this.textContent = statusData.running ? '⏸ 暂停' : '▶ 恢复';
      this.style.background = statusData.running ? '#e74c3c' : '#27ae60';
      log(statusData.running ? '▶ 已恢复转发' : '⏸ 已暂停转发');
    });
  }

  function updateStatus(msg) {
    statusData.forwarded++;
    if (msg.hasImages) {
      statusData.images += msg.images.length;
    }
    statusData.lastForwardTime = new Date().toLocaleTimeString();
    statusData.lastForwardPreview = msg.content ? msg.content.substring(0, 30) : '[📷 图片]';

    var countEl = document.getElementById('ff-count');
    var imgCountEl = document.getElementById('ff-img-count');
    var timeEl = document.getElementById('ff-last-time');
    var previewEl = document.getElementById('ff-last-preview');

    if (countEl) countEl.textContent = statusData.forwarded;
    if (imgCountEl) imgCountEl.textContent = statusData.images;
    if (timeEl) timeEl.textContent = statusData.lastForwardTime;
    if (previewEl) previewEl.textContent = statusData.lastForwardPreview;
  }

  function updateCurrentChat(name) {
    statusData.currentChat = name || '-';
    var el = document.getElementById('ff-current-chat');
    if (el) el.textContent = statusData.currentChat;
  }

  // ============================================================
  //  🧵 核心逻辑
  // ============================================================
  function log() {
    if (CONFIG.debug) console.log.apply(console, ['[飞书转发]'].concat(Array.prototype.slice.call(arguments)));
  }

  function warn() {
    console.warn.apply(console, ['[飞书转发]'].concat(Array.prototype.slice.call(arguments)));
  }

  var pendingForward = false;

  // 启动阶段标志：第一条消息绕过时间窗口限制（保证 markAllExistingAsSeen 保留的最后一条旧消息也能转发）
  var isStartupPhase = true;

  function processMessage(msgEl) {
    var msg = extractMessage(msgEl);
    if (!msg.id) return;

    if (!shouldForward(msg)) return;

    var seen = getSeenIds();
    if (seen.has(msg.id) || seen.has(msg.fingerprint)) return;

    // --- 时间窗口检查 ---
    // 启动阶段跳过时间窗口（保证 markAllExistingAsSeen 保留的最后一条旧消息能转发）
    if (isStartupPhase) {
      isStartupPhase = false;
      log('🟢 启动阶段：跳过时间窗口检查');
    } else if (!isWithinTimeWindow(msg.msgTime)) {
      // 超时消息：标记为已见但跳过，防止后续重复扫描
      addSeenId(msg.id);
      statusData.skipped++;
      log('⏰ 超时跳过:', msg.sender, msg.displayTime, '→', msg.content.substring(0, 30));
      return;
    }

    if (pendingForward) {
      log('⏳ 上一条正在发送，稍后重试');
      return;
    }

    var previewText = msg.content ? msg.content.substring(0, 40) : ('[图片×' + msg.images.length + ']');
    log('📨 转发:', msg.sender, msg.displayTime, '→', previewText);

    pendingForward = true;
    forwardViaWebhook(msg)
      .then(function () {
        addSeenId(msg.id);
        updateStatus(msg);
        log('✅ 成功');
      })
      .catch(function (err) {
        warn('❌ 失败:', err.message);
        // 不标记为 seen，下次扫描重试
      })
      .then(function () {
        pendingForward = false;
      });
  }

  function scanMessages() {
    if (!statusData.running) return;

    var currentChat = getCurrentChatName();
    updateCurrentChat(currentChat);

    if (currentChat !== CONFIG.sourceChat) {
      // 每 30 次轮询才打印一次，避免刷屏
      if (Math.random() < 0.1) log('🔍 当前群聊: "' + currentChat + '"，目标: "' + CONFIG.sourceChat + '" — 不匹配，跳过');
      return;
    }

    var msgItems = document.querySelectorAll('.messageItem-wrapper');
    var seen = getSeenIds();
    var unprocessed = 0;

    for (var i = 0; i < msgItems.length; i++) {
      var id = msgItems[i].getAttribute('data-id');
      if (!id || seen.has(id)) continue;
      unprocessed++;
      processMessage(msgItems[i]);
    }

    if (unprocessed > 0) log('📋 本轮扫描：共 ' + msgItems.length + ' 条消息，处理 ' + unprocessed + ' 条');
  }

  /** 初始化时把页面上已有消息全部标记为"已见"，只保留最后一条留给转发。
   *  如果页面还没加载完（消息数为 0），自动延迟重试。 */
  function markAllExistingAsSeen(retryCount) {
    retryCount = retryCount || 0;
    var msgItems = document.querySelectorAll('.messageItem-wrapper');
    log('📌 markAllExistingAsSeen(重试#' + retryCount + '): 找到 ' + msgItems.length + ' 条消息');

    if (msgItems.length === 0) {
      if (retryCount < 20) {
        log('⏳ 消息列表尚未加载，1.5秒后重试...');
        setTimeout(function () { markAllExistingAsSeen(retryCount + 1); }, 1500);
      } else {
        warn('❌ 已重试 20 次仍无消息，请检查 .messageItem-wrapper 选择器是否已变化');
      }
      return;
    }

    var seen = getSeenIds();
    var added = 0;
    // 全部标记，但跳过最后一条（最新消息），让它被 scanMessages 转发
    var stopAt = msgItems.length - 1;
    for (var i = 0; i < stopAt; i++) {
      var id = msgItems[i].getAttribute('data-id');
      if (id && !seen.has(id)) {
        seen.add(id);
        added++;
      }
    }
    // 诊断：打印保留的最后一条消息信息
    var lastEl = msgItems[msgItems.length - 1];
    var lastId = lastEl ? lastEl.getAttribute('data-id') : 'N/A';
    var lastNameEl = lastEl ? lastEl.querySelector('.message-info-name') : null;
    var lastName = lastNameEl ? lastNameEl.textContent.trim() : '?';
    log('🔖 保留最后一条: id=' + lastId + ', 发送者=' + lastName);

    // ★ 关键：即使最后一条在之前的会话中被标记过，也要从 seen 中移除
    if (lastId && seen.has(lastId)) {
      seen.delete(lastId);
      log('🔓 最后一条之前被标记过，已从 seen 中移除，允许重新转发');
    }

    saveSeenIds(seen);
    if (added > 0) {
      log('📌 已预标记 ' + added + ' 条历史消息（保留最后 1 条待转发）');
    } else {
      log('📌 无新历史消息需标记，最后 1 条待转发');
    }

    // 标记完成后立即触发一次扫描
    setTimeout(scanMessages, 500);
  }

  // ============================================================
  //  🚀 启动
  // ============================================================
  function init() {
    log('🚀 v2.0 启动');
    log('   源: ' + CONFIG.sourceChat + ' → 目标: ' + CONFIG.targetChat);
    log('   时间窗口: ' + CONFIG.maxMessageAgeMinutes + ' 分钟');
    log('   转发模式: ' + CONFIG.forwardMode);

    // 注入样式
    GM_addStyle(
      '#feishu-forward-panel{' +
      'position:fixed;top:60px;right:10px;z-index:99999;width:220px;' +
      'background:#1a1a2e;color:#eee;border-radius:10px;font-size:12px;' +
      'font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;' +
      'box-shadow:0 4px 20px rgba(0,0,0,0.4);overflow:hidden;}' +
      '#feishu-forward-panel .ff-panel-header{' +
      'display:flex;justify-content:space-between;align-items:center;' +
      'padding:8px 12px;background:#16213e;font-weight:600;font-size:13px;' +
      'cursor:grab;user-select:none;}' +
      '#feishu-forward-panel .ff-panel-header:active{' +
      'cursor:grabbing;}' +
      '#feishu-forward-panel .ff-panel-header button{' +
      'border:none;color:#fff;padding:3px 8px;border-radius:4px;cursor:pointer;' +
      'font-size:11px;background:#e74c3c;}' +
      '#feishu-forward-panel .ff-panel-body{padding:8px 12px;}' +
      '#feishu-forward-panel .ff-row{margin-bottom:4px;line-height:1.5;}' +
      '#feishu-forward-panel .ff-label{color:#888;margin-right:4px;}' +
      '#feishu-forward-panel .ff-row span:last-child{color:#4fc3f7;word-break:break-all;}'
    );

    createStatusPanel();

    // ★ 关键：先把页面上所有已有消息标为"已见"（保留最后一条）
    markAllExistingAsSeen();

    // MutationObserver
    var setupObserver = function () {
      var msgList = document.querySelector('.messageList') || document.querySelector('[class*="list_items"]');
      if (msgList) {
        var observer = new MutationObserver(function () {
          clearTimeout(window.__ff_scan_timer);
          window.__ff_scan_timer = setTimeout(scanMessages, 500);
        });
        observer.observe(msgList, { childList: true, subtree: true });
        log('✅ Observer 已绑定');
      } else {
        setTimeout(setupObserver, 2000);
      }
    };
    setupObserver();

    // 轮询兜底
    setInterval(scanMessages, CONFIG.pollInterval);

    // 延迟扫描（等页面稳定）
    setTimeout(scanMessages, 4000);

    // 🔬 诊断：5 秒后输出完整状态
    setTimeout(function () {
      var msgItems = document.querySelectorAll('.messageItem-wrapper');
      var seen = getSeenIds();
      var unseenCount = 0;
      for (var i = 0; i < msgItems.length; i++) {
        if (!seen.has(msgItems[i].getAttribute('data-id'))) unseenCount++;
      }
      log('🔬 === 诊断报告 ===');
      log('   页面消息总数: ' + msgItems.length);
      log('   已标记(seen): ' + seen.size + ' 条');
      log('   未处理: ' + unseenCount + ' 条');
      log('   当前群聊: "' + getCurrentChatName() + '"');
      log('   目标群聊: "' + CONFIG.sourceChat + '"');
      log('   启动阶段: ' + isStartupPhase);
      log('   转发计数: ' + statusData.forwarded);
      log('   webhook 已配置: ' + (!CONFIG.webhookUrl.includes('YOUR-WEBHOOK-TOKEN')));
      if (unseenCount > 0) {
        // 打印第一条未处理消息的详情
        for (var j = 0; j < msgItems.length; j++) {
          if (!seen.has(msgItems[j].getAttribute('data-id'))) {
            var m = extractMessage(msgItems[j]);
            log('   ⚡ 待处理消息: id=' + m.id + ', 发送者=' + m.sender + ', 时间=' + m.displayTime + ', 内容=' + m.content.substring(0, 50));
            log('      shouldForward=' + shouldForward(m) + ', isWithinTimeWindow=' + (m.msgTime ? isWithinTimeWindow(m.msgTime) : 'null时间'));
            break;
          }
        }
      }
      log('🔬 === 诊断结束 ===');
    }, 5000);

    // SPA 路由变化重绑
    var lastUrl = location.href;
    setInterval(function () {
      if (location.href !== lastUrl) {
        lastUrl = location.href;
        log('🔄 路由变化');
        setTimeout(setupObserver, 2000);
        setTimeout(markAllExistingAsSeen, 3000);
      }
    }, 2000);
  }

  if (document.readyState === 'complete' || document.readyState === 'interactive') {
    init();
  } else {
    window.addEventListener('DOMContentLoaded', init);
  }
})();
