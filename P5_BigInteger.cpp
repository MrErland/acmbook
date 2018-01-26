
/*
《算法竞赛入门经典（第二版）》第5章 第3节 高精度非负整数类
 Origin Code: 赋值运算符、输出流、输入流，加法运算
 Version: 0.0
 Date: 2018.1.26
*/

#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;

struct BigInteger {
  static const int BASE = 100000000;
  static const int WIDTH = 8;
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

  BigInteger operator = (const string& str) {           // 赋值运算符
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
      int end = str.length() - i*WIDTH;            // 每8位子串的尾部
      int start = max(0, end - WIDTH);             // 每8位子串的头部
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
};

ostream& operator << (ostream &out, const BigInteger& x) {      // 输出流
  out << x.s.back();                              // 先输入最高位
  for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[20];
    sprintf(buf, "%08d", x.s[i]);
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

int main() {
  BigInteger a, b;
  cin >> a >> b;
  cout << a + b << "\n";
  cout << BigInteger::BASE << "\n";
  return 0;
}


