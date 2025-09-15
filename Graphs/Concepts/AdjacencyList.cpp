#include <iostream>
#include <list>
#include <vector>

class Graph{
    int V;
    std::list<int> *l; //int *arr
    // 'l' points to an array of 'V' Linked Lists of integers

public:
    Graph(int V){
        this->V = V;
        // arr = new int[V]
        l = new std::list<int> [V];
    }

    void addEdge(int u, int v){
        l[u].push_back(v); // 'u' adds 'v' as its neighbour
        l[v].push_back(u); // 'v' adds 'u' as its neighbour
    }

    void printAdjList(){
        for(int i = 0; i < V; i++){
            std::cout << i << " : ";
            for(int neigh : l[i]){
                std::cout << neigh << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);

    g.printAdjList();
    return 0;
}