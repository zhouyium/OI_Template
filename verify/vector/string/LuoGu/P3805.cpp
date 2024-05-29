/*
 * https://www.luogu.com.cn/problem/P3805
 * http://47.110.135.197/problem.php?id=10183
 * Manacher算法
 */
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;

/*
 * Manacher
 */
std::vector<int> d;//回文半径
void manacher(const string &s){
    //特别注意：s是处理好的字符串
    //假设原始字符串为 abcba
    //处理好的字符串为 $#a#b#c#b#a#
    int n=s.size()-1;
    //重置数组z数据
    d.assign(n+1,0);
    d[1]=1;
    for(int i=2,l,r=1; i<=n; i++){
        if(i<=r){
            d[i]=min(d[r-i+l], r-i+1);
        }
        while(s[i-d[i]]==s[i+d[i]]){
            d[i]++;
        }
        if(i+d[i]-1>r){
            l=i-d[i]+1;
            r=i+d[i]-1;
        }
    }
}

/*
 * already palindrome characters are a suffix of the belonged string.
 * If we can match it with the prefix of another string (reverse of input string)
 * then we are done (the idea of KMP).
 * strings in this way: reversed_string#input_string → lamak#kamal. (Here, input string is kamal)
 */
void solve(){
    //读取原始字符串
    string a;
    cin>>a;
    //处理字符串
    int n=a.size()+1;
    string s("$#");
    for(int i=1;i<n;i++){
        s.push_back(a[i-1]);
        s.push_back('#');
    }
    n=s.size()-1;
    //cout<<a<<"\n"<<s<<"\n";
    manacher(s);
    int ans=0;
    for(int i=1;i<=n;i++){
        ans=max(ans,d[i]);
    }
    cout<<ans-1<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    for(int i=1;i<=T;i++){
        //cout<<"Case "<<i<<": ";
        solve();
    }
    return 0;
}