
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


int radEnterpriseSolveB(
    vector<pair<int, int>> adjList[N],
    int startVertex,
    int endVertex
) {
    // todo: solve this

    int lo = 0;
    int hi = 0;

    for (int i = 0; i < N; i++) {
        vector<pair<int, int>> edges = adjList[i];
        for (pair<int, int> edge : edges) {
            hi = max(hi, edge.second);
        }
    }

    int bestSoFar;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (radEnterpriseSolveA(adjList, startVertex, endVertex, mid)) {
            bestSoFar = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return bestSoFar;
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

    cout << "Expected Answer: 5\n";
    cout << "Actual Answer: " << radEnterpriseSolveB(adjList, 1, 4) << "\n";
}
