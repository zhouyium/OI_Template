/*
 * https://www.luogu.com.cn/problem/P3375
 * http://47.110.135.197/problem.php?id=6772
 * 字符串 KMP 和 exKMP 相关
 * KMP算法
 * 输入参数：
 *   s  模式字符串，字符串长度为 N
 *   p  匹配字符串，字符串长度为 M
 *   特别注意，字符串从下标 1 开始。
 * 输出
 *   next数组，长度和字符串 p 一样。
 */
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;

/*
 * KMP
 * nxt[i]表示字串 s[1...i] 最长的相等的真前缀与真后缀的长度。
 * 时间复杂度：O(n+m)，其中n是搜索串长度，m是模式串长度
 */
int nxt[N];
//求next数组
void kmp_next(const std::string &p){
    //注意，我们使用字符串从下标1开始
    int m=p.size()-1;

    //重置数组数据
    nxt[0]=0;
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
            cout<<i-m+1<<"\n";
            cnt++;
            j=nxt[j];//再次匹配
        }
    }
    return cnt;
}

void solve(){
    int n;
    string s,p;
    cin>>s>>p;
    s="#"+s;
    p="#"+p;
    kmp(s,p);

    for(int i=1;i<p.size();i++){
        cout<<nxt[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}