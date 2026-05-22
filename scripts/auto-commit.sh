#!/bin/bash
# 考研每日自动打卡脚本（Git Bash / WSL 用）
# 用法: bash scripts/auto-commit.sh

set -e

REPO_PATH="/d/0_考研"
cd "$REPO_PATH"

# 拉取远端最新
git pull origin main --rebase 2>/dev/null || true

# 写入每日学习记录
TODAY=$(date '+%Y-%m-%d')
NOW=$(date '+%Y-%m-%d %H:%M:%S')
LOG_DIR="学习日志"
DAILY_FILE="$LOG_DIR/$TODAY.md"

mkdir -p "$LOG_DIR"

# 如果今天没有手动记笔记，自动生成一个最小的打卡文件
if [ ! -f "$DAILY_FILE" ]; then
    WEEKDAY=$(date '+%A')
    case "$WEEKDAY" in
        Monday)    CN="星期一" ;;
        Tuesday)   CN="星期二" ;;
        Wednesday) CN="星期三" ;;
        Thursday)  CN="星期四" ;;
        Friday)    CN="星期五" ;;
        Saturday)  CN="星期六" ;;
        Sunday)    CN="星期日" ;;
    esac

    cat > "$DAILY_FILE" << EOF
# $TODAY $CN

## 今日学习内容

-

## 明日计划

-
EOF

    echo "生成每日打卡文件: $DAILY_FILE"
fi

# 提交 & 推送
git add .

if [ -n "$(git status --porcelain)" ]; then
    COMMIT_MSG="$TODAY 学习打卡"
    git config user.email "houliabc@gmail.com"
    git config user.name "houliabc"
    git commit -m "$COMMIT_MSG"
    git push origin main
    echo "提交成功: $COMMIT_MSG"
else
    echo "无变更，跳过提交"
fi
