@echo off

set /a now = 1

:start
gen > test 2> gen_er
if errorlevel 1 (
    echo re gen
    exit
)

stupid < test > stupid_out 2> stupid_er
if errorlevel 1 (
    echo re stupid
    exit
)

a < test > a_out 2> a_er
if errorlevel 1 (
    echo test found: re
    exit
)

fc a stupid > diff
if errorlevel 1 (
    echo test found: wa
    exit
)

echo ok %now%
set /a now = 1 + %now%

goto start
