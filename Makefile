all:
	clang++ -O3 -std=c++11 src/*.cpp -o bin/glabel

clean:
	rm bin/glabel
