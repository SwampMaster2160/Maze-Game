@echo off
del bin\release.exe
del bin\res.res
del bin\room_to_c.exe
cl /Tc"src/tools/room_to_c.c" /Fe"bin/room_to_c.exe" /Fo"bin/room_to_c.obj" /Fd"bin/room_to_c.pdb" /Od /Zi
"bin/room_to_c.exe" src/rooms.map bin/rooms.c
rc /fo"bin/res.res" "src/res.rc"
cl /Tcsrc/main.c /Fe"bin/release.exe" /Fo"bin/release.obj" /O2 /link "bin/res.res"
"bin/release.exe"