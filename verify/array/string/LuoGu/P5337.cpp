/*
 * https://www.luogu.com.cn/problem/P5337
 * http://47.110.135.197/problem.php?id=10188
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;

/*
 * 根据题目说明
 * N=2e5+10
 * AC自动机+DFS
*/
const int N=2e5+10;
//AC自动机数据结构
//在Trie中增加了 fail 指针
struct TRIENODE{
    int son[28];//叶子
    int fail;//AC自动机fail
    int end;//以自己为终点字符串出现的次数
    int num;//答案
    //缺省构造函数
    TRIENODE(){
        fail=end=0;
        for(int i=0;i<26;i++){
            son[i]=0;
        }
    }
} tree[N];
int idx=0;//Trie指针
vector<int> adj[N];

//初始化
void init(){
    //清空数据
    for(int i=0;i<=idx;i++){
        tree[i].fail=tree[i].end=0;
        tree[i].num=0;
        for(int j=0;j<26;j++){
            tree[i].son[j]=0;
        }
    }
    idx=0;
}

//Trie树中插入字符串s
//和标准Trie一样
int insert(const std::string &s, int id){
    int p = 0;//插入位置
    for (const auto &ch : s){
        int c = ch - 'a';
        if(tree[p].son[c]==0){
            //儿子不存在，增加新节点
            tree[p].son[c]=++idx;
        }
        p = tree[p].son[c];
    }
    tree[id].end=p;
    return p;
}

//使用BFS构建AC自动机，构造回跳边和转移边
//即生成nxt的值
void build(){
    std::queue<int> que;
    //BFS初始状态
    for(int i=0;i<26;i++){
        if(tree[0].son[i]>0){
            //tree[tree[0].son[i]].fail=0;//指向根节点
            que.emplace(tree[0].son[i]);
        }
    }
    while(que.size()){
        int p=que.front();
        que.pop();
        for(int i=0;i<26;i++){
            int v=tree[p].son[i];
            if(v==0){
                //儿子不存在
                //爹自建转移边
                tree[p].son[i]=tree[tree[p].fail].son[i];
            }else{
                //儿子存在
                //爹帮儿子建回跳边
                tree[v].fail=tree[tree[p].fail].son[i];
                //儿子入队
                que.emplace(v);
            }
        }
    }
}

//查询主串
int query(const std::string &s){
    int p=0, res=0;
    for(const char ch:s){
        p=tree[p].son[ch-'a'];//转移
        tree[p].num++;
    }
    return res;
}

void dfs(int u){
    for(const auto &v:adj[u]){
        if(v==u){
            continue;
        }
        dfs(v);
        tree[u].num+=tree[v].num;
    }
}

void solve(){
    //初始化
    int n;
    cin>>n;
    //初始化
    init();
    string s;
    //模式串
    for(int i=1;i<=n;i++){
        cin>>s;
        insert(s,i);
    }
    build();

    //查询主串
    cin>>s;
    query(s);
    for(int i=1;i<=idx;i++){
        adj[tree[i].fail].push_back(i);
    }
    dfs(0);

    for(int i=1;i<=n;i++){
        cout<<tree[tree[i].end].num<<"\n";
    }
    cout<<"\n";
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