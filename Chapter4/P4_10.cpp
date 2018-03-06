#include <iostream>
#include <algorithm>
using namespace std;

/*
首先可以把整个方格看成一个容器，每一个小方格具有一定的高度。
水总是先填满高度低的方格，因此可以先将所有方格排序，先填满低的方格。
根据相邻方格的高度差，计算水的体积，累加直到大于给定水体积。
3 3
25 37 45
51 12 34
94 83 27
10000
-------
46.67 66.67%
*/

int n,m;
int grid[100];      // 方格高度
int water;          // 水量

int main()
{
    cin>>n>>m;
    for(int i=0;i<n*m;i++)
    {
        cin>>grid[i];
    }
    cin>>water;
    sort(grid, grid+n*m);      // 从小到大排序

    int now = 0;               // 当前水的体积
    int i;
    int tmp[100]={0};
    for(i=0;i<n*m-1;i++)         // 从低到高
    {
        tmp[i] = (i+1)*100*(grid[i+1]-grid[i]);     // 一层产生的水量
        now += tmp[i];
        if(now > water)
            break;
    }
    double height;
    if(i == n*m-1)                  // 全部灌满
    {
        height = (water-now)*1.0 / (n*m*100) + grid[n*m-1];    // 计算高度
        cout<<height<<" 100%"<<endl;
    }
    else
    {
        height = (water-(now-tmp[i]))*1.0 / ((i+1)*100) + grid[i];
        cout<<height<<" "<<(i+1)*100.0/m/n<<"%"<<endl;
    }
    return 0;
}

