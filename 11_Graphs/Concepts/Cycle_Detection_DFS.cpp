#include <iostream>
#include <list>
#include <vector>
#include <queue>

class Graph{
    int V;
    std::list<int> *l; //int *arr

public:
    Graph(int V){
        this->V = V;
        // arr = new int[V]
        l = new std::list<int> [V];
    }

    void addEdge(int u, int v){
        l[u].push_back(v);
        l[v].push_back(u);
    }

    // marks current node 'src' as visited
    // iterates through its neighbours
    // If 'v' is not visited, recursively calls DFS with 'src' as its parent
    // If 'v' is visited but is not the parent, then a cycle exists -> return true
    bool isCycleUndirDFS(int src, int par, std::vector<bool>& vis){ // O(V+E)
        vis[src] = true;
        std::list<int> neighbours = l[src];

        for(int v: neighbours){
            if(!vis[v]){
                if(isCycleUndirDFS(v, src, vis)){
                    return true;
                }
            } else if(v != par){
                return true;
            }
        }
        return false;
    }

    // initializes all vertices as unvisited
    // runs DFS on every component (since the graph may be disconnected)
    // if any DFS call detects a cycle -> return true
    bool isCycle(){
        std::vector<bool> vis(V, false);
        
        for(int i = 0; i < V; i++){
            if(!vis[i]){
                if(isCycleUndirDFS(i, -1, vis)){
                    return true;
                }
            }
        }
        return false;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(3, 4);

    std::vector<bool> vis(5, false);

    std::cout << g.isCycle() << std::endl;
    return 0;
}