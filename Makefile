main: main.cpp
	g++ -O3 -std=c++2a main.cpp -o main.app && ./main.app

clean:
	rm -rf *.app