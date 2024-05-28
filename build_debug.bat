@echo off
del "bin/debug.exe"
cl /Tc"src/main.c" /Fe"bin/debug.exe" /Fo"bin/debug.obj" /Fd"bin/vc40.pdb" /Od /Zi
"bin/debug.exe"