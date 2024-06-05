@echo off
del bin\debug.exe
del bin\res.res
del bin\room_to_c.exe
cl /Tc"src/tools/room_to_c.c" /Fe"bin/room_to_c.exe" /Fo"bin/room_to_c.obj" /Fd"bin/room_to_c.pdb" /Od /Zi
"bin/room_to_c.exe" src/rooms.map bin/rooms.c
rc /fo"bin/res.res" "src/res.rc"
cl /Tc"src/main.c" /Fe"bin/debug.exe" /Fo"bin/debug.obj" /Fd"bin/vc40.pdb" /Od /Zi /link "bin/res.res"
"bin/debug.exe"