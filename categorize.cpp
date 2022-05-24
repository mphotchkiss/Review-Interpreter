#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string tolower(string s);

struct sentence {
    bool positive;
    vector<string> feature;
};

int main(int argc, char ** argv) {
    ifstream fstream;
    string sentence;
    vector<struct sentence> sentences;
    fstream.open(argv[1]);
    if (fstream.is_open()) {
        while (getline(fstream, sentence)) {
            vector<string> feature;
            sentence = tolower(sentence);

        }
    }
    return 0;
}

string tolower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}