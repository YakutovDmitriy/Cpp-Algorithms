@echo off

set /a now = 1

:start
gen > test 2> gen_er
call :check re gen

stupid < test > stupid_out 2> stupid_er
call :check re stupid

a < test > a_out 2> a_er
call :check test found: re

fc a_out stupid_out > diff
call :check test found: wa

echo ok %now%
set /a now = 1 + %now%

goto start

:check
if errorlevel 1 (
    echo %*
    exit
)
exit /b 0
