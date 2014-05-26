// UVA 10249
// Solution using Max-Flow.
// Wrong Answer @ Running Time ~3.5 secs.

#include <iostream>
#include <set>
#include <list>
#include <queue>
#include <algorithm>
#include <stack>
#include <memory>
#include <vector>

using namespace std;

// Structure used for adjacency list graph
struct edgenode {
    int v;
    int flow;
    int residual;
    std::shared_ptr<edgenode> next;
};


class graph {
    
private:
    
    std::vector<int>                        parents;
    std::vector<bool>                       discovered;
    std::vector<bool>                       processed;
    
    int nVertices;
    int nEdges;
    
    void                        initialize_search();
    void                        bfs(int v);
    int                         path_volume(int s, int t);
    bool                        valid_edge(std::shared_ptr<edgenode> e);
    std::shared_ptr<edgenode>   find_edge(int x, int y);
    void                        augment_path(int   start, int end, int volume);
    
public:
    
    // edges[x] returns the linked list of all outgoing edges
    // from vertex x.
    std::vector<std::shared_ptr<edgenode>>  edges;
    
    graph(int numOfVertices);
    
    // returns max-flow of the graph.
    int                         netflow(int s, int t);
    void                        insert_edge(int x, int y, int capacity);
};

#define MIN(x,y) ((x < y) ? x : y)

typedef std::shared_ptr<edgenode> edgenode_ptr;

// ==============================================
// GRAPH IMPLEMENTATION
// ==============================================

graph::graph(int numOfVertices) {
    nVertices = numOfVertices;
    edges.resize(nVertices);
    parents.resize(nVertices);
    discovered.resize(nVertices);
    processed.resize(nVertices);
}

void graph::initialize_search() {
    for(int i = 0; i < nVertices; i++) {
        parents[i] = -1;
        discovered[i] = false;
        processed[i] = false;
    }
}

void graph::insert_edge(int x, int y, int capacity) {
    edgenode_ptr e(new edgenode);
    e->v = y;
    e->flow = 0;
    e->residual = capacity;
    e->next = edges[x];
    edges[x] = e;
    
    edgenode_ptr er(new edgenode);
    er->v = x;
    er->flow = 0;
    er->residual = 0;
    er->next = edges[y];
    edges[y] = er;
}

void graph::bfs(int start) {
    std::queue<int> q;
    discovered[start] = true;
    q.push(start);
    
    
    while(q.size()) {
        int v = q.front();
        q.pop();
        processed[v] = true;
        
        edgenode_ptr edgeIt = edges[v];
        while(edgeIt) {
            if(!discovered[edgeIt->v] && edgeIt->residual) {
                discovered[edgeIt->v] = true;
                parents[edgeIt->v] = v;
                q.push(edgeIt->v);
            }
            edgeIt = edgeIt->next;
        }
    }
}

int graph::netflow(int s, int t) {
    int maxFlow = 0;
    int volume;
    do {
        initialize_search();
        bfs(s);
        volume = path_volume(s, t);
        augment_path(s, t, volume);
        maxFlow += volume;
    } while(volume > 0);
    
    return maxFlow;
}

bool graph::valid_edge(edgenode_ptr e) {
    return e->residual > 0;
}

int graph::path_volume(int s, int t) {
    if(parents[t] == -1) return 0;
    edgenode_ptr e = find_edge(parents[t], t);
    if(s == parents[t])
        return e->residual;
    else if(!valid_edge(e))
        return 0;
    else
        return MIN(path_volume(s, parents[t]), e->residual);
}

edgenode_ptr graph::find_edge(int x, int y) {
    auto edgeIt = edges[x];
    while(edgeIt) {
        int v = edgeIt->v;
        if(v == y) return edgeIt;
        edgeIt = edgeIt->next;
    }
    
    return NULL;
}

void graph::augment_path(int start, int end, int volume) {
    if(!volume) return;
    if(start == end) return;
    
    edgenode_ptr e = find_edge(parents[end], end);
    e->flow += volume;
    e->residual -= volume;
    
    e = find_edge(end, parents[end]);
    e->residual += volume;
    
    augment_path(start, parents[end], volume);
}

// ==============================================
// GRAPH IMPLEMENTATION ENDS
// ==============================================

int teamSize[71];
int tableSize[71];

int main() {
    while(true) {
        int nTeams, nTables;
        cin >> nTeams >> nTables;
        
        if(nTeams == 0 && nTables == 0)
            break;
        
        if(nTables < nTeams) {
            cout << 0 << endl;
            
            for(int i = 1; i < nTeams + 1; i++)
                cin >> teamSize[i];
            
            for(int i = 1; i < nTables + 1; i++)
                cin >> tableSize[i];
            
            continue;
        }
        
        int nPeople = 0;
        int nSeats = 0;
        
        for(int i = 1; i < nTeams + 1; i++) {
            cin >> teamSize[i];
            nPeople += teamSize[i];
        }
        
        for(int i = 1; i < nTables + 1; i++) {
            cin >> tableSize[i];
            nSeats += tableSize[i];
        }
        
        if(nSeats < nPeople) {
            cout << 0 << endl;
            continue;
        }
        
        // vertex[0] is source
        // vertex[nTeams + nTables + 1] is sink
        
        // there are edges from source to each team i
        // with flow capacity teamSize[i]
        
        // there are edges from each team i to
        // each table j with flow capacity 1
        
        // there are edges from each table j
        // to the sink with flow capacity tabeSize[j]
        
        graph g(nTeams + nTables + 2);
        for(int i = 1; i < nTeams + 1; i++) {
            g.insert_edge(0, i, teamSize[i]);
            
            for(int j = nTeams + 1; j < nTeams + nTables + 1; j++) {
                g.insert_edge(i, j, 1);
            }
        }
        
        for(int i = nTeams + 1; i < nTeams + nTables + 1; i++) {
            g.insert_edge(i, nTeams + nTables + 1, tableSize[i - nTeams]);
        }
        
        int maxFlow = g.netflow(0, nTeams + nTables + 1);
        
        if(maxFlow < nPeople)
            cout << 0 << endl;
        else {
            cout << 1 << endl;
            for(int i = 1; i < nTeams + 1; i++) {
                shared_ptr<edgenode> e = g.edges[i];
                
                // stack is used to print table indices
                // in increasing order.
                
                stack<int> st;
                while(e) {
                    if(e->v && !e->residual) {
                        st.push(e->v - nTeams);
                    }
                    
                    e = e->next;
                }
                
                int first = 0;
                while(st.size()) {
                    if(first++)
                        cout << " ";
                    int t = st.top();
                    st.pop();
                    cout << t;
                }
                
                cout << endl;
            }
        }
    }
    
    return 0;
}