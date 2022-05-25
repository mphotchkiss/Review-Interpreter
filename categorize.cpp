#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string tolower(string);
bool compareFunction(string, string);
vector<string> remove_repeats(vector<string>);
struct kb process_file(int, char **);

struct kb {
    vector<vector<int> > features;
    vector<string> vocab;
};

int main(int argc, char ** argv) {
    struct kb knowledgeBase = process_file(argc, argv);
    
    return 0;
}

struct kb process_file(int argc, char ** argv) {
    struct kb knowledgeBase;
    ifstream fstream;
    ofstream fout;
    string sentence;
    vector<string> feature;
    fstream.open(argv[1]);
    if (fstream.is_open()) {
        while (getline(fstream, sentence)) {

            sentence = tolower(sentence);
            string temp = "";
            for(int i = 0; i < sentence.length(); i++) {
                if (sentence[i] == ' ') {
                    temp.erase(remove_if(temp.begin(), temp.end(), ::ispunct), temp.end());
                    if (temp != "") {
                        feature.push_back(temp);
                    }
                    temp = "";
                }
                else if (sentence[i] == '\t') {
                    break;
                }
                else {
                    temp += sentence[i];
                }
            }
            sort(feature.begin(), feature.end(), compareFunction);
            feature = remove_repeats(feature);
            feature.push_back("classlabel");
        }
    }
    fstream.close();
    vector<vector<int> > sentences;
    fstream.open(argv[1]);
    if (fstream.is_open()) {
        while (getline(fstream, sentence)) {
            map<string, bool> checkSentence;
            int positive = 0;
            sentence = tolower(sentence);
            string temp = "";
            for(int i = 0; i < sentence.length(); i++) {
                if (sentence[i] == ' ') {
                    temp.erase(remove_if(temp.begin(), temp.end(), ::ispunct), temp.end());
                    if (temp != "") {
                        checkSentence.insert(pair<string,bool>(temp, true));
                    }
                    temp = "";
                }
                else if (sentence[i] == '\t') {
                    if (sentence[i+2] == '1') {
                        positive = 1;
                    }
                    break;
                }
                else {
                    temp += sentence[i];
                }
            }
            vector<int> sentenceVector;
            for (int i = 0; i < feature.size() - 1; i++) {
                if (checkSentence.count(feature[i])) {
                    sentenceVector.push_back(1);
                }
                else {
                    sentenceVector.push_back(0);
                }
            }
            sentenceVector.push_back(positive);
            sentences.push_back(sentenceVector);
        }
    }
    fstream.close();
    fout.open(argv[2]);
    if (fout.is_open()) {
        for (int i = 0; i < feature.size() - 1; i++) {
            fout << feature[i] << ",";
        }
        fout << feature[feature.size() - 1];
        fout << endl;
        for(int i = 0; i < sentences.size(); i++) {
            for (int j = 0; j < sentences[i].size() - 1; j++) {
                fout << sentences[i][j] << ",";
            }
            fout << sentences[i][sentences[i].size() - 1];
            fout << endl;
        }
    }
    knowledgeBase.vocab = feature;
    knowledgeBase.features = sentences;
    return knowledgeBase;
}


string tolower(string s) {
    for_each(s.begin(), s.end(), [](char & c) {
        c = ::tolower(c);
    });
    return s;
}

bool compareFunction(string s1, string s2) {
    return s1 < s2;
}

vector<string> remove_repeats(vector<string> words) {
    for (int i = 1; i < words.size(); i++) {
        if (words[i] == words[i-1]) {
            words.erase(words.begin() + i);
        }
    }
    return words;
}