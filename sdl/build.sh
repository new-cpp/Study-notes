

file="$1.cpp"
echo $file
g++ -std=c++17 -o test.exe "$1.cpp" -I "C:\mingw32\include" -L "C:\mingw32\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
