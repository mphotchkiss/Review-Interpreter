#include "kb.h"

using namespace std;

kb::kb(vector<string> vocab, vector<vector<int> > features) {
    this->vocab = vocab;
    this->features = features;
}

vector<int> kb::categorize(kb * data) {
    vector<int> results;
    double prob = this->computePositive(1);
    cout << "Probability in training data that positive: " << prob << endl;
    //for each entry in the features, categorize
    for (int i = 0; i < 5; i++) { //data->features.size()
        double probPos = log(prob);
        double probNeg = log(1.0-prob);
        //for each entry in the row (except for the last)
        for (int j = 0; j < data->features[i].size() - 1 ; j++) {
            probPos += log(this->computeVocabGivenPositive(data->vocab[j], data->features[i][j], 1));
            probNeg += log(this->computeVocabGivenPositive(data->vocab[j], data->features[i][j], 0));
        }
        cout << "probPos: " << probPos << endl;
        cout << "probNeg: " << probNeg << endl;
        if (probPos > probNeg) {
            results.push_back(1);
        }
        else {
            results.push_back(0);
        }
    }
    return results;
}

double kb::computeVocabGivenPositive(string word, int present, int pos) {
    int recordsBothTrue = 0;
    bool inVocab = false;
    int column;
    for (int i = 0; i < this->vocab.size(); i++) {
        if (this->vocab[i].compare(word) == 0) {
            inVocab = true;
            column = i;
        }
    }
    if (inVocab) {
        for (int i = 0; i < this->features.size(); i++) {
            if (this->features[i][column] == present && this->features[i].back() == pos)
                recordsBothTrue++;
        }
    }
    double prob = (1+recordsBothTrue)/(this->computePositive(pos)+this->vocab.size());
    //cout << "P(" << word << "=true|positive=" << ((bool) pos) << "):\t" << prob << endl;
    return prob;
}

//computes the probability that a post is positive
double kb::computePositive(int pos) {
    int positive = 0;
    for (int i = 0; i < this->features.size(); i++) {
        if (this->features[i].back() == pos) {
            positive++;
        }
    }
    return positive/((double) this->features.size());
}

vector<string> kb::getVocab() {
    return this->vocab;
}

vector<vector<int> > kb::getFeatures() {
    return this->features;
}