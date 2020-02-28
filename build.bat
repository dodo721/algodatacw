@echo off
mkdir build
cl fourinarow.c /Fe./build/fourinarow.exe /Fo./build/fourinarow.obj
cd build
fourinarow
cd ..