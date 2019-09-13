/**
 * @author FanQie
 */
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int v;
    int weight;

    Node() = default;    
    Node(const int &_v, const int &_weight): v(_v), weight(_weight) {}

};

int n, m;
vector<vector<Node>> graph;
vector<int> f;
vector<int> g;
vector<int> costTime;
vector<int> inDegree;
vector<int> outDegree;

int main() {
    scanf("%d %d", &n, &m);
    const int START = 0;
    const int END = n+1;
    graph.resize(n + 2, vector<Node>(0));
    f.resize(n+2, 0);
    g.resize(n+2, 0);
    costTime.resize(n+2, 0);
    inDegree.resize(n+2, 0);
    outDegree.resize(n+2, 0);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &costTime[i]);
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u].push_back(Node(v, costTime[v]));
        ++inDegree[v];
        ++outDegree[u];
    }
    for (int i = 1; i <= n; ++i) {
        if (outDegree[i] == 0) {
            graph[i].push_back(Node(END, 0));
            ++inDegree[END];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            graph[START].push_back(Node(i, costTime[i]));
            ++inDegree[i];
        }
    }

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int frontV = q.front();
        q.pop();
        for (const Node& node : graph[frontV]) {
            --inDegree[node.v];
            f[node.v] = f[frontV] + node.weight;
            if (inDegree[node.v] == 0) {
                q.push(node.v);
            }
        }
    }
    printf("%d\n", f[END]);
    return 0;
}