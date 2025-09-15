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

    bool isCycleUndirBFS(int src, std::vector<bool> &vis){ // O(V+E)
        std::queue<std::pair<int, int>> q;

        q.push({src, -1});
        vis[src] = true;

        while(q.size() > 0){
            int u = q.front().first;
            int parU = q.front().second;
            q.pop();

            std::list<int> neighbors = l[u];
            for(int v: neighbors){
                if(!vis[v]){
                    q.push({v, u});
                    vis[v] = true;
                } else if(v != parU){
                    return true;
                }
            }
        }
        return false;
    }
    bool isCycle(){
        std::vector<bool> vis(V, false);

        for(int i = 0; i < V; i++){
            if(!vis[i]){
                if(isCycleUndirBFS(i, vis)){
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