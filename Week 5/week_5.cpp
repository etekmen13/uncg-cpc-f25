#include "util.hpp"
#include <vector>
#include <algorithm>
#define REP(i,a,b) for(int i = a; i <= b; i++)
#define rep(i,a,b) for(int i = a; i < b; i++)
#define PER(i,a,b) for(int i = a; i >= b; i--)
#define per(i,a,b) for(int i = a; i > b; i--)

using namespace std;

#pragma region HopcroftKarp
struct HopcroftKarp {
    int nL, nR; // sizes of left and right
    vector<vector<int>> adj; // each left node i holds adj[i] right nodes
    vector<int> matchL, matchR; // matching L nodes, matching R nodes.
    vector<int> dist; // BFS levels for the left nodes

    static constexpr int INF = numeric_limits<int>::max();

    HopcroftKarp(int nLeft, int nRight) 
        : nL(nLeft), nR(nRight), adj(nLeft),
        matchL(nLeft, -1), matchR(nRight, -1), dist(nLeft, INF) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < nL);
        assert(0 <= v && v < nR);
        adj[u].push_back(v);
    }

    bool bfs() {

        queue<int> q;

        rep(u, 0, nL) {
            if (matchL[u] == -1) { // if unmatched, add to queue at level 0.
                dist[u] = 0;
                q.push(u);
            }
            else {
                dist[u] = INF; // matched nodes are ignored
            }
        }

        bool found_aug_path = false;

        while (!q.empty()) {
            auto u = q.front(); q.pop();

            for (auto v : adj[u]) {
                auto lmatch_v = matchR[v]; // leftside match for v

                if (lmatch_v == -1) { // v is unmatched. we found a free R node, so we found an augmenting path.
                    found_aug_path = true;

                } 
                else if (dist[lmatch_v] == INF) {// this left node has a matching pair. 
                        dist[lmatch_v] = dist[u] + 1; // increase layer of this node by 1.
                        q.push(lmatch_v);
                } 
            
            }
        }

        return found_aug_path;
    }

    bool dfs(int u) {
        for(auto v : adj[u]) {
            int lmatch_v = matchR[v];

            if (lmatch_v == -1) { // found a free R, so we found an augmenting path. Flip it!
                matchL[u]  = v; // u was unmatched before, now it is matched.
                matchR[v] = u; // v was unmatched before, now it is matched.

                return true; //successfully found augmenting path.
            }
            
            
            // v had a match, so dfs on it until we get to the free R.
            // But first, we must check if there are any valid edges, i.e. edges that are one layer above us.
            if (dist[lmatch_v] == dist[u] + 1) {
                bool found_aug_path = dfs(lmatch_v); 

                if (found_aug_path) { // our dfs found the augpath, so as we unfold, flip edges along the way.

                    matchL[u] = v; // u unmatches from what it was matched to before, now matches v.
                    matchR[v] = u; // v unmatches from what it was matched to before, now matches u.
                    return true;
                }
            }
        }

        // if no augpath found, then the node we started on should not be considered in future dfses.
        dist[u] = INF;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) { // while bfs has found augmenting path(s)
            // dfs from every free left node, just like Kuhn's
            rep(u, 0, nL) {
                if (matchL[u] == -1 && dist[u] == 0) {// free left node at layer 0 are the only ones we can start on.

                    if (dfs(u)) // if the dfs found an augpath, increase matching by 1.
                        ++matching;
                }

            }

        }
        return matching;
    }

    vector<pair<int,int>> get_matched_pairs()  {
        vector<pair<int,int>> pairs;
        rep(u, 0, nL) {
            if (matchL[u] != -1) {
                pairs.emplace_back(u, matchL[u]);
            }
        }
        return pairs;
    }
};
#pragma endregion
int main() {
    ios::sync_with_stdio(false); // removes runtime checks to ensure consistency with legacy C `printf` and `scanf` functions. You then must only use cin and cout.
    cin.tie(nullptr); // unties cin and cout. Instead of printing answers as inputs come in, the program now reads in all inputs, then prints all outputs.
int nL = 4, nR = 4;
    HopcroftKarp hk(nL, nR);
    hk.add_edge(0, 0);
    hk.add_edge(0, 1);
    hk.add_edge(1, 0);
    hk.add_edge(1, 2);
    hk.add_edge(2, 1);
    hk.add_edge(3, 2);
    hk.add_edge(3, 3);

    int ans = hk.max_matching(); // O(E * sqrt(V))
    cout << "Maximum matching size = " << ans << "\n";

    for (auto [u, v] : hk.get_matched_pairs()) {
        cout << "L " << u << " <-> R " << v << "\n";
    }
    return 0;
}