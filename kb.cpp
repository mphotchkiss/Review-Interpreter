#include "kb.h"

using namespace std;

kb::kb(vector<string> vocab, vector<vector<int> > features) {
    this->vocab = vocab;
    this->features = features;
}

//computes the probability that a post is positive
double kb::computePositive() {
    int positive = 0;
    for (int i = 0; i < this->features.size(); i++) {
        if (this->features[i].back() == 1) {
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