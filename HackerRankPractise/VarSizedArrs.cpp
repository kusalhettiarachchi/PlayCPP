#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int length, queries;

    string line;
    int number;

    getline(cin, line);
    istringstream iss(line);
    iss >> length;
    iss >> queries;

    vector<vector<int> > Xs;
    vector<int> X;
    vector<int> Y;

    int sLength;

    for(int i=0 ; i<length ; ++i){
        vector<int> Ys;
        getline(cin, line);
        istringstream iss(line);
        iss >> sLength;
        while (iss >> number) {
            Ys.push_back(number);
        }
        Xs.push_back(Ys);
    }

    int x, y;
    for(int j=0 ; j<queries ; ++j){
        scanf("%d %d", &x, &y);
        X.push_back(x);
        Y.push_back(y);
    }
    int a, b = 0;

    for(int k=0; k < queries; ++k){
        a = X[k];
        b = Y[k];
        cout << Xs.at(a).at(b) << endl;
    }
    return 0;
}

