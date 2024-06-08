/*
 * AC自动机是多模式匹配算法
 * vector版本
 * 问题：给出若干个模式串 P（长度为n） 和一个主串 S（长度为m），问有多少个模式串在字符串 S 中出现过。
 * 以 Trie 的结构为基础，结合 KMP 的思想 建立的自动机，用于解决多模式匹配等任务。
 * 简单来说，建立一个 AC 自动机有两个步骤：
 *   1. 基础的 Trie 结构：将所有的模式串构成一棵 Trie。
 *   2. KMP 的思想：对 Trie 树上所有的结点构造失配指针。
 * 然后就可以利用它进行多模式匹配了。
 * 时间复杂度:O(n+m)
 * Ver: 1.0.0
 */

#include<vector>
#include<queue>
#include<string>
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
};
std::vector<TRIENODE> tree;

//初始化
void init(){
    //清空数据
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
            //儿子不存在，增加新节点
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

/*
 * 使用方法
 * 1. 初始化
 *   init();
 * 2. 构建trie
 * for(int i=1;i<=n;i++){
 *   string s;
 *   cin>>s;
 *   insert(s);
 * }
 * 3. 构建AC自动机
 * build();
 * 4. 查询
 * cin>>s;
 * query(s);
 */