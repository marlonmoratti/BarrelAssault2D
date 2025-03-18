all:
	g++ -o main main.cpp ./source/*.cpp ./tinyxml2/tinyxml2.cpp -lGL -lGLU -lglut -std=c++17

clean:
	rm main

run: all
	./main
