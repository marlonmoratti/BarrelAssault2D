all:
	g++ -o main main.cpp ./source/*.cpp ./tinyxml2/tinyxml2.cpp -lGL -lGLU -lglut
