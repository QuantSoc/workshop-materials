
#include <iostream>
#include <vector>

using namespace std;

const int N = 100;

struct Edge {
    int start;
    int end;
    int weight;
};


void dfs(
    int src, 
    int protectionLevel, 
    vector<pair<int, int>> adjList[N],
    vector<bool> &seen
) {
    if (seen[src]) {
        return;
    }

    seen[src] = true;

    for (pair<int, int> e : adjList[src]) {
        int u = e.first;
        int w = e.second;

        if (w > protectionLevel) {
            continue;
        }

        dfs(u, protectionLevel, adjList, seen);
    }
}


bool radEnterpriseSolveA(
    vector<pair<int, int>> adjList[N],
    int startVertex,
    int endVertex,
    int protectionLevel
) {
    vector<bool> seen(N, false);

    dfs(startVertex, protectionLevel, adjList, seen);

    return seen[endVertex];
}


void addEdge(vector<pair<int, int>> adjList[N], Edge e) {
    adjList[e.start].push_back({e.end, e.weight});
    adjList[e.end].push_back({e.start, e.weight});
}

int main() {
    // pair is formatted as {nextVertex, weight}
    vector<pair<int, int>> adjList[N];

    addEdge(adjList, {1, 2, 2});
    addEdge(adjList, {2, 4, 5});
    addEdge(adjList, {1, 3, 6});
    addEdge(adjList, {3, 4, 3});

    cout << "Expected Answer: False\n";
    cout << "Actual Answer: " << radEnterpriseSolveA(adjList, 1, 4, 4) << "\n";
}
