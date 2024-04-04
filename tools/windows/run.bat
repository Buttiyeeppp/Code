@echo off
g++ %1.cpp -o %1 -std=c++14 -O2 -Wall -Wextra -Wl,--stack=512000000 -Dxxzx
%1.exe