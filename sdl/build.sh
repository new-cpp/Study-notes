

file="$1"
echo $file
g++ -std=c++17 -o test.exe "$1" -I "C:\mingw32\include" -L "C:\mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
