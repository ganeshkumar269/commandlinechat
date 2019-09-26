LIBS = -lcurldll
INCLUDE_DIR = -I./dependencies/include/
LIB_DIR = -L./dependencies/lib/
LOCAL_INCLUDE_DIR = -I./include/



all:
	mingw32-g++.exe -Wall -std=c++14 main.cpp functions.cpp inputParse.cpp -L ./dependencies/ -lcurldll -o clc.exe