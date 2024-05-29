#include<vector>
#include<string>

const int N=1e6+10;
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

/*
 * 特别注意：
 *   字符串是从下标 1 开始
 *
 * 使用方法：
 * string s;
 * cin>>s;
 * s="#"+s;//由于字符串从下标 1 开始
 * exkmp(s);
 */