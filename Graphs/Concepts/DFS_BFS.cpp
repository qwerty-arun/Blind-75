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

    void depthFirstSearchHelper(int u, std::vector<bool>& vis){
        std::cout << u << " ";
        vis[u] = true;

        for(int v: l[u]){
            if(!vis[v]){ // if neighbour is not visited
                depthFirstSearchHelper(v, vis); // 'v' becomes the source
            }
        }
    }

    void depthFirstSearch(){ //O(V+E)
        std::cout << "DFS: " << std::endl;
        int src = 0;
        std::vector<bool> vis(V, false);

        // For disconnected graphs
        // for (int i = 0; i < V; i++){
        //     if(!vis[i]){
        //         depthFirstSearchHelper(i, vis);
        //     }
        // }
        
        depthFirstSearchHelper(src, vis);
    }

    void breadthFirstSearch(){ // O(V+E)

        std::cout << "\n\nBFS: " << std::endl;
        std::queue<int> Q; 
        std::vector<bool> vis(V, false);

        Q.push(0);
        vis[0] = true;

        while(Q.size() > 0){
            int u = Q.front(); // u -> source
            Q.pop();

            std::cout << u << " ";

            for(int v : l[u]){ // v-> immediate neighbours
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                }
            }
        }
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::vector<bool> vis(5, false);
    g.depthFirstSearch();
    g.breadthFirstSearch();
    return 0;
}