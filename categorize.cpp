#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "kb.h"

using namespace std;

string tolower(string);
bool compareFunction(string, string);
vector<string> remove_repeats(vector<string>);
kb * process_file(char *, char *);
void print_results(kb * trained, kb * test, vector<int> training_results, vector<int> testing_results);

int main(int argc, char ** argv) {
    kb * trained = process_file(argv[1], argv[2]);
    kb * test = process_file(argv[3], argv[4]);
    vector<int> training_results = trained->categorize(trained);
    vector<int> testing_results = trained->categorize(test);
    print_results(trained, test, training_results, testing_results);
    return 0;
}

void print_results(kb * trained, kb * test, vector<int> training_results, vector<int> testing_results) {
    ofstream fout;
    fout.open("results.txt");
    int number_correct = 0;
    int total_sentences = trained->getFeatures().size();
    for (int i = 0; i < training_results.size(); i++) {
        if (training_results[i] == trained->getFeatures()[i][trained->getFeatures()[i].size() - 1]) {
            number_correct++;
        }
    }
    double percentage = 100 * ((double)number_correct / (double)total_sentences);
    fout << "Training Set:" << endl;
    fout << "Training done using trainingSet.txt, which is processed and stored in preprocessed_train.txt as per the command line arguments in the Makefile. The information from this processing is then used for testing on the training set." << endl;
    fout << "Percentage of training data sentences correctly classified: " << percentage << "%" << endl;
    fout << endl;
    number_correct = 0;
    total_sentences = test->getFeatures().size();
    for (int i = 0; i < testing_results.size(); i++) {
        if (testing_results[i] == test->getFeatures()[i][test->getFeatures()[i].size() - 1]) {
            number_correct++;
        }
    }
    percentage = 100 * ((double)number_correct / (double)total_sentences);
    fout << "Testing Set:" << endl;
    fout << "Training done using trainingSet.txt. Testing is done by preprocessing testSet.txt and uses the same values as seen in preprocessed_test.txt." << endl;
    fout << "Percentage of testing data sentences correctly classified: " << percentage << "%" << endl;
}

kb * process_file(char * in, char * out) {
    ifstream fstream;
    ofstream fout;
    string sentence;
    vector<string> feature;
    fstream.open(in);
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
    fstream.open(in);
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
    fout.open(out);
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
    kb * knowledgeBase = new kb(feature, sentences);
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