//
//  main.cpp
//  Round 257.E Jzzhu and Apples
//
//  Created by Semih Yavuz on 7/20/14.
//  Copyright (c) 2014 Semih Yavuz. All rights reserved.
//

// Problem: http://codeforces.com/problemset/problem/449/C

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
using namespace std;

vector <int> primes;
vector <vector <int> > mults;
bool* flag;
bool* flag2;
stack<int> st;

int n;
int summand;

void load1() {
    primes.push_back(2);
    primes.push_back(3);
    int cur;
    bool check;
    for (int i=5; i<=n;i=i+2) {
        check=true;
        for (cur=0; primes[cur]*primes[cur]<=i && cur<primes.size();cur++) {
            if (i%primes[cur]==0) {
                check=false;
                break;
            }
        }
        if (check)
            primes.push_back(i);
    }
}

void load2() {
    flag=new bool[n+1];
    for (int i=0;i<=n;i++)
        flag[i]=false;
    for (int i=0;i<primes.size();i++) {
        vector<int> current;
        current.push_back(primes[i]);
        flag[primes[i]]=true;
        for (int j=primes[i];j*primes[i]<=n;j++) {
            if (!flag[j*primes[i]]) {
                current.push_back(j*primes[i]);
                flag[j*primes[i]]=true;
            }
        }
        mults.push_back(current);
    }
}

int find() {
    flag2=new bool[n+1];
    for (int i=0;i<=n;i++)
        flag2[i]=false;
    int res=0;
    for (int i=1;i<mults.size();i++) {
        if (mults[i].size()%2==0) {
            res=res+(int)(mults[i].size()/2);
        }
        else {
            res=res+(int)(mults[i].size()/2);
            if (2*primes[i]<=n) {
                st.push(i);
                flag2[2*primes[i]]=true;
            }
        }
    }
    
    int tot=(int)st.size();
    int multiplesOfTwo=(int)mults[0].size();
    summand=multiplesOfTwo-tot;
    
    res=res+tot+(summand/2);
    
    return res;
}


void print() {
    int m= find();
    cout<<m<<endl;
    int cur;
    while (!st.empty()) {
        cur=st.top();
        cout<<2*primes[cur]<<" "<<mults[cur][(int)(mults[cur].size())-1]<<endl;
        st.pop();
    }
    
    int len;
    for (int i=1;i<mults.size();i++) {
        if (mults[i].size()%2==0)
            len=(int)mults[i].size();
        else
            len=(int)mults[i].size()-1;
        
        for (int j=0;j<len;j=j+2) {
            cout<<mults[i][j]<<" "<<mults[i][j+1]<<endl;
        }
    }
    
    int k;
    if (summand%2==0) {
        k=0;
    }
    else {
        k=1;
    }
        
    
    while (k<mults[0].size()) {
        while (flag2[mults[0][k]])
            k++;
        
        if (k<mults[0].size()) {
            cout<<mults[0][k]<<" ";
        }
        k++;
            
        while (flag2[mults[0][k]])
            k++;
            
        if (k<mults[0].size()) {
            cout<<mults[0][k]<<endl;
        }

        k++;
    }
}


int main(int argc, const char * argv[])
{
    cin>>n;
    load1();
    load2();
    print();
    
    return 0;
 
}

