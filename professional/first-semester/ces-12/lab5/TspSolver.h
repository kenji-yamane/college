#ifndef TSP_SOLVER
#define TSP_SOLVER


#include <TspReader.h>
#include <vector>

struct Edge {
    int origin;
    int destination;
    int weigth;
};

struct PrimRule {
    bool operator()(Edge const &e1, Edge const &e2);
};

class TspSolver {
public:
    // you should fill percourse with a permutation that represents the TSP solution
    void solve(TspReader &tr,std::vector<int> &percourse); 
}; 

bool PreorderRule(Edge &e1, Edge &e2);
void Prim(const std::vector<std::vector<int> > &graph, std::vector<std::vector<Edge> > &T);
void Preorder(std::vector<std::vector<Edge> > &T, int vertex, std::vector<int> &ans, std::vector<bool> &visited);

#endif
