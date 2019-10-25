//
// Created by hkusal on 2019-10-23.
//
#include <regex>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

void TokenizeLines(const vector<string>& pHRMLLines, vector<string> &tokens);

void ProcessQuery(const vector<string>& pTokenizedHRML, const string& pQuery);

int main() {
    int l, q;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> l;
    iss >> q;

    vector<string> lines;
    vector<string> queries;

    for(int i=0 ; i<l ; ++i){
        getline(cin, line);
        lines.push_back(line);
    }

    for(int j=0 ; j<q ; ++j){
        getline(cin, line);
        queries.push_back(line);
    }

//    vector<string> &rLines   = lines;
//    vector<string> &rQueries = queries;

    vector<string> tokenizedHRML;
//    vector<string> * ptokenizedHRML = tokenizedHRML;

    TokenizeLines(lines, tokenizedHRML);
//    vector<char*> &rtokenizedHRML = tokenizedHRML;

    for(int k=0; k < q; ++k){
        ProcessQuery(tokenizedHRML, queries.at(k));
    }
    return 0;
}

void ProcessQuery(const vector<string>& pTokenizedHRML, const string& pQuery) {
    char query[pQuery.size()];
    strcpy(query, pQuery.c_str());
    char* token = strtok(query, ".~");
    vector<char*> tags;
    while (token != nullptr){
        tags.push_back(token);
        token = strtok(nullptr, ".~");
    }
    // get the attribute
    char *attribute = tags.back();
    // remove attribute from tag array
    tags.pop_back();

    vector<char*> tagsCopy = tags;
    // iterators
    auto check = tagsCopy.begin();

    // path validating variables
    bool started = false;
    vector<char*> path;
    regex pattern("^(tag)([1-9]+)");

    // start parsing
    for (auto i = pTokenizedHRML.begin(); i != pTokenizedHRML.end() ; ++i) {
        if (started && regex_match(i.base()->c_str(), pattern)){
            path.push_back((char*)i.base()->c_str());
        }
        if (strcmp(i->c_str(), *check.base()) == 0) {
            started = true;
            if (path.empty()){
                path.push_back((char*)i.base()->c_str());
            }
            if (strcmp(*check.base(), attribute) == 0){
                bool clear = true;
                for (size_t a = 0; a < path.size(); a++) {
                    if (strcmp(path[a], tags[a]) != 0) {
                        clear = false;
                    }
                }
                if (clear){
                    cout << (++i)->c_str() << endl;
                } else {
                    cout << "Not Found!" <<endl;
                }
                break;
            } else {
                if (strcmp(*check.base(), tags[tags.size() - 1]) == 0){
                    *check.base() = attribute;
                } else {
                    ++check;
                }
            }
        } else {
            if (strcmp(i->c_str(), pTokenizedHRML[pTokenizedHRML.size() - 1].c_str()) == 0) {
                cout << "Not Found!" <<endl;
                break;
            }
        }
    }
}

void TokenizeLines(const vector<string>& pHRMLLines, vector<string> &tokens) {
    for (const string& pHRMLLine : pHRMLLines) {
        char HRML[pHRMLLine.size()];
        strcpy(HRML, pHRMLLine.c_str());
        vector<char*> tagsInLine;
        char* tag = strtok(HRML, " <=>\"/");
        while (tag != NULL){
            tokens.push_back(tag);
            tag = strtok(NULL, " <=>\"/");
        }
    }
}