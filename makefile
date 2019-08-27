all:
	g++ main.cpp functions.cpp inputParse.cpp -L ./dependencies/ -lcurldll -o cls.exe