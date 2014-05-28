// UVA 112
// Recursive paranthesis parsing + depth-first tree traversal.
// Accepted

#include <iostream>
#include <vector>
#include <memory>
#include <istream>

#define LEFT 0
#define RIGHT 1

using namespace std;

bool found = false;

struct node {
    int x;
    shared_ptr<node> l;
    shared_ptr<node> r;
};

typedef shared_ptr<node> node_ptr;

void parse_tree(node_ptr* loc) {
    cin >> ws;
    if(cin.peek() == ')')
        return;
    
    int val;
    char lp, rp;
    cin >> val;
    
    node_ptr n(new node);
    n->x = val;
    n->l = NULL;
    n->r = NULL;
    *loc = n;
    
    cin >> ws >> lp;
    parse_tree(&n->l);
    cin >> ws >> rp;
    
    cin >> ws >> lp;
    parse_tree(&n->r);
    cin >> ws >> rp;
}

node_ptr parse() {
    char lp, rp;
    int root;
    cin >> ws >> lp >> ws;
    
    if(!(cin >> root)) {
        cin.clear();
        cin >> rp;
        return NULL;
    }
    else {
        node_ptr n(new node);
        n->x = root;
        n->l = NULL;
        n->r = NULL;
        
        cin >> ws >> lp;
        parse_tree(&n->l);
        cin >> ws >> rp;
        
        cin >> ws >> lp;
        parse_tree(&n->r);
        cin >> ws >> rp;
        
        cin >> ws >> rp;
        return n;
    }
}

void traverse(node_ptr root, int n, int total) {
    
    if(found)
        return;
    
    n += root->x;
    
    if((!root->l &&  !root->r)) {
        if(n == total)
            found = true;
        return;
    }
    
    if(root->l)
        traverse(root->l, n, total);
    if(root->r)
        traverse(root->r, n, total);
}

void solve(int total) {
    node_ptr root = parse();
    if(root)
        traverse(root, 0, total);
    if(found)
        cout << "yes" << endl;
    else
        cout << "no" << endl ;
    found = false;
}



int main() {
    int total;
    while(cin >> total) {
        solve(total);
    }
    return 0;
}