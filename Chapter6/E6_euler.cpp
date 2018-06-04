// 欧拉问题的解法

#define _acmbook_e6_euler_
#ifdef _acmbook_e6_euler_

#include <stack>
using namespace std;
const int N = 1000;
struct road{int u, v; road(int s, int t):u(s), v(t){}};
stack<road> path;
int G[N][N], vis[N][N], n;

void euler(int u)   // 源点
{
    for(int v =  0; v < n; v++)
    {
        if(G[u][v] && !vis[u][v])
        {
            vis[u][v] = vis[v][u] = 1;  // 无向图
            euler(v);
            path.push(road(u, v));
        }
    }
}

#endif
