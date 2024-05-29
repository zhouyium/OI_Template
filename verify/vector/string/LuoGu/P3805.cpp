/*
 * https://www.luogu.com.cn/problem/P3805
 * http://47.110.135.197/problem.php?id=10183
 * Manacher算法
 */
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;

/*
 * KMP
 */
std::vector<int> nxt;
//求next数组
void kmp_next(const std::string &p){
    //注意，我们使用字符串从下标1开始
    int m=p.size()-1;

    //重置数组数据
    nxt.assign(m+1,0);
    for(int i=2,j=0; i<=m; i++){
        while(j && p[i]!=p[j+1]){
            //找到最长的前后缀重叠长度
            j=nxt[j];
        }
        if(p[i]==p[j+1]){
            j++;
        }
        nxt[i]=j;
    }
}

//匹配操作
int kmp(const std::string &s, const std::string &p){
    int cnt=0;
    kmp_next(p);

    //注意，我们使用字符串从下标1开始
    int n=s.size()-1;
    int m=p.size()-1;
    for(int i=1,j=0; i<=n; i++){
        while(j && s[i]!=p[j+1]){
            //不匹配，利用next往回跳
            j=nxt[j];
        }
        if(s[i]==p[j+1]){
            //匹配，则匹配下一位
            j++;
        }
        if(j==m){
            //满足匹配条件
            //根据题目处理，比如输出答案之类
            //cout<<i-m<<" ";
            cnt++;
            j=nxt[j];//再次匹配
        }
    }
    return cnt;
}

/*
 * exKMP
 */
std::vector<int> z;
void exkmp(const std::string &s){
    int n=s.size()-1;
    //重置数组z数据
    z.assign(n+1,0);
    z[1]=n;
    for(int i=2,l=0,r=0; i<=n; i++){
        if(i<=r){
            z[i]=min(z[i-l+1], r-i+1);
        }
        while(s[i+z[i]]==s[1+z[i]]){
            z[i]++;
        }
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
}

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