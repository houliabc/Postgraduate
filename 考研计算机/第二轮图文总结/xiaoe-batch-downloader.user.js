// ==UserScript==
// @name         小鹅通图文课程 Markdown 下载器（合并单文件版）
// @namespace    https://github.com/houliabc/xiaoe-downloader
// @version      9.0.0
// @description  单篇下载 + 一键批量下载合并为一个Markdown文件（章节→H1，文章→H2，内容标题降一级）
// @author       Claude (for houliabc)
// @match        https://*.xiaoe-tech.com/p/t_pc/course_pc_detail/image_text/*
// @match        https://*.xet-pc.citv.cn/p/t_pc/course_pc_detail/image_text/*
// @match        https://*.pc.xiaoe-tech.com/p/t_pc/course_pc_detail/image_text/*
// @grant        none
// ==/UserScript==

(function () {
  'use strict';

  // ======================== 配置 ========================
  var STORAGE_KEY = 'xe_batch_v9';
  var CONTENT_KEY = 'xe_batch_contents_v9';
  var BATCH_DELAY = 2800;

  var CSS = '\
#xe-dl-btn{position:fixed;top:120px;right:24px;z-index:2147483647;min-width:130px;padding:11px 18px;background:linear-gradient(135deg,#43e97b,#38f9d7);color:#1a1a1a;border:none;border-radius:22px;font-size:14px;font-weight:600;cursor:pointer;box-shadow:0 4px 16px rgba(67,233,123,.4);transition:all .25s;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;letter-spacing:.5px;white-space:nowrap;text-align:center}\
#xe-dl-btn:hover{transform:translateY(-2px);box-shadow:0 6px 22px rgba(67,233,123,.55)}\
#xe-batch-btn{position:fixed;top:175px;right:24px;z-index:2147483647;min-width:130px;padding:11px 18px;background:linear-gradient(135deg,#f093fb,#f5576c);color:#fff;border:none;border-radius:22px;font-size:14px;font-weight:600;cursor:pointer;box-shadow:0 4px 16px rgba(240,147,251,.45);transition:all .25s;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;letter-spacing:.5px;white-space:nowrap;text-align:center}\
#xe-batch-btn:hover{transform:translateY(-2px);box-shadow:0 6px 22px rgba(240,147,251,.6)}\
#xe-batch-btn:disabled{opacity:.5;cursor:not-allowed}\
#xe-panel{position:fixed;top:50%;left:50%;transform:translate(-50%,-50%);z-index:2147483647;width:640px;max-height:80vh;background:#fff;border-radius:16px;box-shadow:0 20px 60px rgba(0,0,0,.3);padding:28px;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;display:none;overflow-y:auto}\
#xe-panel.xe-show{display:block}\
#xe-panel h3{font-size:20px;margin:0 0 16px;color:#333}\
#xe-panel .xe-close{position:absolute;top:16px;right:20px;font-size:24px;cursor:pointer;color:#999;border:none;background:none;line-height:1}\
#xe-panel .xe-info{margin:8px 0 16px;font-size:13px;color:#888;line-height:1.5}\
#xe-panel .xe-item{display:flex;align-items:center;padding:7px 0;border-bottom:1px solid #f0f0f0;font-size:13px}\
#xe-panel .xe-item input[type=checkbox]{margin-right:10px;zoom:1.2;flex-shrink:0}\
#xe-panel .xe-item .xe-chapter{color:#667eea;margin-right:8px;font-weight:600;min-width:90px;flex-shrink:0}\
#xe-panel .xe-item .xe-title{flex:1;color:#333}\
#xe-panel .xe-actions{margin-top:20px;display:flex;gap:12px;flex-wrap:wrap}\
#xe-panel .xe-actions button{padding:10px 20px;border:none;border-radius:20px;font-size:14px;font-weight:600;cursor:pointer;transition:all .2s}\
#xe-panel .xe-actions button:hover{transform:translateY(-1px)}\
#xe-panel .xe-actions .xe-start{background:linear-gradient(135deg,#667eea,#764ba2);color:#fff;font-size:15px;padding:12px 28px}\
#xe-panel .xe-actions .xe-copy{background:#f0f0f0;color:#333}\
#xe-panel .xe-actions .xe-select-all{background:#e8f4fd;color:#2196F3}\
#xe-overlay{position:fixed;inset:0;z-index:2147483646;background:rgba(0,0,0,.4);display:none}\
#xe-overlay.xe-show{display:block}\
.xe-ok{background:linear-gradient(135deg,#43e97b,#38f9d7)!important;color:#1a1a1a!important}\
.xe-err{background:#e74c3c!important}\
#xe-progress-bar{position:fixed;top:0;left:0;height:4px;z-index:2147483648;background:linear-gradient(90deg,#667eea,#764ba2);transition:width .3s;border-radius:0 2px 2px 0}\
';

  // ======================== 工具函数 ========================
  function $1(s) { return document.querySelector(s); }
  function $a(s) { return document.querySelectorAll(s); }

  function findContentRoot() {
    var el = $1('.xe-preview__content');
    if (el && el.textContent.trim().length > 200) return el;
    var ps = document.querySelectorAll('.tabs-pane');
    for (var i = 0; i < ps.length; i++) { if (ps[i].offsetParent && ps[i].textContent.trim().length > 500) return ps[i]; }
    return $1('.content_left');
  }

  var BLOCK = {};
  'div section article main aside nav header footer p h1 h2 h3 h4 h5 h6 ul ol li blockquote hr table pre img figure details summary'
    .split(' ').forEach(function(t) { BLOCK[t] = 1; });

  function isBlock(el) { return BLOCK[el.tagName.toLowerCase()] === 1; }
  function hasOnlyInline(el) {
    for (var i = 0; i < el.children.length; i++) { if (isBlock(el.children[i])) return false; }
    return true;
  }

  function getStyle(el) {
    var cs = window.getComputedStyle(el), parts = [];
    var fw = cs.fontWeight;
    if (fw === 'bold' || parseInt(fw) >= 600) parts.push('font-weight:bold');
    if (cs.fontStyle === 'italic') parts.push('font-style:italic');
    var c = cs.color;
    if (c && !/rgb\(\s*0,\s*0,\s*0\)|rgb\(\s*5[01],\s*5[01],\s*5[01]\)|rgb\(\s*3\d,\s*3\d,\s*3\d\)/.test(c.replace(/\s/g, '')))
      parts.push('color:' + c);
    var bg = cs.backgroundColor;
    if (bg && bg !== 'rgba(0, 0, 0, 0)' && bg !== 'transparent') parts.push('background-color:' + bg);
    var td = cs.textDecorationLine;
    if (td && td !== 'none') parts.push('text-decoration:' + td);
    return parts;
  }

  function inline(el, inH) {
    var out = '';
    for (var i = 0; i < el.childNodes.length; i++) {
      var ch = el.childNodes[i];
      if (ch.nodeType === 3) { out += ch.textContent; continue; }
      if (ch.nodeType !== 1) continue;
      var tag = ch.tagName.toLowerCase();
      var inner = inline(ch, inH);
      if (!inner && tag !== 'br' && tag !== 'img') continue;
      switch (tag) {
        case 'strong': case 'b':
          var st = getStyle(ch), ex = [];
          for (var si = 0; si < st.length; si++) { if (st[si] !== 'font-weight:bold') ex.push(st[si]); }
          if (inH) out += inner;
          else if (ex.length) out += '<span style="' + ex.join(';') + '">**' + inner + '**</span>';
          else out += '**' + inner + '**';
          break;
        case 'em': case 'i': out += '*' + inner + '*'; break;
        case 'u': case 'ins': out += '<u>' + inner + '</u>'; break;
        case 'del': case 's': out += '~~' + inner + '~~'; break;
        case 'mark': out += '<mark>' + inner + '</mark>'; break;
        case 'code': case 'kbd': case 'samp': out += '`' + inner + '`'; break;
        case 'a': out += '[' + inner + '](' + ch.href + ')'; break;
        case 'br': out += '\n'; break;
        case 'span':
          var st2 = getStyle(ch);
          if (inH && st2.length === 1 && st2[0] === 'font-weight:bold') out += inner;
          else if (st2.length) out += '<span style="' + st2.join(';') + '">' + inner + '</span>';
          else out += inner;
          break;
        case 'img':
          // 懒加载兼容：优先 data-src > data-original > data-lazy-src > src > currentSrc
          var s = ch.getAttribute('data-src') || ch.getAttribute('data-original') || ch.getAttribute('data-lazy-src') || ch.getAttribute('src') || ch.src || ch.currentSrc || '';
          if (s) out += '\n![' + (ch.alt || '图片') + '](' + s + ')\n';
          break;
        case 'sub': out += '<sub>' + inner + '</sub>'; break;
        case 'sup': out += '<sup>' + inner + '</sup>'; break;
        default: out += inner;
      }
    }
    return out;
  }

  function asOneLine(el, inH) { var t = inline(el, inH).trim(); return t || ''; }

  function convert(root) {
    var L = [];
    function walk(el) {
      if (!el || el.nodeType !== 1) return;
      var tag = el.tagName.toLowerCase();
      if (tag === 'script' || tag === 'style' || tag === 'noscript' || tag === 'template' || tag === 'svg' || tag === 'iframe') return;
      if (el.hidden) return;
      if ((el.style || {}).display === 'none') return;
      if (el.closest && (el.closest('[class*="comment"]') || el.closest('[class*="sidebar"]') || el.closest('[class*="shop"]') || el.closest('[class*="store"]'))) return;
      if (el.classList) { for (var i = 0; i < el.classList.length; i++) { if (/^(comment|reply|sidebar|shop|store|footer)/.test(el.classList[i])) return; } }

      if (tag === 'h1' || tag === 'h2' || tag === 'h3' || tag === 'h4' || tag === 'h5' || tag === 'h6') {
        var ht = asOneLine(el, true); if (ht) { L.push('#'.repeat(parseInt(tag[1])) + ' ' + ht); L.push(''); }
        return;
      }
      if (tag === 'p') {
        var pt = asOneLine(el, false); if (pt) { L.push(pt); L.push(''); }
        return;
      }
      if (tag === 'pre') {
        var lang = '', ce = el.querySelector('code[class*="language-"]') || el.querySelector('code[class*="lang-"]');
        if (ce) { var m = ce.className.match(/(?:language|lang)-(\w+)/); if (m) lang = m[1]; }
        L.push('```' + lang); L.push(el.textContent.replace(/\n+$/, '')); L.push('```'); L.push('');
        return;
      }
      if (tag === 'img') {
        // 懒加载兼容
        var s = el.getAttribute('data-src') || el.getAttribute('data-original') || el.getAttribute('data-lazy-src') || el.getAttribute('src') || el.src || el.currentSrc || '';
        L.push('![' + (el.alt || '图片') + '](' + s + ')'); L.push('');
        return;
      }
      if (tag === 'hr') { L.push('---'); L.push(''); return; }

      if (tag === 'blockquote') {
        var bq = [];
        function q(el2) {
          if (el2.nodeType === 3) { var t2 = el2.textContent.trim(); if (t2) bq.push('> ' + t2); return; }
          if (el2.nodeType !== 1) return;
          var et = el2.tagName.toLowerCase();
          if (et === 'script' || et === 'style' || et === 'noscript') return;
          if (et === 'p') { var t2 = asOneLine(el2, false); if (t2) bq.push('> ' + t2); }
          else if (et === 'img') { var s2 = el2.getAttribute('data-src') || el2.getAttribute('data-original') || el2.getAttribute('data-lazy-src') || el2.getAttribute('src') || el2.src || el2.currentSrc || ''; bq.push('> ![' + (el2.alt || '图片') + '](' + s2 + ')'); }
          else if (et === 'pre') { bq.push('> ```'); bq.push('> ' + el2.textContent.trim()); bq.push('> ```'); }
          else if (et === 'br') { bq.push('>'); }
          else if (et === 'ul') { for (var j = 0; j < el2.children.length; j++) { var li = el2.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t2 = asOneLine(li, false); if (t2) bq.push('> - ' + t2); } } }
          else if (et === 'ol') { var n = 1; for (var j = 0; j < el2.children.length; j++) { var li = el2.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t2 = asOneLine(li, false); if (t2) bq.push('> ' + (n++) + '. ' + t2); } } }
          else if (el2.children && el2.children.length && hasOnlyInline(el2)) { var t2 = asOneLine(el2, false); if (t2) bq.push('> ' + t2); }
          else if (el2.children && el2.children.length) { for (var j = 0; j < el2.children.length; j++) q(el2.children[j]); }
          else { var t2 = el2.textContent.trim(); if (t2) bq.push('> ' + t2); }
        }
        for (var j = 0; j < el.childNodes.length; j++) q(el.childNodes[j]);
        if (bq.length) { for (var j = 0; j < bq.length; j++) L.push(bq[j]); L.push(''); }
        return;
      }

      if (tag === 'ul') {
        for (var j = 0; j < el.children.length; j++) { var li = el.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t = asOneLine(li, false); if (t) L.push('- ' + t); } }
        L.push(''); return;
      }
      if (tag === 'ol') {
        var n = 1;
        for (var j = 0; j < el.children.length; j++) { var li = el.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t = asOneLine(li, false); if (t) L.push((n++) + '. ' + t); } }
        L.push(''); return;
      }

      if (el.children && el.children.length) {
        if (hasOnlyInline(el)) {
          var t = asOneLine(el, false); if (t) { L.push(t); L.push(''); }
        } else {
          for (var j = 0; j < el.children.length; j++) walk(el.children[j]);
        }
      } else {
        var t = asOneLine(el, false); if (t) { L.push(t); L.push(''); }
      }
    }

    for (var i = 0; i < root.children.length; i++) walk(root.children[i]);
    return L;
  }

  // ─── 只把 H2 降为 H3（避免和文章标题 ## 冲突），H3 及以下不动 ───
  function downgradeHeadings(lines) {
    return lines.map(function(line) {
      // 只降级 ## 开头的内容标题（和文章标题同级 → 需降一级）
      if (/^##\s/.test(line) && !/^###/.test(line)) return '#' + line;
      return line;
    });
  }

  // ======================== 单篇复制 ========================
  function doSingleCopy() {
    var title = (document.title || '').trim() || '课程图文';
    var root = findContentRoot();
    if (!root) throw new Error('未找到内容区，刷新后重试');

    var lines = convert(root);
    var md = '## ' + title + '\n\n> 来源: ' + window.location.href + '\n> 时间: ' + new Date().toLocaleString('zh-CN') + '\n\n---\n\n' + lines.join('\n');

    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(md);
    } else {
      var ta = document.createElement('textarea');
      ta.value = md; ta.style.cssText = 'position:fixed;left:-9999px';
      document.body.appendChild(ta); ta.select(); document.execCommand('copy'); document.body.removeChild(ta);
    }
    return title;
  }

  // ======================== API ========================
  function getCourseId() {
    var m = window.location.search.match(/product_id=([^&]+)/);
    return m ? m[1] : null;
  }
  function getCommunityId() {
    var m = window.location.search.match(/community_id=([^&]+)/);
    return m ? m[1] : null;
  }
  function getAppId() { return window.APPID || 'appvpmptkl94774'; }

  function apiUrl() {
    return window.location.origin + '/xe.course.business_go.avoidlogin.e_course.resource_catalog_list.get/1.0.0';
  }

  async function fetchChapterList(pId) {
    var body = new URLSearchParams({
      app_id: getAppId(), resource_id: '', course_id: getCourseId(),
      p_id: pId, order: 'asc', page: '1', page_size: '100',
      sub_course_id: '', is_display_auth_sections: '0', community_id: getCommunityId()
    }).toString();
    var resp = await fetch(apiUrl(), { method: 'POST', headers: { 'Content-Type': 'application/x-www-form-urlencoded' }, body: body, credentials: 'include' });
    var data = await resp.json();
    if (data.code !== 0 || !data.data) throw new Error('API错误: ' + (data.msg || ''));
    return data.data.list;
  }

  async function discoverAllItems() {
    var chapters = await fetchChapterList('0');
    var items = [];
    for (var i = 0; i < chapters.length; i++) {
      var ch = chapters[i];
      var list = await fetchChapterList(ch.resource_id);
      for (var j = 0; j < list.length; j++) {
        var it = list[j];
        if (it.resource_type === 1 && it.resource_title && it.resource_title.indexOf('图文总结') !== -1) {
          items.push({
            chapterTitle: ch.chapter_title || ch.resource_title,
            title: it.resource_title,
            resourceId: it.resource_id
          });
        }
      }
    }
    return items;
  }

  function buildUrl(resourceId) {
    return window.location.origin + '/p/t_pc/course_pc_detail/image_text/' + resourceId +
      '?community_id=' + encodeURIComponent(getCommunityId()) +
      '&product_id=' + encodeURIComponent(getCourseId()) +
      '&anonymous=2&type=6';
  }

  // ======================== 面板 ========================
  var _allItems = [];
  var _panelCreated = false;

  function createPanel() {
    var overlay = document.createElement('div'); overlay.id = 'xe-overlay'; document.body.appendChild(overlay);
    var panel = document.createElement('div'); panel.id = 'xe-panel';
    panel.innerHTML = '\
      <button class="xe-close" id="xe-panel-close">&times;</button>\
      <h3>\u{1F4DA} 批量下载图文总结（合并为单文件）</h3>\
      <div class="xe-info" id="xe-panel-info">正在加载课程目录...</div>\
      <div id="xe-item-list"></div>\
      <div class="xe-actions">\
        <button class="xe-select-all" id="xe-select-all">✅ 全选 / 取消全选</button>\
        <button class="xe-copy" id="xe-copy-urls">\u{1F4CB} 复制选中链接</button>\
        <button class="xe-start" id="xe-start-batch">\u{1F680} 开始合并下载</button>\
      </div>\
      <div style="margin-top:14px;font-size:12px;color:#999;line-height:1.6">\
        \u{1F539} <b>合并下载</b>：自动翻页收集内容，最终生成一个 .md 文件<br>\
        \u{1F539} 标题层级：<code># 章节名</code> → <code>## 文章标题</code> → <code>### 内容小标题</code><br>\
        \u{1F539} 过程约需 N×3 秒，<b>请勿关闭页面</b>，完成后自动下载\
      </div>';
    document.body.appendChild(panel);

    $1('#xe-panel-close').onclick = hidePanel;
    overlay.onclick = hidePanel;
    $1('#xe-select-all').onclick = toggleSelectAll;
    $1('#xe-copy-urls').onclick = copyUrls;
    $1('#xe-start-batch').onclick = startBatch;
  }

  function showPanel() { $1('#xe-overlay').classList.add('xe-show'); $1('#xe-panel').classList.add('xe-show'); loadPanelData(); }
  function hidePanel() { $1('#xe-overlay').classList.remove('xe-show'); $1('#xe-panel').classList.remove('xe-show'); }

  async function loadPanelData() {
    var info = $1('#xe-panel-info'), listEl = $1('#xe-item-list');
    info.textContent = '正在加载课程目录...'; listEl.innerHTML = '';
    try {
      _allItems = await discoverAllItems();
      if (!_allItems.length) { info.textContent = '⚠️ 未找到"图文总结"内容'; return; }
      info.innerHTML = '\u{1F4E6} 共 <b>' + _allItems.length + '</b> 篇图文总结，勾选要下载的项目：<br><span style="font-size:12px;color:#aaa">输出格式：<code># 章节</code> → <code>## 文章名</code> → <code>### 正文标题</code></span>';
      var html = '';
      for (var i = 0; i < _allItems.length; i++) {
        var it = _allItems[i];
        html += '<div class="xe-item"><input type="checkbox" id="xe-chk-' + i + '" checked data-idx="' + i + '"><span class="xe-chapter">' + esc(it.chapterTitle) + '</span><span class="xe-title">' + esc(it.title) + '</span></div>';
      }
      listEl.innerHTML = html;
      updateCount();
      listEl.querySelectorAll('input[type=checkbox]').forEach(function(cb) { cb.onchange = updateCount; });
    } catch(e) { info.textContent = '❌ 加载失败: ' + e.message; }
  }

  function getSelected() {
    var r = [];
    $a('#xe-item-list input[type=checkbox]:checked').forEach(function(cb) {
      var i = parseInt(cb.getAttribute('data-idx'));
      if (!isNaN(i) && _allItems[i]) r.push(_allItems[i]);
    });
    return r;
  }

  function updateCount() {
    var n = getSelected().length;
    var btn = $1('#xe-start-batch');
    if (btn) btn.textContent = '\u{1F680} 开始合并下载（' + n + ' 篇 → 1 个文件）';
  }

  function toggleSelectAll() {
    var cbs = $a('#xe-item-list input[type=checkbox]');
    var all = true;
    cbs.forEach(function(cb) { if (!cb.checked) all = false; });
    cbs.forEach(function(cb) { cb.checked = !all; });
    updateCount();
  }

  function copyUrls() {
    var items = getSelected();
    if (!items.length) { alert('请先勾选'); return; }
    var urls = items.map(function(it) { return buildUrl(it.resourceId); }).join('\n');
    try { GM_setClipboard(urls, 'text'); } catch(e) {
      navigator.clipboard.writeText(urls).catch(function() {
        var ta = document.createElement('textarea'); ta.value = urls; document.body.appendChild(ta); ta.select(); document.execCommand('copy'); document.body.removeChild(ta);
      });
    }
    alert('✅ 已复制 ' + items.length + ' 个链接');
  }

  function esc(s) { return s.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;'); }

  // ======================== 课程名称提取 ========================
  function getCourseTitle() {
    // 尝试从小鹅通页面常见选择器获取课程名称
    var selectors = [
      '.course-title', '.class-title', '.product-title',
      '[class*="course"][class*="title"]',
      '.xe-header__title', '.catalog-header__title',
      '.breadcrumb span:last-child', '[class*="breadcrumb"] [class*="active"]'
    ];
    for (var i = 0; i < selectors.length; i++) {
      try {
        var el = $1(selectors[i]);
        if (el && el.textContent.trim()) return el.textContent.trim();
      } catch(e) {}
    }
    // 兜底：尝试从 document.title 中提取（格式通常是 "文章名_课程名" 或类似）
    var dt = (document.title || '').trim();
    var parts = dt.split(/[_\-\—\|]/);
    if (parts.length > 1) {
      var last = parts[parts.length - 1].trim();
      if (last && last.length > 1 && last.length < 50) return last;
    }
    return null;
  }

  // ======================== 批量核心：收集 + 合并 ========================
  function startBatch() {
    var items = getSelected();
    if (!items.length) { alert('请先勾选'); return; }

    // 构建队列，按章节分组
    var queue = items.map(function(it, idx) {
      return { index: idx, total: items.length, title: it.title, chapterTitle: it.chapterTitle, resourceId: it.resourceId, url: buildUrl(it.resourceId) };
    });

    var state = { queue: queue, currentIndex: 0, startedAt: new Date().toISOString(), collected: 0, failed: 0, courseTitle: getCourseTitle() || '课程图文合集' };

    // 初始化内容存储（空数组）
    try {
      localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
      localStorage.setItem(CONTENT_KEY, JSON.stringify([]));
    } catch(e) { alert('localStorage 写入失败，请清理浏览器存储'); return; }

    hidePanel();
    if (!confirm('\u{1F680} 即将合并下载 ' + queue.length + ' 篇图文总结为一个文件。\n\n每篇间隔约 ' + (BATCH_DELAY/1000) + ' 秒，请勿关闭页面。\n开始？')) {
      localStorage.removeItem(STORAGE_KEY); localStorage.removeItem(CONTENT_KEY); return;
    }
    window.location.href = queue[0].url;
  }

  function hasPendingBatch() {
    try { return !!localStorage.getItem(STORAGE_KEY); } catch(e) { return false; }
  }

  function getBatchState() {
    try { return JSON.parse(localStorage.getItem(STORAGE_KEY)); } catch(e) { return null; }
  }

  function getCollectedContents() {
    try { return JSON.parse(localStorage.getItem(CONTENT_KEY)) || []; } catch(e) { return []; }
  }

  function processBatch() {
    var state = getBatchState();
    if (!state || state.currentIndex >= state.queue.length) { finishAndDownload(); return; }

    var item = state.queue[state.currentIndex];
    var currentUrl = window.location.href;

    // 校验URL
    if (currentUrl.indexOf(item.resourceId) === -1) {
      console.warn('[XE-BATCH] URL不匹配，终止。期望:', item.resourceId);
      localStorage.removeItem(STORAGE_KEY); localStorage.removeItem(CONTENT_KEY);
      return;
    }

    // 等待内容渲染 + 触发懒加载图片
    waitForContent(function() {
      triggerLazyImages(function() {
        try {
          var root = findContentRoot();
          if (root) {
            var lines = convert(root);
            // 降级内容中的标题
            lines = downgradeHeadings(lines);

            // 存到累积数组
            var collected = getCollectedContents();
            collected.push({
              chapterTitle: item.chapterTitle,
              title: item.title.replace(/^图文总结[：:]\s*/, ''),  // 去掉"图文总结："前缀
              resourceId: item.resourceId,
              sourceUrl: currentUrl,
              lines: lines
            });
            try { localStorage.setItem(CONTENT_KEY, JSON.stringify(collected)); } catch(e) {
              console.error('[XE-BATCH] 内容存储失败（可能超容量）', e);
            }
            state.collected++;
            console.log('[XE-BATCH] 已收集 (' + (state.currentIndex + 1) + '/' + state.queue.length + '): ' + item.title);
          } else {
            state.failed++;
            console.error('[XE-BATCH] 内容为空: ' + item.title);
          }
        } catch(e) {
          state.failed++;
          console.error('[XE-BATCH] 失败: ' + item.title, e);
        }

        state.currentIndex++;
        if (state.currentIndex >= state.queue.length) {
          // 全部收集完毕
          finishAndDownload();
          return;
        }

        // 保存进度，跳到下一页
        try { localStorage.setItem(STORAGE_KEY, JSON.stringify(state)); } catch(e) {}
        updateProgress(state.currentIndex, state.queue.length);
        setTimeout(function() {
          window.location.href = state.queue[state.currentIndex].url;
        }, BATCH_DELAY);
      });
    });
  }

  // ─── 滚屏触发懒加载图片 ───
  function triggerLazyImages(cb) {
    var scrollHeight = document.body.scrollHeight;
    var winHeight = window.innerHeight;
    // 逐段滚到底部，触发所有懒加载图片
    var pos = winHeight;
    function step() {
      window.scrollTo(0, pos);
      pos += winHeight;
      if (pos < scrollHeight) {
        setTimeout(step, 200);
      } else {
        // 滚到底了，等一会儿让图片加载，再滚回顶部
        setTimeout(function() {
          window.scrollTo(0, 0);
          setTimeout(cb, 400);
        }, 600);
      }
    }
    step();
  }

  function waitForContent(cb) {
    var tries = 0;
    function check() {
      tries++;
      var root = findContentRoot();
      if (root && root.textContent.trim().length > 200) { setTimeout(cb, 600); return; }
      if (tries >= 35) { console.warn('[XE-BATCH] 超时'); cb(); return; }
      setTimeout(check, 200);
    }
    setTimeout(check, BATCH_DELAY);
  }

  function finishAndDownload() {
    var state = getBatchState();
    var collected = getCollectedContents();

    if (!collected.length) {
      alert('❌ 没有收集到任何内容');
      cleanup();
      return;
    }

    // 合并内容
    var md = buildCombinedMarkdown(collected, state);
    var courseTitle = (state && state.courseTitle) || '课程图文合集';
    var safeName = (courseTitle + '_图文总结合集').replace(/[\\/:*?"<>|]/g, '_');
    var blob = new Blob(['﻿' + md], { type: 'text/markdown;charset=utf-8' });
    var url = URL.createObjectURL(blob);
    var a = document.createElement('a'); a.href = url; a.download = safeName + '.md';
    document.body.appendChild(a); a.click(); document.body.removeChild(a);
    URL.revokeObjectURL(url);

    var msg = '✅ 合并下载完成！\n📦 ' + (state ? state.collected : collected.length) + ' 篇 → 1 个文件\n📁 文件已保存到下载目录';
    alert(msg);
    cleanup();
  }

  function buildCombinedMarkdown(collected, state) {
    var lines = [];

    // 文件标题
    var courseTitle = (state && state.courseTitle) || '课程图文合集';
    lines.push('# ' + courseTitle + ' — 图文总结合集');
    lines.push('');
    lines.push('> 自动生成于: ' + new Date().toLocaleString('zh-CN'));
    lines.push('> 共收录 ' + collected.length + ' 篇图文总结');
    if (state && state.queue) {
      var chapters = {};
      collected.forEach(function(c) { chapters[c.chapterTitle] = (chapters[c.chapterTitle] || 0) + 1; });
      lines.push('> 涵盖章节: ' + Object.keys(chapters).join('、'));
    }
    lines.push('');
    lines.push('---');
    lines.push('');

    // 按章节分组
    var chapterGroups = {};
    collected.forEach(function(item) {
      var ch = item.chapterTitle;
      if (!chapterGroups[ch]) chapterGroups[ch] = [];
      chapterGroups[ch].push(item);
    });

    // 按章节顺序输出（保持原始发现顺序）
    var chapterOrder = [];
    collected.forEach(function(item) {
      if (chapterOrder.indexOf(item.chapterTitle) === -1) chapterOrder.push(item.chapterTitle);
    });

    for (var ci = 0; ci < chapterOrder.length; ci++) {
      var chName = chapterOrder[ci];
      var articles = chapterGroups[chName];
      if (!articles || !articles.length) continue;

      // 章节标题（H1）
      lines.push('# ' + chName);
      lines.push('');

      for (var ai = 0; ai < articles.length; ai++) {
        var art = articles[ai];

        // 文章标题（H2，已去掉"图文总结："前缀）
        lines.push('## ' + art.title);
        lines.push('');

        // 文章内容（已降级的标题）
        var bodyLines = art.lines || [];
        for (var bi = 0; bi < bodyLines.length; bi++) {
          lines.push(bodyLines[bi]);
        }

        // 文章间分隔
        lines.push('');
        lines.push('---');
        lines.push('');
      }
    }

    return lines.join('\n');
  }

  function cleanup() {
    try { localStorage.removeItem(STORAGE_KEY); localStorage.removeItem(CONTENT_KEY); } catch(e) {}
    removeProgress();
  }

  // ======================== 进度条 ========================
  function updateProgress(current, total) {
    var bar = $1('#xe-progress-bar');
    if (!bar) { bar = document.createElement('div'); bar.id = 'xe-progress-bar'; document.body.appendChild(bar); }
    bar.style.width = Math.round((current / total) * 100) + '%';
  }

  function removeProgress() {
    var bar = $1('#xe-progress-bar');
    if (bar) { bar.style.opacity = '0'; bar.style.transition = 'opacity 0.5s'; setTimeout(function() { bar.remove(); }, 600); }
  }

  // ======================== 初始化 ========================
  function initButtons() {
    if (document.getElementById('xe-dl-btn')) return;
    var s = document.createElement('style'); s.textContent = CSS; document.head.appendChild(s);

    var btn = document.createElement('button'); btn.id = 'xe-dl-btn'; btn.textContent = '\u{1F4CB} 复制 MD';
    btn.onclick = function() {
      if (btn.classList.contains('xe-ok')) return;
      try { doSingleCopy(); btn.classList.add('xe-ok'); btn.textContent = '✅ 已复制！'; setTimeout(function() { btn.classList.remove('xe-ok'); btn.textContent = '\u{1F4CB} 复制 MD'; }, 2000); }
      catch(e) { console.error(e); btn.classList.add('xe-err'); btn.textContent = '❌ 失败'; setTimeout(function() { btn.classList.remove('xe-err'); btn.textContent = '\u{1F4CB} 复制 MD'; }, 2500); }
    };
    document.body.appendChild(btn);

    var batchBtn = document.createElement('button'); batchBtn.id = 'xe-batch-btn'; batchBtn.textContent = '\u{1F4DA} 批量合并';
    batchBtn.onclick = function() {
      if (!getCourseId()) { alert('❌ 未检测到课程ID'); return; }
      if (!_panelCreated) { createPanel(); _panelCreated = true; }
      showPanel();
    };
    document.body.appendChild(batchBtn);
    console.log('[XE-DL] v9.0 合并单文件版就绪');
  }

  var _batchProcessed = false;

  function init() {
    // 批量模式
    if (hasPendingBatch() && !_batchProcessed) {
      _batchProcessed = true;
      var state = getBatchState();
      var total = state ? state.queue.length : 0;
      updateProgress(state ? state.currentIndex : 0, total);

      var s = document.createElement('style'); s.textContent = CSS; document.head.appendChild(s);
      var pbtn = document.createElement('button');
      pbtn.id = 'xe-dl-btn';
      pbtn.style.cssText = 'background:linear-gradient(135deg,#f093fb,#f5576c)!important';
      pbtn.textContent = '⏳ 收集 ' + (state ? state.currentIndex + 1 : '?') + '/' + total;
      pbtn.onclick = function() {
        if (confirm('取消批量下载？已收集的内容将丢失。')) { cleanup(); pbtn.textContent = '❌ 已取消'; _batchProcessed = false; }
      };
      document.body.appendChild(pbtn);
      processBatch();
      return;
    }

    // 正常模式
    var root = findContentRoot();
    if (!root) { setTimeout(init, 500); return; }
    initButtons();
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', function() { setTimeout(init, 1500); });
  } else {
    setTimeout(init, 800);
  }
})();
