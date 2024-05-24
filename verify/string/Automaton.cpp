/*
 * https://www.luogu.com.cn/problem/P3808
 * http://47.110.135.197/problem.php?id=10186
 */
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
//TRIE相关数据定义
int trie[N][26];//Trie定义
int cnt[N];//cnt[i]表示第i个字符串的节点位置，即以i为终止节点的字符串出现的次数
int idx=0;//控制当前插入位置

//KMP定义
int nxt[N];//nxt[i]表示i号节点结尾的字符串的最大后缀

//Trie树中插入字符串s
//和标准Trie一样
int insert(const std::string &s){
    int p = 0;//插入位置
    for (const auto &ch : s){
        int c = ch - 'a';
        if (!trie[p][c]) {
            trie[p][c] = ++idx;
        }
        p = trie[p][c];
    }
    cnt[p]++;
    return p;
}

//使用BFS构建AC自动机，构造回跳边和转移边
//即生成nxt的值
void build(){
    std::queue<int> que;
    //BFS初始状态
    for(int i=0;i<26;i++){
        if(trie[0][i]){
            que.push(trie[0][i]);
        }
    }
    while(que.size()){
        int u=que.front();
        que.pop();
        for(int i=0;i<26;i++){
            int v=trie[u][i];
            if(!v){
                //儿子不存在
                //爹自建转移边
                trie[u][i]=trie[nxt[u]][i];
            }else{
                //儿子存在
                //爹帮儿子建回跳边
                nxt[v]=trie[nxt[u]][i];
                //儿子入队
                que.push(v);
            }
        }
    }
}

int query(const std::string &s){
    int u=0, res=0;
    for(const char ch:s){
        u=trie[u][ch-'a'];//转移
        for(int j=u; j && cnt[j]!=-1; j=nxt[j]){
            res+=cnt[j];
            cnt[j]=-1;
        }
    }
    return res;
}

void solve(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        string p;
        cin>>p;
        insert(p);
    }
    build();

    string s;
    cin>>s;
    cout<<query(s)<<"\n";
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