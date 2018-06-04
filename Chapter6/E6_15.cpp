/*
例题6-15 补全了全部代码
测试数据如下：
4 3
a b
c b
d c
*/

#define _acmbook_e6_15_
#ifdef _acmbook_e6_15_
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 105;
int c[maxn];
int topo[maxn], t, n;
int G[maxn][maxn];

bool dfs(int u)
{
    c[u] = -1;
    for(int v = 0; v < n; v++)
    {
        if(G[u][v])
        {
            if(c[v] < 0) return false;      // 存在有向环
            else if(!c[v] && !dfs(v)) return false;
        }
    }
    c[u] = 1;
    topo[--t] = u;
    return true;
}

bool toposort()
{
    t = n;
    memset(c, 0, sizeof(c));
    for(int u = 0; u < n; u++)
    {
        if(!c[u])
        {
            if(!dfs(u)) return false;
        }
    }
    return true;
}

int main()
{
    int m;
    scanf("%d%d", &n, &m);      // 变量数 不等式数
    getchar();
    char a, b;
    memset(G, 0, sizeof(G));
    for(int i = 0; i < m; i++)
    {
        scanf("%c %c", &a, &b);   // 建立拓扑关系图
        getchar();
        G[a-'a'][b-'a'] = 1;
    }
    if(toposort())
    {
        for(int i = t; i < n - 1; i++) printf("%c ", topo[i]+'a');
        printf("%c", topo[n-1]+'a');
    }else printf("-1\n");
    return 0;
}
#endif
