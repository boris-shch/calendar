del *.exe
windres calendar.rc -F pe-i386 -o calendar.res -O coff
g++ -o calendar.exe -std=c++11 -Wall calendar.res calendar.cpp -m32 -mwindows -lComctl32 -static-libgcc
move calendar.exe calendar_32.exe
windres calendar.rc -o calendar.res -O coff
g++ -o calendar.exe -std=c++11 -Wall calendar.res calendar.cpp -mwindows -lComctl32 -static-libgcc
move calendar.exe calendar_64.exe
