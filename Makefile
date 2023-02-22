array:
	g++ -std=c++2a array.cpp -o array.app && ./array.app

vector:
	g++ -std=c++2a vector.cpp -o vector.app && ./vector.app

clean:
	rm -rf *.app