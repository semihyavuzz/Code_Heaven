// UVA 129
// Permutation.
// Accepted

#include <iostream>
#include <cmath>

using namespace std;

char seq[80];
bool finished = false;
int _count;

bool check(int k) {
    for(int i = 1; i <= (k / 2); i++) {
        bool same = true;
        for(int j = k - 1; j > k - i - 1; j--) {
            if(seq[j] != seq[j - i]) {
                same = false;
                break;
            }
        }
        if(same)
            return false;
    }
    return true;
}

int backtrack(int k, int n, int L) {
    int result = 0;
    for(int i = 0; i < L; i++) {
        seq[k] = (char)('A' + i);
        if(check(k + 1)) {
            _count++;
            if(_count == n) {
                result = k + 1;
                break;
            }
            result = backtrack(k + 1, n, L);
            if(result)
                break;
        }
    }
    
    return result;
}

void solve(int n, int L) {
    _count = 0;
    int k = backtrack(0, n, L);
    int size = k;
    
    for(int i = 0; i < k; i++) {
        if(i && !(i % 64)) cout << endl;
        else if(i && !(i % 4)) cout << " ";
        cout << seq[i];
    }
    cout << endl << size << endl;
}

int main() {
    int n, L;
    
    while((cin >> n >> L) && (n != 0 && L != 0)) {
        solve(n, L);
    }
    return 0;
}