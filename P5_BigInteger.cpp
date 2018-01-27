
/*
《算法竞赛入门经典（第二版）》第5章 第3节 高精度非负整数类
 Origin Code: 赋值运算符、输出流、输入流，加法运算、比较运算符
 Version: 0.0
 Date: 2018.1.26
 *************************************************************
 Version: 0.1 增加减法、乘法运算
 By: Erland
 Date: 2018.1.26
 *************************************************************
 Version: 0.2 修改了减法中的Bug、添加除法运算
 By: Erland
 Date: 2018.1.27
*/

#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

struct BigInteger {
  static const int BASE = 10000;        // 考虑到乘法运算可能产生较大的数，因此BASE改为10000
  static const int WIDTH = 4;
  vector<int> s;

  BigInteger(long long num = 0) { *this = num; }    // 构造函数
  BigInteger operator = (long long num) {           // 赋值运算符
    s.clear();
    do {
      s.push_back(num % BASE);
      num /= BASE;
    } while(num > 0);
    return *this;
  }

  BigInteger operator = (const string& str) {         // 赋值运算符
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
      int end = str.length() - i * WIDTH;          // 每width位子串的尾部
      int start = max(0, end - WIDTH);             // 每width位子串的头部
      sscanf(str.substr(start, end-start).c_str(), "%d", &x);
      s.push_back(x);
    }
    return *this;
  }

  BigInteger operator + (const BigInteger& b) const {        // 加法
    BigInteger c;
    c.s.clear();
    for(unsigned int i = 0, g = 0; ; i++) {       // g为进位 模拟加法运算
      if(g == 0 && i >= s.size() && i >= b.s.size()) break;
      int x = g;
      if(i < s.size()) x += s[i];
      if(i < b.s.size()) x += b.s[i];
      c.s.push_back(x % BASE);
      g = x / BASE;
    }
    return c;
  }

  BigInteger operator - (const BigInteger& b) const {       // 减法 注意减数和被减数可能交换位置
    BigInteger c;
    c.s.clear();
    if(*this > b)
    {
      for(unsigned int i = 0, g = 0; ; i++) {
        if(g == 0 && i >= s.size() && i >= b.s.size()) break;
        int x = g;
        if(i < s.size()) x = s[i] - g;
        if(i < b.s.size()) x -= b.s[i];
        if(x >= 0) { g = 0; c.s.push_back(x % BASE); }
        else {g = 1; c.s.push_back((x + BASE) % BASE); }
      }
    }
    else         // 如果减数大于被减数，互换位置，并在结果的高位加上负号
    {
      for(unsigned int i = 0, g = 0; ; i++) {
        if(g == 0 && i >= s.size() && i >= b.s.size()) break;
        int x = g;
        if(i < s.size()) x = b.s[i] - g;        // 修改
        if(i < b.s.size()) x -= s[i];           // 修改
        if(x >= 0) { g = 0; c.s.push_back(x % BASE); }
        else {g = 1; c.s.push_back((x + BASE) % BASE); }
      }
        int t = c.s.back();        // 结果的最高位取负号         // 0.2 中修改了Bug
        c.s.pop_back();
        c.s.push_back(0 - t);
    }
    return c;
  }

  BigInteger mul(int b, int j) const {     // 单个元素与BigInteger相乘
      BigInteger c;
      c.s.clear();
      for(int i = 0; i < j; i++)         // 在末尾补0
        c.s.push_back(0);
      for(unsigned int i = 0, g = 0; ; i++)
      {
          if(g == 0 && i >= s.size()) break;
          int x = 0;
          if(i < s.size()) x = b * s[i];
          c.s.push_back((x + g) % BASE);
          g = (x + g) / BASE;
      }
      return c;
  }

  BigInteger operator * (const BigInteger& b) const {           // 乘法
    BigInteger c;
    c.s.clear();
    for(unsigned int i = 0; i < b.s.size(); i++) {    // 把b的每一个子元素分别去乘this
        BigInteger t = mul(b.s[i], i);          // 累加
        c = (c + t);
    }
    return c;
  }

  BigInteger operator / (const BigInteger& b) const {       // 除法
    BigInteger c;
    c.s.clear();
    if(*this < b) { c.s.push_back(0);  return c; }     // a < b 输出0
    if(*this == b) { c.s.push_back(1); return c; }
    int i;     // 10 的 i 次方
    BigInteger t = b;
    vector <BigInteger> tmp;        // 用来保存10的次方倍数
    tmp.push_back(t);
    while(true)              // 将除数增大10倍，直到大于被除数
    {
        t = t * 10;
        if(*this > t) tmp.push_back(t);
        else break;
    }
    vector <int> ans;       // 保存结果的每一位
    BigInteger re = *this;
    while(!tmp.empty())
    {
        t = tmp[tmp.size() - 1];
        for(i = 1; ; i++) { if(re - (t * i) < 0 ) break; }
        re = re - (t * (i - 1));
        ans.push_back(i - 1);
        tmp.pop_back();
    }
    // 把ans转为BigInteger
    int powTen[4] = {1, 10, 100, 1000};
    while(!ans.empty())
    {
        int x = 0;
        for(int i = 0; i < WIDTH; i++){
            if(!ans.empty()){
                x += (ans.back() * powTen[i]);
                ans.pop_back();
            }
        }
        c.s.push_back(x);
    }
    return c;
  }

  bool operator < (const BigInteger& b) const{             // 小于
    if(s.size() != b.s.size()) return s.size() < b.s.size();
    for(int i = s.size() - 1; i >= 0; i++)
        if(s[i] != b.s[i]) return s[i] < b.s[i];
    return false;      // 相等
  }
  bool operator > (const BigInteger& b) const{ return b < *this; }
  bool operator <= (const BigInteger& b) const{ return !(b < *this); }
  bool operator >= (const BigInteger& b) const{ return !(*this < b); }
  bool operator != (const BigInteger& b) const{ return (b < *this) || (*this < b); }
  bool operator == (const BigInteger& b) const{ return (!(b < *this)) && (!(*this < b)); }
};

ostream& operator << (ostream &out, const BigInteger& x) {      // 输出流
  out << x.s.back();                              // 先输入最高位
  for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[10];
    sprintf(buf, "%04d", x.s[i]);           // 修改位数 08 -> 04
    for(unsigned int j = 0; j < strlen(buf); j++) out << buf[j];
  }
  return out;
}

istream& operator >> (istream &in, BigInteger& x) {             // 输入流
  string s;
  if(!(in >> s)) return in;
  x = s;
  return in;
}

#include<set>
#include<map>
set<BigInteger> s;
map<BigInteger, int> m;
static const BigInteger ZERO = 0;

int main()
{
  BigInteger a, b;
  cin >> a >> b;
  cout << "a + b = " << a + b << "\n";
  cout << "a - b = " << a - b << "\n";
  cout << "b - a = " << b - a << "\n";
  cout << "a * b = " << a * b << "\n";
  if(b != ZERO) cout << "a / b = " << a / b << "\n";       // 存在bug
  cout << "BigInteger:BASE = " << BigInteger::BASE << "\n";
  return 0;
}


