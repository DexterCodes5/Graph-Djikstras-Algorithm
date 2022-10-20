#include <iostream>
#include <list>
#include <vector>
#include <set>

// Weighted Graph
class Graph {
    int V;
    // Pointer to an array of lists
    std::list<std::pair<int,int> > *l;
    
public:
    Graph(int v) :V{v} {
        l = new std::list<std::pair<int,int>>[V];
    }
    
    void addEdge(int u, int v, int wt, bool undir = true) {
        l[u].push_back({wt,v});
        if (undir) {
            l[v].push_back({wt,u});
        }
    }
    
    int djikstra(int src, int dest) {
        
        // Data structures
        std::vector<int> dist(V,INT_MAX);
        std::set<std::pair<int,int>> s;
        
        // 1.Init
        dist[src] = 0;
        s.insert({0,src});
        
        while (!s.empty()) {
            std::set<std::pair<int,int>>::iterator it = s.begin();
            
            int node = it->second;
            int distTillNow = it->first;
            s.erase(it); // Pop
            
            // Iterate over the nbrs of node
            for (std::pair<int,int> nbrPair : l[node]) {
                //.....
                
                int nbr = nbrPair.second;
                int currentEdge = nbrPair.first;
                
                if (distTillNow + currentEdge < dist[nbr]) {
                    // remove if nbr already exists int the set
                    
                    std::set<std::pair<int,int>>::iterator f = s.find({dist[nbr],nbr});
                    if (f != s.end()) {
                        s.erase(f);
                    }
                    
                    // insert the updated value with the new dist
                    dist[nbr] = distTillNow + currentEdge;
                    s.insert({dist[nbr],nbr});
                }
            }
        }
        // Single Source Shortest Dist to all other nodes
        for (int i = 0; i < V; i++) {
            std::cout << "Node i " << i << " Dist " << dist[i] << "\n";
        }
        return dist[dest];
    }
};

int main(){
    Graph g(5);
    g.addEdge(0,1,1);
    g.addEdge(1,2,1);
    g.addEdge(0,2,4);
    g.addEdge(0,3,7);
    g.addEdge(3,2,2);
    g.addEdge(3,4,3);
    
    std::cout << g.djikstra(0,4) << std::endl;
    
    return 0;
}
