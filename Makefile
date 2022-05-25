CC = g++ -std=c++11

all: categorize

categorize: categorize.cpp
	$(CC) categorize.cpp -o categorize

clean:
	rm -f categorize