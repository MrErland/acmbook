#include <iostream>
#include <string>
#include <set>
#include <iterator>
using namespace std;
set<string> tmp;

void RotateX()          // 只旋转X轴，分为转一次、两次、三次
{
    for(set<string>::iterator i=tmp.begin();i!=tmp.end();i++)
    {
        string t=*i;
        string a=t.substr(2,1) + t.substr(1,1) + t.substr(5,1) + t.substr(0,1) + t.substr(4,1) + t.substr(3,1);
        string b=t.substr(5,1) + t.substr(1,1) + t.substr(3,1) + t.substr(2,1) + t.substr(4,1) + t.substr(0,1);
        string c=t.substr(3,1) + t.substr(1,1) + t.substr(0,1) + t.substr(5,1) + t.substr(4,1) + t.substr(2,1);
        tmp.insert(a);
        tmp.insert(b);
        tmp.insert(c);
    }
}

void RotateY()          // 只旋转Y轴
{
    for(set<string>::iterator i=tmp.begin();i!=tmp.end();i++)
    {
        string t=*i;
        string a=t.substr(1,1) + t.substr(5,1) + t.substr(2,1) + t.substr(3,1) + t.substr(0,1) + t.substr(4,1);
        string b=t.substr(5,1) + t.substr(4,1) + t.substr(2,1) + t.substr(3,1) + t.substr(1,1) + t.substr(0,1);
        string c=t.substr(4,1) + t.substr(0,1) + t.substr(2,1) + t.substr(3,1) + t.substr(5,1) + t.substr(1,1);
        tmp.insert(a);
        tmp.insert(b);
        tmp.insert(c);
    }
}

void RotateZ()          // 只旋转Z轴
{
    for(set<string>::iterator i=tmp.begin();i!=tmp.end();i++)
    {
        string t=*i;
        string a=t.substr(0,1) + t.substr(2,1) + t.substr(4,1) + t.substr(1,1) + t.substr(3,1) + t.substr(5,1);
        string b=t.substr(0,1) + t.substr(3,1) + t.substr(1,1) + t.substr(4,1) + t.substr(2,1) + t.substr(5,1);
        string c=t.substr(0,1) + t.substr(4,1) + t.substr(3,1) + t.substr(2,1) + t.substr(1,1) + t.substr(5,1);
        tmp.insert(a);
        tmp.insert(b);
        tmp.insert(c);
    }
}

int main()
{
    string first,second;
    while(cin>>first>>second && (first.length() != 6 || second.length() != 6))  ;
    fflush(stdin);
    tmp.insert(first);
    RotateX();
    RotateY();
    RotateZ();
    for(set<string>::iterator i=tmp.begin();i!=tmp.end();i++)       // 打印骰子所有的可能性
    {
        cout<<*i<<endl;
    }
    for(set<string>::iterator i=tmp.begin();i!=tmp.end();i++)
    {
        if(*i == second)
        {
            cout<<first<<" is the same as "<<second<<endl;
            break;
        }
    }
    return 0;
}

