@echo off
g++ %1.cpp -o %1 -std=c++14 -O2 -Wall -Wextra -Wl,--stack=512000000 -Dxxzx
%1.exe <"%1%2".in >"%1%2".txt
fc /w "%1%2".out "%1%2".txt