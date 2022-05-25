CC = g++ -std=c++11

all: categorize

categorize: categorize.cpp
	$(CC) categorize.cpp -o categorize

run:
	./categorize trainingSet.txt preprocessed_train.txt 

clean:
	rm -f categorize