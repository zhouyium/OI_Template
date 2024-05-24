#include<vector>
#include<string>
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
 * 特别注意：
 *   字符串是从下标 1 开始
 *
 * 使用方法：
 * string s,p;
 * cin>>s>>p;
 * s="#"+s;//由于字符串从下标 1 开始
 * kmp(s,p);
 */