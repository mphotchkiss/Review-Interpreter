#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class kb {
    public:
        kb(vector<string>, vector<vector<int> >);

        double computePositive(int);
        double computeVocabGivenPositive(string, int, int);
        vector<int> categorize(kb *);
        vector<string> getVocab();
        vector<vector<int> > getFeatures();
    private:
        vector<vector<int> > features;
        vector<string> vocab;
};