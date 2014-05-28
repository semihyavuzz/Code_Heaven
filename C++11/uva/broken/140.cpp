// UVA 140
// Permutation.
// Wrong Answer.

#include <iostream>
#include <string>
#include <list>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

#define MAX_NV 8
#define MAX_L 26

bool    edges[MAX_NV][MAX_NV];
int     map[MAX_L];
int     rmap[MAX_NV];

int     min_bandwidth;
string  min_order;

void split(string &s, char delim, list<string>& l) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        l.push_back(item);
    }
}

int toi(char c) {
    return c - 'A';
}

int calc_bandwidth(int order[MAX_NV], int n) {
    int max = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(edges[order[i]][order[j]] && max < abs(i-j)) {
                max = abs(i-j);
            }
        }
    }
    return max;
}

void backtrack(int order[MAX_NV], bool used[MAX_NV], int k, int n) {
    if(k == n) {
        int bandwidth = calc_bandwidth(order, n);
        if(bandwidth <= min_bandwidth) {
            stringstream ss;
            for(int i = 0; i < n; i++) {
                ss << (char)('A' + rmap[order[i]]);
                ss << " ";
            }
            ss << "-> " << bandwidth;
            
            string result = ss.str();
            
            if(bandwidth < min_bandwidth || result < min_order) {
                min_bandwidth = bandwidth;
                min_order = ss.str();
            }
        }
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(!used[i]) {
            order[k] = i;
            used[i] = true;
            backtrack(order, used, k + 1, n);
            used[i] = false;
        }
    }
    
}

int main() {
    string graph;
    bool first = true;
    while(cin >> graph && graph != "#") {
        if(!first) cout << endl;
        else first = false;
        for(int i = 0; i < MAX_NV; i++) {
            rmap[i] = -1;
            for(int j = 0; j < MAX_NV; j++)
                edges[i][j] = false;
        }
        
        for(int i = 0; i < MAX_L; i++) {
            map[i] = -1;
        }
        
        graph.erase(std::remove_if( graph.begin(), graph.end(),
                               [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), graph.end() );
        
        min_bandwidth = 100;
        int nVertices = 0;
        list<string> records;
        split(graph, ';', records);
        
        for(list<string>::iterator it = records.begin(); it != records.end(); it++) {
            string s = *it;
            int v = toi(s[0]);
            map[v] = nVertices;
            rmap[nVertices] = v;
            nVertices++;
        }
        
        for(list<string>::iterator it = records.begin(); it != records.end(); it++) {
            string s = *it;
            int v = toi(s[0]);
            for(int i = 2; i < s.length(); i++) {
                int y = toi(s[i]);
                if(map[y] == -1) {
                    map[y] = nVertices;
                    rmap[nVertices] = y;
                    nVertices++;
                }
                edges[map[v]][map[y]] = true;
                edges[map[y]][map[v]] = true;
            }
        }
        
        int order[MAX_NV];
        bool used[MAX_NV];
        
        backtrack(order, used, 0, nVertices);
        cout << min_order;
    }
    return 0;
}