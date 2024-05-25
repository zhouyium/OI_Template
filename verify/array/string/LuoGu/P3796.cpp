/*
 * https://www.luogu.com.cn/problem/P3796
 * http://47.110.135.197/problem.php?id=10187
 */
#include<bits/stdc++.h>
using namespace std;

/*
 * 根据题目说明
 * N=150, len=70
 * N*len=150*70=10,500=1.05e4
*/
const int N=1.06e4+10;
//AC自动机数据结构
//在Trie中增加了 fail 指针
struct TRIENODE{
    int son[28];//叶子
    int fail;//AC自动机fail
    int end;//以自己为终点字符串出现的次数
    //缺省构造函数
    TRIENODE(){
        fail=end=0;
        for(int i=0;i<26;i++){
            son[i]=0;
        }
    }
} tree[N];
int idx=0;//Trie指针
struct RESULT{
    int num;
    int pos;
} ans[N];//所有单词出现次数

//初始化
void init(){
    //清空数据
    for(int i=0;i<=idx;i++){
        tree[i].fail=tree[i].end=0;
        for(int j=0;j<26;j++){
            tree[i].son[j]=0;
        }
        ans[i].num=ans[i].pos=0;
    }
    idx=0;
}

//Trie树中插入字符串s
//和标准Trie一样
int insert(const std::string &s, int num){
    int p = 0;//插入位置
    for (const auto &ch : s){
        int c = ch - 'a';
        if(tree[p].son[c]==0){
            //儿子不存在，增加新节点
            tree[p].son[c]=++idx;
        }
        p = tree[p].son[c];
    }
    tree[p].end=num;
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
        for(int j=p; j; j=tree[j].fail){
            ans[tree[j].end].num++;
        }
    }
    return res;
}

bool mycmp(const RESULT &t1, const RESULT &t2){
    if(t1.num!=t2.num){
        return t1.num>t2.num;
    }else{
        return t1.pos<t2.pos;
    }
}

string s[N];
void solve(){
    //初始化
    int n;
    while (cin>>n){
        if(n==0){
            break;
        }

        //初始化
        init();
        //模式串
        for(int i=1;i<=n;i++){
            cin>>s[i];
            ans[i].num=0;
            ans[i].pos=i;
            insert(s[i],i);
        }
        build();

        //查询主串
        cin>>s[0];
        query(s[0]);

        //排序答案
        sort(ans+1, ans+n+1, mycmp);
        cout<<ans[1].num<<"\n";
        cout<<s[ans[1].pos]<<"\n";
        for(int i=2;i<=n;i++){
            if(ans[i].num==ans[i-1].num){
                cout<<s[ans[i].pos]<<"\n";
            }else{
                break;
            }
        }
    }
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