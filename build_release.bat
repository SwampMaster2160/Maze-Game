@echo off
del bin\release.exe
del bin\res.res
rc /fo"bin/res.res" "src/res.rc"
cl /Tcsrc/main.c /Fe"bin/release.exe" /Fo"bin/release.obj" /O2 /link "bin/res.res"
"bin/release.exe"