# Простой make-file без переменных, для релиза и дебага

.PHONY: all debug release clean

all: debug release

debug: hello-dbg

hello-dbg: main.cpp
	g++ -g -O0 main.cpp -o hello-dbg -Wall

release: hello

clean:
	rm -f hello hello-dbg

hello: main.cpp
	g++ -O2 main.cpp -o hello -DNDEBUG -Wall
