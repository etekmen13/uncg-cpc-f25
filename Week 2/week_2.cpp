#include "util.hpp"
#include <vector>
#include <algorithm>
using namespace std;

#pragma region Tarjan
void Tarjan() {
    // Build a tiny undirected graph (0..5)
    // Triangle 0-1-2 plus a chain 1-3-4-5 hanging off node 1.
    // Articulation points should be: 1, 3, and 4.
    //
    //  0
    //  | \
    //  |  [1] -- [3] -- [4] -- 5
    //  | /
    //  2
    std::vector<std::vector<int>> adj(6);
    auto add = [&](int u, int v){ adj[u].push_back(v); adj[v].push_back(u); };
    add(0,1); add(1,2); add(2,0); // triangle
    add(1,3); add(3,4); add(4,5); // chain

    int n = (int)adj.size();
    std::vector<int> tin(n, -1), low(n);
    std::vector<char> cut(n, 0);
    int timer = 0;

    function<void(int,int)> dfs = [&](int u, int p) {
        tin[u] = low[u] = ++timer;
        int children = 0;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (tin[v] != -1) {
                low[u] = std::min(low[u], tin[v]);
            } else {
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);
                if (p != -1 && low[v] >= tin[u]) cut[u] = 1;
                ++children;
            }
        }
        if (p == -1 && children > 1) cut[u] = 1;
    };

    for (int i = 0; i < n; ++i)
        if (tin[i] == -1) dfs(i, -1);

    for (int i = 0; i < n; ++i)
        if (cut[i]) std::cout << "Articulation point: " << i << "\n";
}
#pragma endregion

#pragma region BFS_01
void BFS_01() {
    int N = 6;              // vertices 0..5
    int S = 0;              // source
    vector<vector<pair<int,int>>> G(N); // contains: (to, weight in {0,1})

    auto add_edge = [&](int u, int v, int w, bool undirected = true) {
        G[u].push_back({v, w});
        if (undirected) G[v].push_back({u, w});
    };

    // Graph (undirected):
    // 0 --0--> 1, 0 --1--> 2
    // 1 --1--> 2, 1 --0--> 3
    // 2 --1--> 3, 2 --1--> 5
    // 3 --0--> 4
    // 4 --0--> 5
    add_edge(0, 1, 0);
    add_edge(0, 2, 1);
    add_edge(1, 2, 1);
    add_edge(1, 3, 0);
    add_edge(2, 3, 1);
    add_edge(2, 5, 1);
    add_edge(3, 4, 0);
    add_edge(4, 5, 0);

    const int INF = 1e9;
    vector<int> dist(N, INF);
    deque<int> dq;

    dist[S] = 0;
    dq.push_front(S);

    while (!dq.empty()) {
        int v = dq.front(); dq.pop_front();
        for (auto [to, w] : G[v]) {      // w ∈ {0,1}
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                if (w == 0) dq.push_front(to);
                else        dq.push_back(to);
            }
        }
    }

    // --- Show results ---
    cout << "0-1 shortest distances from source " << S << ":\n";
    for (int i = 0; i < N; ++i) {
        cout << "dist[" << i << "] = " << (dist[i] == INF ? -1 : dist[i]) << "\n";
    }
}
#pragma endregion

#pragma region TopologicalDP
void KahnsTopoSort() {
    // DAG with 6 nodes: 0..5
    // Edges: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
    int n = 6;
    vector<vector<int>> adj(n);
    auto add_edge = [&](int u, int v){ adj[u].push_back(v); };
    add_edge(5,2); add_edge(5,0);
    add_edge(4,0); add_edge(4,1);
    add_edge(2,3); add_edge(3,1);

    // Compute in-degrees
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : adj[u]) ++indeg[v];

    // Push all 0-in-degree nodes
    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);

    // Kahn's algorithm
    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    // Output
    if ((int)topo.size() != n) {
        cout << "Graph has a cycle (not a DAG)\n";
    } else {
        cout << "Topological order:";
        for (int x : topo) cout << ' ' << x;
        cout << '\n';
    }
}
void ShortestPathDAG() {
    // DAG with nodes 0..4 (already in topological order)
    int n = 5, src = 0;
    vector<vector<pair<int,int>>> g(n);
    auto add = [&](int u,int v,int w){ g[u].push_back({v,w}); };

    // Edges (all go from lower index -> higher index)
    add(0,1,2);  add(0,2,5);
    add(1,2,1);  add(1,3,2);
    add(2,3,1);  add(3,4,3);

    // Given topological order (precomputed)
    vector<int> topo = {0,1,2,3,4};

    const long long INF = (1LL<<60);
    vector<long long> dist(n, INF);
    dist[src] = 0;

    // Single pass over the topo order, relaxing outgoing edges
    for (int u : topo) {
        if (dist[u] == INF) continue;         // unreachable so far
        for (auto [v,w] : g[u]) {
            dist[v] = min(dist[v], dist[u] + w);
        }
    }

    // Print distances from src
    for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) cout << "dist[" << i << "] = INF\n";
        else                cout << "dist[" << i << "] = " << dist[i] << "\n";
    }
}

void LongestPathDAG() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Example DAG (topological order is 0,1,2,3,4)
    // Edges: u -> v (weight)
    vector<vector<pair<int,int>>> g(5);
    auto add = [&](int u,int v,int w){ g[u].push_back({v,w}); };
    add(0,1,2);
    add(0,2,3);
    add(1,3,4);
    add(2,3,1);
    add(2,4,2);
    add(3,4,5);

    vector<int> topo = {0,1,2,3,4};          // pre-topologically sorted

    const int N = (int)g.size();
    const long long NEG = (long long)-4e18;

    // dp[v] = best (max) distance ending at v from some source
    vector<long long> dp(N, 0);              // 0 works: empty path at each node
    vector<int> par(N, -1);                  // parent for path reconstruction

    for (int u : topo) {
        for (auto [v,w] : g[u]) {
            if (dp[u] + w > dp[v]) {
                dp[v] = dp[u] + w;
                par[v] = u;
            }
        }
    }

    // Find the endpoint of a longest path
    int best = 0;
    for (int i = 1; i < N; ++i) if (dp[i] > dp[best]) best = i;

    // Reconstruct path
    vector<int> path;
    for (int x = best; x != -1; x = par[x]) path.push_back(x);
    reverse(path.begin(), path.end());

    cout << "Longest path weight = " << dp[best] << "\nPath: ";
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << " -> ";
        cout << path[i];
    }
    cout << "\n";
}
#include <bits/stdc++.h>
using namespace std;

// Count number of paths from a single source to all nodes in a topo-sorted DAG.
void NumWaysDAG() {
    // Vertices 0..5 are in topological order.
    int n = 6, s = 0;
    vector<vector<int>> g(n);
    auto add = [&](int u, int v){ g[u].push_back(v); };

    // DAG (all edges go from smaller to larger index):
    // 0 -> 1,2
    // 1 -> 3
    // 2 -> 3,4
    // 3 -> 5
    // 4 -> 5
    add(0,1); add(0,2);
    add(1,3);
    add(2,3); add(2,4);
    add(3,5);
    add(4,5);

    vector<long long> ways(n, 0);
    ways[s] = 1; // one way to be at the source

    // Since nodes are pre-topologically sorted, a single left-to-right pass suffices.
    for (int u = 0; u < n; ++u)
        for (int v : g[u])
            ways[v] += ways[u];

    // Print number of paths from s to every node
    for (int i = 0; i < n; ++i)
        cout << "ways[" << i << "] = " << ways[i] << '\n';
}

#pragma endregion


int main() {
    ios::sync_with_stdio(false); // removes runtime checks to ensure consistency with legacy C `printf` and `scanf` functions. You then must only use cin and cout.
    cin.tie(nullptr); // unties cin and cout. Instead of printing answers as inputs come in, the program now reads in all inputs, then prints all outputs.
    
    //Tarjan();
    //BFS_01();
    //KahnsTopoSort();
    //ShortestPathDAG();
    //LongestPathDAG();
    //NumWaysDAG();
    return 0;
}