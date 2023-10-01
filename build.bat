@ECHO OFF

clang main.cpp -o ramp.exe -g -std=c++17 -Lglew -Lglfw -lglew32s -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lmsvcrt
