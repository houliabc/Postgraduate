// ==UserScript==
// @name         小鹅通图文课程 Markdown 下载器
// @namespace    https://github.com/houliabc/xiaoe-downloader
// @version      7.0.0
// @description  一键下载小鹅通图文课程为 Markdown（保留格式，图片用原始URL）
// @author       Claude (for houliabc)
// @match        https://*.xiaoe-tech.com/p/t_pc/course_pc_detail/image_text/*
// @match        https://*.xet-pc.citv.cn/p/t_pc/course_pc_detail/image_text/*
// @match        https://*.pc.xiaoe-tech.com/p/t_pc/course_pc_detail/image_text/*
// @grant        none
// ==/UserScript==

(function () {
  'use strict';

  var CSS = '#xe-copy-btn{position:fixed;top:285px;right:24px;z-index:2147483647;min-width:130px;padding:11px 18px;background:linear-gradient(135deg,#43e97b,#38f9d7);color:#1a1a1a;border:none;border-radius:22px;font-size:14px;font-weight:600;cursor:pointer;box-shadow:0 4px 16px rgba(67,233,123,.4);transition:all .25s;font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",Roboto,sans-serif;letter-spacing:.5px;white-space:nowrap;text-align:center}#xe-copy-btn:hover{transform:translateY(-2px);box-shadow:0 6px 22px rgba(67,233,123,.55)}#xe-copy-btn.xe-ok{background:#2196F3;color:#fff}#xe-copy-btn.xe-err{background:#e74c3c}';

  // ======================== 工具 ========================
  function $1(s) { return document.querySelector(s); }

  function findContentRoot() {
    var el = $1('.xe-preview__content');
    if (el && el.textContent.trim().length > 200) return el;
    var ps = document.querySelectorAll('.tabs-pane');
    for (var i = 0; i < ps.length; i++) { if (ps[i].offsetParent && ps[i].textContent.trim().length > 500) return ps[i]; }
    return $1('.content_left');
  }

  // ── 块级标签集合 ──
  var BLOCK = {};
  'div section article main aside nav header footer p h1 h2 h3 h4 h5 h6 ul ol li blockquote hr table pre img figure details summary'
    .split(' ').forEach(function(t) { BLOCK[t] = 1; });

  function isBlock(el) { return BLOCK[el.tagName.toLowerCase()] === 1; }
  function hasOnlyInline(el) {
    for (var i = 0; i < el.children.length; i++) { if (isBlock(el.children[i])) return false; }
    return true;
  }

  // ── 行内样式 ──
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

  // ── 行内元素 → MD 片段 ──
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
          var s = ch.getAttribute('src') || ch.src || '';
          if (s) out += '\n![' + (ch.alt || '图片') + '](' + s + ')\n';
          break;
        case 'sub': out += '<sub>' + inner + '</sub>'; break;
        case 'sup': out += '<sup>' + inner + '</sup>'; break;
        default: out += inner;
      }
    }
    return out;
  }

  // ── 将任意元素转成一行 MD（用于内联容器） ──
  function asOneLine(el, inH) { var t = inline(el, inH).trim(); return t || ''; }

  // ── DOM → MD ──
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

      // ── 标题 ──
      if (tag === 'h1' || tag === 'h2' || tag === 'h3' || tag === 'h4' || tag === 'h5' || tag === 'h6') {
        var ht = asOneLine(el, true); if (ht) { L.push('#'.repeat(parseInt(tag[1])) + ' ' + ht); L.push(''); }
        return;
      }
      // ── 段落 ──
      if (tag === 'p') {
        var pt = asOneLine(el, false); if (pt) { L.push(pt); L.push(''); }
        return;
      }
      // ── 代码块 ──
      if (tag === 'pre') {
        var lang = '', ce = el.querySelector('code[class*="language-"]') || el.querySelector('code[class*="lang-"]');
        if (ce) { var m = ce.className.match(/(?:language|lang)-(\w+)/); if (m) lang = m[1]; }
        L.push('```' + lang); L.push(el.textContent.replace(/\n+$/, '')); L.push('```'); L.push('');
        return;
      }
      // ── 图片 ──
      if (tag === 'img') {
        var s = el.getAttribute('src') || el.src || '';
        L.push('![' + (el.alt || '图片') + '](' + s + ')'); L.push('');
        return;
      }
      // ── 分割线 ──
      if (tag === 'hr') { L.push('---'); L.push(''); return; }

      // ── 引用块 ──
      if (tag === 'blockquote') {
        var bq = [];
        function q(el2) {
          if (el2.nodeType === 3) { var t2 = el2.textContent.trim(); if (t2) bq.push('> ' + t2); return; }
          if (el2.nodeType !== 1) return;
          var et = el2.tagName.toLowerCase();
          if (et === 'script' || et === 'style' || et === 'noscript') return;
          if (et === 'p') { var t2 = asOneLine(el2, false); if (t2) bq.push('> ' + t2); }
          else if (et === 'img') { var s2 = el2.getAttribute('src') || el2.src || ''; bq.push('> ![' + (el2.alt || '图片') + '](' + s2 + ')'); }
          else if (et === 'pre') { bq.push('> ```'); bq.push('> ' + el2.textContent.trim()); bq.push('> ```'); }
          else if (et === 'br') { bq.push('>'); }
          else if (et === 'ul') { for (var j = 0; j < el2.children.length; j++) { var li = el2.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t2 = asOneLine(li, false); if (t2) bq.push('> - ' + t2); } } }
          else if (et === 'ol') { var n = 1; for (var j = 0; j < el2.children.length; j++) { var li = el2.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t2 = asOneLine(li, false); if (t2) bq.push('> ' + (n++) + '. ' + t2); } } }
          // ★ 关键：内联容器（如 section > span+strong）→ 合并为一行
          else if (el2.children && el2.children.length && hasOnlyInline(el2)) { var t2 = asOneLine(el2, false); if (t2) bq.push('> ' + t2); }
          else if (el2.children && el2.children.length) { for (var j = 0; j < el2.children.length; j++) q(el2.children[j]); }
          else { var t2 = el2.textContent.trim(); if (t2) bq.push('> ' + t2); }
        }
        for (var j = 0; j < el.childNodes.length; j++) q(el.childNodes[j]);
        if (bq.length) { for (var j = 0; j < bq.length; j++) L.push(bq[j]); L.push(''); }
        return;
      }

      // ── 无序列表 ──
      if (tag === 'ul') {
        for (var j = 0; j < el.children.length; j++) { var li = el.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t = asOneLine(li, false); if (t) L.push('- ' + t); } }
        L.push(''); return;
      }
      // ── 有序列表 ──
      if (tag === 'ol') {
        var n = 1;
        for (var j = 0; j < el.children.length; j++) { var li = el.children[j]; if (li.tagName && li.tagName.toLowerCase() === 'li') { var t = asOneLine(li, false); if (t) L.push((n++) + '. ' + t); } }
        L.push(''); return;
      }

      // ── 容器 ──
      if (el.children && el.children.length) {
        if (hasOnlyInline(el)) {
          // 内联容器：合并为一段
          var t = asOneLine(el, false); if (t) { L.push(t); L.push(''); }
        } else {
          // 块级容器：仅递归子元素，不单独输出文字节点
          for (var j = 0; j < el.children.length; j++) walk(el.children[j]);
        }
      } else {
        var t = asOneLine(el, false); if (t) { L.push(t); L.push(''); }
      }
    }

    for (var i = 0; i < root.children.length; i++) walk(root.children[i]);
    return L;
  }

  // ======================== 主流程 ========================
  function doCopy() {
    var title = (document.title || '').trim() || '课程图文';
    var root = findContentRoot();
    if (!root) throw new Error('未找到内容区，刷新后重试');

    var lines = convert(root);
    var md = '## ' + title + '\n\n> 来源: ' + window.location.href + '\n> 时间: ' + new Date().toLocaleString('zh-CN') + '\n\n---\n\n' + lines.join('\n');

    // 复制到剪贴板
    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(md);
    } else {
      var ta = document.createElement('textarea');
      ta.value = md; ta.style.cssText = 'position:fixed;left:-9999px';
      document.body.appendChild(ta); ta.select(); document.execCommand('copy'); document.body.removeChild(ta);
    }
    return title;
  }

  // ======================== 按钮 ========================
  function init() {
    var root = findContentRoot();
    if (!root) { setTimeout(init, 500); return; }
    if (document.getElementById('xe-copy-btn')) return;

    var s = document.createElement('style'); s.textContent = CSS; document.head.appendChild(s);
    var btn = document.createElement('button'); btn.id = 'xe-copy-btn'; btn.textContent = '\u{1F4CB} 复制 MD';
    btn.onclick = function () {
      if (btn.classList.contains('xe-ok')) return;
      try {
        doCopy();
        btn.classList.add('xe-ok'); btn.textContent = '✅ 已复制！';
        setTimeout(function () { btn.classList.remove('xe-ok'); btn.textContent = '\u{1F4CB} 复制 MD'; }, 2000);
      } catch (e) {
        console.error('[XE-Copy]', e);
        btn.classList.add('xe-err'); btn.textContent = '❌ 失败';
        setTimeout(function () { btn.classList.remove('xe-err'); btn.textContent = '\u{1F4CB} 复制 MD'; }, 2500);
      }
    };
    document.body.appendChild(btn);
    console.log('[XE-Copy] v8.0 就绪');
  }
  setTimeout(init, document.readyState === 'loading' ? 1500 : 800);
})();
