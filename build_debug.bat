@echo off
del bin\debug.exe
del bin\res.res
rc /fo"bin/res.res" "src/res.rc"
cl /Tc"src/main.c" /Fe"bin/debug.exe" /Fo"bin/debug.obj" /Fd"bin/vc40.pdb" /Od /Zi /link "bin/res.res"
"bin/debug.exe"