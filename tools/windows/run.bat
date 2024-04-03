@echo off
g++ %1.cpp -o %1 -std=c++14 -O2 -Wall -Wextra -Dxxzx -Wl,--stack=512000000