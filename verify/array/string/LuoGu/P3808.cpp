/*
 * https://www.luogu.com.cn/problem/P3808
 * http://47.110.135.197/problem.php?id=10186
 */
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
//TRIE相关数据定义
//Trie数据定义
struct NODE{
    int son[28];//叶子
    int fail;//AC自动机fail
    int end;//以自己为终点字符串出现的次数
} trie[N];
int idx=0;//控制当前插入位置

//初始化
void init(){
    //清空数据
    for(int i=0;i<=idx;i++){
        trie[i].fail=trie[i].end=0;
        for(int j=0;j<26;j++){
            trie[i].son[j]=0;
        }
    }
    idx=0;
}

//Trie树中插入字符串s
//和标准Trie一样
int insert(const std::string &s){
    int p = 0;//插入位置
    for (const auto &ch : s){
        int c = ch - 'a';
        if (trie[p].son[c]==0) {
            trie[p].son[c] = ++idx;
        }
        p = trie[p].son[c];
    }
    trie[p].end++;
    return p;
}

//使用BFS构建AC自动机，构造回跳边和转移边
//即生成nxt的值
void build(){
    std::queue<int> que;
    //BFS初始状态
    for(int i=0;i<26;i++){
        if(trie[0].son[i]){
            que.emplace(trie[0].son[i]);
        }
    }
    while(que.size()){
        int u=que.front();
        que.pop();
        for(int i=0;i<26;i++){
            int v=trie[u].son[i];
            if(!v){
                //儿子不存在
                //爹自建转移边
                trie[u].son[i]=trie[trie[u].fail].son[i];
            }else{
                //儿子存在
                //爹帮儿子建回跳边
                trie[v].fail=trie[trie[u].fail].son[i];
                //儿子入队
                que.emplace(v);
            }
        }
    }
}

//查询主串
int query(const std::string &s){
    int u=0, res=0;
    for(const char ch:s){
        u=trie[u].son[ch-'a'];//转移
        for(int j=u; j && trie[j].end!=-1; j=trie[j].fail){
            res+=trie[j].end;
            trie[j].end=-1;
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