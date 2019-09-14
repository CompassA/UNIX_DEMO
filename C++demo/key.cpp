/*
 * @Author: FanQie 
 * @Date: 2019-09-14 00:20:24 
 * @Last Modified by: FanQie
 * @Last Modified time: 2019-09-14 23:00:45
 */
#include <stdio.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Node {
    int v;
    //到V节点花费的时间
    int weight;

    Node() = default;    
    Node(const int &_v, const int &_weight): v(_v), weight(_weight) {}

};

const int MAGICNUM = 1000000007;
int n, m;
//AOE图
vector<vector<Node>> graph;
//前驱
vector<vector<int>> pre;
//最早开始
vector<int> f;
//最晚开始
vector<int> g;
//活动耗费时间
vector<int> costTime;
//入度
vector<int> inDegree;
//出度
vector<int> outDegree;

int main() {
    scanf("%d %d", &n, &m);
    const int START = 0;
    const int END = n+1;
    graph.resize(n+2, vector<Node>(0));
    pre.resize(n+2, vector<int>(0));
    f.resize(n+2, 0);
    g.resize(n+2, INT_MAX);
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
        pre[v].push_back(u);
        ++inDegree[v];
        ++outDegree[u];
    }
    
    for (int i = 1; i <= n; ++i) {
        if (inDegree[i] == 0) {
            graph[START].push_back(Node(i, costTime[i]));
            ++inDegree[i];
            pre[i].push_back(START);
            ++outDegree[START];
        } else if (outDegree[i] == 0) {
            graph[i].push_back(Node(END, 0));
            ++inDegree[END];
            pre[END].push_back(i);
            ++outDegree[i];
        }
    }

    queue<int> q;
    q.push(START);
    while (!q.empty()) {
        int frontV = q.front();
        q.pop();
        for (const Node& node : graph[frontV]) {
            /*
             *node.v  frontV的后继节点
             *node.weight 执行node.v需要花费的时间
             */
            --inDegree[node.v];
            f[node.v] = max(f[frontV] + node.weight, f[node.v]);
            if (inDegree[node.v] == 0) {
                q.push(node.v);
            }
        }
    }
    printf("%d\n", f[END]);

    g[END] = f[END];
    q.push(END);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const int& nodeNo : pre[v]) {
            g[nodeNo] = min(g[v] - costTime[v], g[nodeNo]);
            --outDegree[nodeNo];
            if (outDegree[nodeNo] == 0) {
                q.push(nodeNo);
            }
        }
    }

    // for (int i = 0; i <= n+1; ++i) {
    //     printf("f[%d] = %d; g[%d] = %d\n", i, f[i], i, g[i]);
    // }

    long long res = 1;
    for (int i = 1; i <= n; ++i) {
        res = res * (g[i] - f[i] + 10) % MAGICNUM;
    }
    printf("%lld\n", res);

    return 0;
}