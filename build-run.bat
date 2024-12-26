@echo off
del /f /q a.exe 2>nul
clang -std=c++20 -Wall -Wextra -Wpedantic main.cpp
if %ERRORLEVEL% EQU 0 (
    .\a.exe
)