// UVA 110
// Simulating Insertion Sort with backtracking.
// Accepted

#include <iostream>
#include <list>
#include <iterator>
#include <string>

#define PROGRAM     "program sort(input,output);\n"
#define VAR         "var\n"
#define INTEGER     " : integer;\n"
#define BEGIN       "begin\n"
#define READLN      "readln"
#define WRITELN     "writeln"
#define END         "end."

#define PRINT_IF(a,b, lvl)          (cout << string((lvl-1)*2, ' ') << "if " << a << " < " << b << " then\n")
#define PRINT_ELSE(lvl)             (cout << string((lvl-1)*2, ' ') << "else\n")
#define PRINT_IF_ELSE(a,b,lvl)      (cout << string((lvl-1)*2, ' ') << "else if " << a << " < " << b << " then\n")

using namespace std;

void insert(list<char>& a, int lvl, int n) {
    if(lvl < n) {
        for(auto it = a.end();; it--) {
            char currChar = (char)('a' + lvl);
            if(a.size()) {
                if(it == a.end())
                    PRINT_IF(*prev(it), currChar, lvl);
                else if(it == a.begin())
                    PRINT_ELSE(lvl);
                else
                    PRINT_IF_ELSE(*prev(it), currChar, lvl);
            }
            
            auto newIt = a.insert(it, (char)('a' + lvl));
            lvl++;
            insert(a, lvl, n);
            lvl--;
            a.erase(newIt);
            
            if(it == a.begin())
                break;
        }
        
    }
    else {
        cout << string((lvl-1)*2, ' ');
        cout << WRITELN << "(";
        for(auto it = a.begin(); it != a.end(); it++) {
            if(it != a.begin()) cout << ",";
            cout << *it;
        }
        cout << ")" << endl;
    }
        
}

void comma_sep_vars(int nVars) {
    for(int i = 0; i < nVars; i++) {
        if(i) cout << ",";
        cout << (char)('a' + i);
    }
}

void solve() {
    int nVars;
    cin >> nVars;
    
    list<char> v;
    
    cout << PROGRAM << VAR;
    comma_sep_vars(nVars);
    cout << INTEGER << BEGIN;
    cout << READLN << "(";
    comma_sep_vars(nVars);
    cout << ");" << endl;
    insert(v, 0, nVars);
    cout << END << endl;
}

int main() {
    int nCases;
    cin >> nCases;
    for(int i = 0; i < nCases; i++) {
        if(i) cout << endl;
        solve();
    }
    return 0;
}

