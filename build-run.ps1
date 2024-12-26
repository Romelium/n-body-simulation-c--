Remove-Item -Force -ErrorAction SilentlyContinue .\a.exe
& clang -std=c++20 -Wall -Wextra -Wpedantic main.cpp
if ($?) { .\a.exe }