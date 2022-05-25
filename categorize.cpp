#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

string tolower(string s);

struct sentence {
    bool positive;
    vector<string> feature;
};

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

int main(int argc, char ** argv) {
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
                    feature.push_back(temp);
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
    vector<vector<int>> sentences;
    fstream.open(argv[1]);
    if (fstream.is_open()) {
        while (getline(fstream, sentence)) {
            unordered_map<string, bool> checkSentence;
            int positive = 0;
            sentence = tolower(sentence);
            string temp = "";
            for(int i = 0; i < sentence.length(); i++) {
                if (sentence[i] == ' ') {
                    temp.erase(remove_if(temp.begin(), temp.end(), ::ispunct), temp.end());
                    checkSentence.insert(pair<string,bool>(temp, true));
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
    
    return 0;
}