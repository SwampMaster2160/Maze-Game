@echo off
del "bin/release.exe"
cl /Tcsrc/main.c /Fe"bin/release.exe" /Fo"bin/release.obj" /O2
"bin/release.exe"