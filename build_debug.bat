@echo off
del bin\debug.exe
del bin\res.res
del bin\tools.exe
cl /Tc"src/tools/map_to_c.c" /Fe"bin/map_to_c.exe" /Fo"bin/map_to_c.obj" /Fd"bin/map_to_c.pdb" /Od /Zi
"bin/map_to_c.exe" a b c
rc /fo"bin/res.res" "src/res.rc"
cl /Tc"src/main.c" /Fe"bin/debug.exe" /Fo"bin/debug.obj" /Fd"bin/vc40.pdb" /Od /Zi /link "bin/res.res"
"bin/debug.exe"