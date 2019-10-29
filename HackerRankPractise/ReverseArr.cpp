//
// Created by hkusal on 2019-10-25.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <istream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
//    int l;
//    scanf("%d\n\r", &l);
//    int arr[l];
//
//    string nums;
//    // scanf("%s", &nums);
//    getline(cin, nums);
//    istringstream iss(nums);
//    int n;
//    int p = 0;
//    while(iss >> n) {
//        arr[p++] = n;
//    }
//    while(--p > -1){
//        cout << arr[p] << " ";
//    }

    int a,b,c;
    b = 101011;
    c = 101011;
    bool d = b^c;
    cout << BoolToString(d);

    return 0;
}

