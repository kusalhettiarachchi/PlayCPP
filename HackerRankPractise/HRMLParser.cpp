//
// Created by hkusal on 2019-10-28.
//
#include <string>
#include <vector>
#include <iostream>
#include <regex>

using namespace std;

//const regex startPattern("^(<).+");
//const regex endPattern("^(</).+");

void Tagify(string *query, string& tag, int& pointer);

string LocateValue(const string& hrml, const string& attribute);

bool ValidatePath(vector<int> vector1, vector<int> vector2, bool &attributeIsNotNested);

string ExtractVal(string valString);

int main() {
    int l, q;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> l;
    iss >> q;

    string hrml;

    vector<string> queries;

    for(int i=0 ; i<l ; ++i){
        getline(cin, line);
        hrml += line;
    }

    for(int j=0 ; j<q ; ++j){
        getline(cin, line);
        queries.push_back(line);
    }

    for (auto m = queries.begin(); m < queries.end(); ++m) {
        int pointer = 0;
        bool attrThis = false;

        string query = *m;
        string tag;

        vector<int> openP;
        vector<int> closeP;

        while (pointer < query.size()){
            Tagify(&query, tag, pointer);
            attrThis = pointer == query.size();

            if (attrThis) {
                int parentTagStart = openP.back();

                int open = hrml.find(tag);
                openP.push_back(open);
                int close = hrml.find(tag);
                closeP.push_back(close);

                string betweenLastTagAndAttribute = hrml.substr(parentTagStart + 1, open - parentTagStart);
                bool attrIsNotNested = count(betweenLastTagAndAttribute.begin(), betweenLastTagAndAttribute.end(), '<') == 0;

                string val;
                bool validPath = ValidatePath(openP, closeP, attrIsNotNested);
                if (validPath) {
                    val = LocateValue(hrml, tag);
                } else {
                    val = "Not Found!";
                }
                cout << val << endl;
            } else {
                int open = hrml.find("<" + tag);
                openP.push_back(open);
                int close = hrml.find("</" + tag);
                closeP.push_back(close);
            }
        }
    }

    return 0;
}

bool ValidatePath(vector<int> vector1, vector<int> vector2, bool &attributeIsNotNested) {
    return is_sorted(vector1.begin(), vector1.end()) && is_sorted(vector2.rbegin(), vector2.rend()) && attributeIsNotNested;
}

string LocateValue(const string& hrml, const string& attribute) {
    int start = hrml.find_first_of('=', hrml.find(attribute));
    istringstream iss(hrml.substr(start + 3));
    string val;
    char c;
    while(iss >> c){
        if (isalnum(c)){
            val += c;
        } else {
            break;
        }
    }
    return val;
}


void Tagify(string *query, string& tag, int& pointer) {
    istringstream iss((*query).substr(pointer));
    char c;
    tag = "";
    // This line
    while (iss >> c) {
        ++pointer;
        if (isalnum(c)){
            tag += c;
        } else {
            break;
        }
    }
}


