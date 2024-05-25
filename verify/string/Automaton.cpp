/*
 * https://www.luogu.com.cn/problem/P3808
 * http://47.110.135.197/problem.php?id=10186
 */
#include<bits/stdc++.h>
using namespace std;

const int N=1e6+10;
//TRIE相关数据定义
//Trie数据定义
struct TRIENODE{
    int son[28];//叶子
    int fail;//AC自动机fail
    int end;//以自己为终点字符串出现的次数
    //缺省构造函数
    TRIENODE(){
        for(int i=0;i<26;i++){
            son[i]=0;
            fail=0;
            end=0;
        }
    }
};
std::vector<TRIENODE> tree;
int idx=0;//控制当前插入位置

//初始化
void init(){
    tree.clear();
    //插入第一个节点
    tree.push_back(TRIENODE());
}
//Trie树中插入字符串s
//和标准Trie一样
int insert(const std::string &s){
    int p = 0;//插入位置
    for (const auto &ch : s){
        int c = ch - 'a';
        if(tree[p].son[c]==0){
            tree.push_back(TRIENODE());
            tree[p].son[c]=tree.size()-1;
        }
        p = tree[p].son[c];
    }
    tree[p].end++;
    return p;
}

//使用BFS构建AC自动机，构造回跳边和转移边
//即生成nxt的值
void build(){
    std::queue<int> que;
    //BFS初始状态
    for(int i=0;i<26;i++){
        if(tree[0].son[i]>0){
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
        for(int j=p; j && tree[j].end>0; j=tree[j].fail){
            res+=tree[j].end;
            tree[j].end=0;
        }
    }
    return res;
}

void solve(){
    //初始化
    init();
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