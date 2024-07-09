
# wsl : build 
# file="$1"
# echo $file
# g++ -std=c++17 -o test.exe "$1" -I "C:\migw32\include" -L "C:\mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
#
#
#windows build

echo "build"

cmake --preset=default -DFILENAME="$1"
cmake --build build

echo "execute"
./build/Debug/main.exe
