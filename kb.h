#include <vector>
#include <string>

using namespace std;

class kb {
    public:
        kb(vector<string>, vector<vector<int> >);

        vector<string> getVocab();
        vector<vector<int> > getFeatures();
    private:
        vector<vector<int> > features;
        vector<string> vocab;
};