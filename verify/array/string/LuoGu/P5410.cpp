/*
 * https://www.luogu.com.cn/problem/P5410
 * http://47.110.135.197/problem.php?id=10180
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
using LL=long long;

const int N=4e7+2;
/*
 * exKMP（Z函数）
 * z[i]表示字符串S与它第i个字符开始的后缀的最大公共前缀（LCP）长度
 * 时间复杂度：O(n)
 */
int z[N];
void exkmp(const std::string &s){
    int n=s.size()-1;
    //重置数组z数据
    memset(z, 0, (n+1)*sizeof(int));
    z[1]=n;
    for(int i=2,l=0,r=0; i<=n; i++){
        //初始化z
        if(i<=r){
            z[i]=min(z[i-l+1], r-i+1);
        }
        //暴力拓展
        while(s[i+z[i]]==s[1+z[i]]){
            z[i]++;
        }
        //更新最优区间
        if(i+z[i]-1>r){
            l=i;
            r=i+z[i]-1;
        }
    }
}

void solve(){
    string s,t,p;
    cin>>s>>t;
    LL n=t.size();
    LL m=s.size();

    p="#"+t+t;
    exkmp(p);
    LL res1=0;
    for(LL i=n+1;i<=2*n;i++){
        res1^=(i-n)*(min(z[i]*1ll,n)+1);
    }
    cout<<res1<<"\n";

    p="#"+t+s;
    exkmp(p);
    LL res2=0;
    for(LL i=n+1;i<=n+m;i++){
        res2^=(i-n)*(min(z[i]*1ll,n)+1);
    }
    cout<<res2<<"\n";
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