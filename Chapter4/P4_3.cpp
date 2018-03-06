#include <iostream>
#include <string>
#include <vector>
using namespace std;
char chess[9][9];        // 8 * 8的棋盘， 其中黑为B 白为W， *为空格
char side;               // 存在两方，分别是 B W
static int N = 8;
struct point{int x;int y;};
string mod;
vector<struct point> place;   // 每一个可能的落点

/*
********
********
***B**W*
***BBB**
**WBWW**
**BBBW**
********
********
W
只实现了上下左右四个方向的落子和合并子，没有考虑对角线的情况。
*/

bool isInChess(int x, int y)
{
    return x >= 1 && x <= N && y >= 1 && y <= N;
}

void getPlace()
{
    place.clear();
    struct point tmp;
    for(int x=1;x<=N;x++)
    {
        for(int y=1;y<=N;y++)
        {
            bool f = 0;
            tmp.x = x;
            tmp.y = y;
            if(chess[x][y] != '*')
                continue;
            if(isInChess(x+1, y))
            {
                if(chess[x+1][y] != '*' && chess[x+1][y] != side)
                {
                    char c = chess[x+1][y];
                    for(int s=x+2;s<=N;s++)
                    {
                        if(chess[s][y] == c)
                            continue;
                        else if(chess[s][y] == side)
                        {
                              f = 1;
                              place.push_back(tmp);
                              break;
                        }
                        else
                            break;
                    }
                }
            }
            if(isInChess(x-1, y) && !f)
            {
                if(chess[x-1][y] != '*' && chess[x-1][y] != side)
                {
                    char c = chess[x-1][y];
                    for(int s=x-2;s>=1;s--)
                    {
                        if(chess[s][y] == c)
                            continue;
                        else if(chess[s][y] == side)
                        {
                              f = 1;
                              place.push_back(tmp);
                              break;
                        }
                        else
                            break;
                    }
                }
            }
            if(isInChess(x,y+1) && !f)
            {
                if(chess[x][y+1] != '*' && chess[x][y+1] != side)
                {
                    char c = chess[x][y+1];
                    for(int s=y+2;s<=N;s++)
                    {
                        if(chess[x][s] == c)
                            continue;
                        else if(chess[x][s] == side)
                        {
                              f = 1;
                              place.push_back(tmp);
                              break;
                        }
                        else
                            break;
                    }
                }
            }
            if(isInChess(x,y-1) && !f)
            {
                if(chess[x][y-1] != '*' && chess[x][y-1] != side)
                {
                    char c = chess[x][y-1];
                    for(int s=y-2;s>=1;s--)
                    {
                        if(chess[x][s] == c)
                            continue;
                        else if(chess[x][s] == side)
                        {
                              f = 1;
                              place.push_back(tmp);
                              break;
                        }
                        else
                            break;
                    }
                }
            }
        }
    }
}

void delePlace(int x, int y)
{
    if(isInChess(x+1, y) && chess[x+1][y] != side && chess[x+1][y] != '*')
    {
        for(int i=x+2;i<=N;i++)
        {
            if(chess[i][y]==chess[x+1][y])
                continue;
            else if(chess[i][y]!=chess[x+1][y] && chess[i][y]!='*')
            {
                for(int j=x+1;j<i;j++)
                    chess[j][y] = side;
                break;
            }
            else
                break;
        }
    }
    if(isInChess(x-1, y) && chess[x-1][y] != side && chess[x-1][y] != '*')
    {
        for(int i=x-2;i>=1;i--)
        {
            if(chess[i][y]==chess[x-1][y])
                continue;
            else if(chess[i][y]!=chess[x-1][y] && chess[i][y]!='*')
            {
                for(int j=x-1;j>i;j--)
                    chess[j][y] = side;
                break;
            }
            else
                break;
        }
    }
    if(isInChess(x, y+1) && chess[x][y+1] != side && chess[x][y+1] != '*')
    {
        for(int i=y+2;i<=N;i++)
        {
            if(chess[x][i]==chess[x][y+1])
                continue;
            else if(chess[x][i]!=chess[x][y+1] && chess[x][i]!='*')
            {
                for(int j=y+1;j<i;j++)
                    chess[x][j] = side;
                break;
            }
            else
                break;
        }
    }
    if(isInChess(x, y-1) && chess[x][y-1] != side && chess[x][y-1] != '*')
    {
        for(int i=y-2;i>=1;i--)
        {
            if(chess[x][i]==chess[x][y-1])
                continue;
            else if(chess[x][i]!=chess[x][y-1] && chess[x][i]!='*')
            {
                for(int j=y-1;j>i;j--)
                    chess[x][j] = side;
                break;
            }
            else
                break;
        }
    }
}

int main()
{
    for(int i=1;i<=N;i++)
    {
        fflush(stdin);
        for(int j=1;j<=N;j++)
            scanf("%c", &chess[i][j]);
    }
    fflush(stdin);
    scanf("%c", &side);
    getPlace();

    cout<<"Mod: L/Mrc, Q: Exit"<<endl;
    while(cin >> mod && mod != "Q")
    {
        if(mod == "L")
        {
            cout<<"Side: "<<side<<endl;
            if(place.size() == 0)
            {
                cout<<"No legal move"<<endl;
                continue;
            }
            for(int i=0;i<place.size();i++)
                cout<<"("<<place[i].x<<","<<place[i].y<<")"<<endl;
        }
        else if(mod == "Mrc")
        {
            if(place.size()==0)         // 没有合法的操作
            {
                if(side == 'B') side = 'W';
                else side = 'B';
                getPlace();
                cout<<"Exchange Black & White"<<endl;
                continue;
            }
            int x,y;
            while(cin>>x>>y)            //  输入一个合法的操作点
            {
                bool f = 0;
                for(int i=0;i<place.size();i++)
                {
                    if(place[i].x == x && place[i].y == y)
                    {
                        f=1;
                        break;
                    }
                }
                if(f)
                    break;
                cout<<"Not a legal place"<<endl;
            }
            fflush(stdin);
            chess[x][y] = side;
            delePlace(x, y);            // 消除中间的子
            if(side == 'B')     side = 'W';     // 改变游戏方
            else side = 'B';
            getPlace();                  // 重新计算可能的落点
            int mw=0;
            int mb=0;
            for(int i=1;i<=N;i++)         // 计算黑白的子数
                for(int j=1;j<=N;j++)
                    if(chess[i][j]=='B') mb++;
                    else if(chess[i][j]=='W') mw++;
            cout<<"Black: "<<mb<<"\tWhite: "<<mw<<endl;
        }
        else
            cout<<"Illegal Mod."<<endl;
        cout<<"Mod: L/Mrc   Q: Exit"<<endl;
    }
    if(mod == "Q")
    {
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                printf("%2c", chess[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}

