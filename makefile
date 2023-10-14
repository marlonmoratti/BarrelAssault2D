all:
	g++ -o trabalhocg main.cpp ./source/*.cpp ./tinyxml2/tinyxml2.cpp -lGL -lGLU -lglut

clean:
	rm trabalhocg

run: all
	./trabalhocg
