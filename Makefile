CC = g++ -std=c++11

all: categorize

categorize: categorize.cpp kb.cpp
	$(CC) categorize.cpp kb.cpp -o categorize

run:
	./categorize trainingSet.txt preprocessed_train.txt testSet.txt preprocessed_test.txt

clean:
	rm -f categorize preprocessed_train.txt