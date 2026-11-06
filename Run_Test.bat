@echo off
cd /d "%~dp0"
echo ===== Search for FAILED =====
log_parser.exe security.log FAILED
echo.
echo ===== Search for 404 =====
log_parser.exe security.log 404
echo.
pause
