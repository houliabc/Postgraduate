// ==UserScript==
// @name         正方教务系统自动评教
// @namespace    http://tampermonkey.net/
// @version      1.0
// @description  自动完成教学质量评价，全部打100分，逐门保存，最后提交
// @author       Claude
// @match        http://jwgl2.gdyzy.edu.cn/xsjxpj.aspx*
// @grant        GM_setValue
// @grant        GM_getValue
// @run-at       document-end
// ==/UserScript==

(function() {
    'use strict';

    const DELAY = 2000; // 页面加载后等待时间(ms)，确保 ASP.NET postback 完成

    setTimeout(() => {
        const courseSelect = document.getElementById('pjkc');
        if (!courseSelect) return; // 不在评教页面，跳过

        const currentValue = courseSelect.value;
        const totalCourses = courseSelect.options.length;
        const currentIndex = courseSelect.selectedIndex;
        const courseName = courseSelect.options[currentIndex]?.text || currentValue;
        const isLast = (currentIndex === totalCourses - 1);

        // 读取已保存课程列表（跨页面 reload 持久化）
        let saved = GM_getValue('pj_saved', '');
        let savedList = saved ? saved.split(',') : [];

        // 如果全部课程已保存 → 提交
        if (savedList.length >= totalCourses) {
            log('✅ 全部课程已保存，正在提交...');
            clickButton('提交');
            GM_setValue('pj_saved', ''); // 清除状态，下次可重新评
            return;
        }

        // 当前课程已保存（postback 重复触发），跳过
        if (savedList.includes(currentValue)) {
            log(`⏭️ "${courseName}" 已保存，等待跳转下一门...`);
            return;
        }

        // ★ 核心：所有评分拉满 100
        let count = 0;
        document.querySelectorAll('select').forEach(s => {
            if (s.id !== 'pjkc') {
                s.value = '100';
                count++;
            }
        });

        // 记录已保存
        savedList.push(currentValue);
        GM_setValue('pj_saved', savedList.join(','));

        log(`📝 [${savedList.length}/${totalCourses}] "${courseName}" → ${count}项全100，正在保存...`);

        // 延迟点击保存（等 DOM 更新）
        setTimeout(() => {
            clickButton('保存');
        }, 400);

    }, DELAY);

    // ---------- 工具函数 ----------

    function clickButton(text) {
        // ASP.NET 的按钮可能是 <input type="submit"> 或 <a href="javascript:__doPostBack">
        const inputs = document.querySelectorAll('input[type="submit"]');
        for (const inp of inputs) {
            if (inp.value && inp.value.indexOf(text) !== -1) {
                inp.click();
                return true;
            }
        }
        const links = document.querySelectorAll('a');
        for (const link of links) {
            if (link.textContent && link.textContent.indexOf(text) !== -1) {
                link.click();
                return true;
            }
        }
        return false;
    }

    function log(msg) {
        console.log('[自动评教]', msg);
        // 页面右上角浮动提示
        let div = document.getElementById('pj_toast');
        if (!div) {
            div = document.createElement('div');
            div.id = 'pj_toast';
            div.style.cssText =
                'position:fixed;top:12px;right:12px;background:#2e7d32;color:#fff;' +
                'padding:10px 16px;border-radius:6px;z-index:99999;font-size:14px;' +
                'box-shadow:0 2px 12px rgba(0,0,0,.3);max-width:420px;';
            document.body.appendChild(div);
        }
        div.textContent = msg;
    }

})();
