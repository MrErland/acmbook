#include <iostream>

using namespace std;
static int N = 1000;
int schedule[10][1000];
int n;
struct student{int a; int b; int c;}stud[10];

// 假设先让所有学生都按照时间表保持清醒或睡觉，然后在每次状态变化的时候，去判断是否应该继续睡觉还是保持清醒
// 如果不应该继续睡觉，则改变此时的状态，保持清醒，依次改变其之后的默认状态
// 如果找到一个时刻，所有学生保持清醒，则结束。
// 用0表示清醒，用1表示睡觉。
// 3 (2 4 1) (1 5 2) (1 4 3)  --------- 18

int main()
{
    while(cin>>n)
    {
        if(n>=1 && n<=10) break;
    }
    for(int i=0;i<n;i++)
    {
        cin>>stud[i].a>>stud[i].b>>stud[i].c;
        // 初始化表
        int j=0,k=0;
        if(stud[i].c > stud[i].a)       // 初始状态处于睡眠
        {
            for(;j<(stud[i].a+stud[i].b-stud[i].c);j++)
                schedule[i][j]=1;
        }
        else                              // 初始状态处于清醒
        {
            for(;j<(stud[i].a-stud[i].c);j++)
                schedule[i][j]=0;

            for(;k<stud[i].b;k++)
                schedule[i][j+k]=1;
        }
        int p=j+k;
        while(p<N)              // 将剩余部分全部写成默认的状态
        {
            for(int q=0; q<stud[i].a && p<N; q++,p++)
                schedule[i][p]=0;
            for(int q=0; q<stud[i].b && p<N; q++,p++)
                schedule[i][p]=1;
        }
    }

    // 从1到N，依次判断是否应该继续睡觉   0是初始状态，不用判断
    int j;
    for(j=1;j<N;j++)           // 时间段
    {
        int num = 0;            // 记录睡着的人数
        for(int i=0;i<n;i++)       // 学生数
        {
            if(schedule[i][j-1]==1 )       // 上一个状态是睡着的
                num++;
        }
        if(num > n/2)               // 睡着的人多余半数，继续判断下一个时间
            continue;
        else if(num == 0)           // 都是醒的，结束
            break;
        for(int i=0;i<n;i++)
        {
            if(schedule[i][j-1]==0 && schedule[i][j]==1)    // 上个状态清醒，这个状态睡觉 --> 这个状态转到清醒
            {
                int p=j;
                while(p<N)                  // 从清醒状态开始
                {
                    for(int q=0; q<stud[i].a && p<N; q++,p++)
                        schedule[i][p]=0;
                    for(int q=0; q<stud[i].b && p<N; q++,p++)
                        schedule[i][p]=1;
                }
            }
        }
    }

    if(j!=N)
        cout<<j+1<<endl;            // 从0开始，因此j+1
    else
        cout<<"-1"<<endl;
    return 0;
}

