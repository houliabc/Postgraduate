# Daily auto-commit script for study notes
# Runs via Windows Task Scheduler, triggered daily at 21:00

$ErrorActionPreference = "Stop"

# Detect repo root (parent of the scripts/ folder containing this script)
$REPO_PATH = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$HOME_DIR  = "$env:USERPROFILE"

# =========== Env (SSH) ===========
$env:HOME = $HOME_DIR
$env:SKIP_SSH_ASKPASS = "1"
$env:GIT_SSH_COMMAND = "ssh -i $HOME_DIR\.ssh\id_rsa -o StrictHostKeyChecking=no"

# =========== Enter repo ===========
Set-Location $REPO_PATH

# =========== Safe pull (stash first) ===========
$hasLocal = $null -ne (git status --porcelain)
if ($hasLocal) {
    git stash push -m "auto-commit: temp stash" 2>$null
}
try {
    git pull origin main --rebase 2>&1 | Out-Null
} catch { }
if ($hasLocal) {
    git stash pop 2>$null
}

# =========== Generate daily log ===========
$today     = Get-Date -Format "yyyy-MM-dd"
$logDir    = Join-Path $REPO_PATH "daily-logs"
$dailyFile = Join-Path $logDir "$today.md"

if (-not (Test-Path $logDir)) {
    New-Item -ItemType Directory -Path $logDir -Force | Out-Null
}

if (-not (Test-Path $dailyFile)) {
    $weekdayMap = @{
        0 = "Sun"; 1 = "Mon"; 2 = "Tue"; 3 = "Wed"
        4 = "Thu"; 5 = "Fri"; 6 = "Sat"
    }
    $dow = $weekdayMap[[int](Get-Date).DayOfWeek]

    $content = "# $today ($dow)`n`n## Study`n`n-`n`n## Tomorrow`n`n-`n"
    Set-Content -Path $dailyFile -Value $content -Encoding UTF8
    Write-Host "Generated daily log: $today.md"
}

# =========== Commit & Push ===========
git add .

$status = git status --porcelain
if ($status) {
    $commitMsg = "$today daily checkpoint"
    git config user.email "houliabc@gmail.com"
    git config user.name "houliabc"
    git commit -m $commitMsg
    git push origin main
    Write-Host "Committed: $commitMsg"
}
else {
    Write-Host "No changes, skipping."
}
