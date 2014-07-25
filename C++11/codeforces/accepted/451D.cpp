//
//  main.cpp
//  451D-Count Good Substrings
//
//  Created by Semih Yavuz on 7/24/14.
//  Copyright (c) 2014 Semih Yavuz. All rights reserved.
//
// Problem: http://codeforces.com/problemset/problem/451/D

#include <iostream>
#include <string>
using namespace std;

#define ll long long

string str;
ll answer[2];
ll a[2];
ll b[2];

void findNumber(string s) {
    
    ll l=s.size();
    
    for (ll i=0;i<l;i++) {
        if (s[i]=='a') {
            a[i%2]++;
            
            if (i%2==0) {
                answer[0]+=a[1];
                answer[1]+=a[0];
            }
            else {
                answer[0]+=a[0];
                answer[1]+=a[1];
            }
        }
        
        else {
            b[i%2]++;
            
            if(i%2==0) {
                answer[0]+=b[1];
                answer[1]+=b[0];
            }
            else {
                answer[0]+=b[0];
                answer[1]+=b[1];
            }
        }
        
    }
}




int main(int argc, const char * argv[])
{
    cin>>str;
    findNumber(str);
    cout<<answer[0]<<" "<<answer[1]<<endl;

    return 0;
}

