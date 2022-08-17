# Review-Interpreter

A program that recieves reviews (as in Yelp, for example) as input and outputs the positive/negative status of the review by leveraging a Naive Bayes Classifier and training data.

## What I learned

### Naive Bayes Classifiers
- assuming conditional independence
- identifying features/attributes
- stabilizing floating points using logarithms
- using the Uniform Dirichlet Priors equation to fill gaps
- drawing conclusions with probabalistic inference

### Other challenges
- abstracting a knowledge base representation into a class
- utilizing class methods to define the interaction of two objects

## How to use

### Overview
A naive bayes classifier relies on a training set of data from which to draw conclusions on the test set. As such, the repository includes a test set and a training set of data. The purpose of the project was to reflect the effectiveness of classification; Both the training and test sets have 0's and 1's to denote negativity and positivity, respectively, although traditionally a naive bayes classifier would be used to classify data that is not yet determined to be positive or negative. For these reasons, this is more a proof of concept in the way the program is run, but with a little repurposing the classifier could be configured to accept a review and compute its positivity/negativity on the fly. Ultimately, the purpose of the project was to test the effectiveness of a classifier, as outlined in the explanation of outputs.

### Running
Note: These instructions assume that C++ is available on the hardware device running the program

Compile the code and generate the `categorize` executable
```bash
make
``` 

Run the program, passing in the training set as the training data and the test set as the test data. The 2nd and 4th arguments are the names of the processed files (in other words, these are the intermediary forms of the information that's been processed).
```bash
./categorize trainingSet.txt processedTraining.txt testSet.txt processedTest.txt
```
### Output
The program will generate a number of output files...
#### results.txt
This is the primary results file that matters. These are the computed accuracies of classification for two different scenarios. The first of which is the classifier working on its own training data, and the second is the classifier working on the test data set.

#### processedTraining.txt
This is the intermediary form of information mentioned above which represents the training set. This step is important for visualizing the knowledge base used by the classifier. Think of it as a table represented in a text file. The first row is the column labels, each a word. Each subsequent row represents an entry in the training data, where each column in that row denotes the presence or absence of the word for that given the column. The last column in each row represents the positivity/negativity.

#### processedTesting.txt
Again, an intermediary form of representing the information in the testing set. The format is the same as the processed training data. Note that the program does not use this file as the knowledge base, although theoretically the inputs could be changed such that it does within the scope of this project's functionality.

