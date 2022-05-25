#include "kb.h"

using namespace std;

kb::kb(vector<string> vocab, vector<vector<int> > features) {
    this->vocab = vocab;
    this->features = features;
}

vector<string> kb::getVocab() {
    return this->vocab;
}

vector<vector<int> > kb::getFeatures() {
    return this->features;
}