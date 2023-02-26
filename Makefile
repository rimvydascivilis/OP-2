main: main.cpp
	g++ -std=c++2a main.cpp -o main.app && ./main.app

clean:
	rm -rf *.app