/*
 * AC自动机是多模式匹配算法
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
 * 1. 构建trie
 * for(int i=1;i<=n;i++){
 *   string s;
 *   cin>>s;
 *   insert(s);
 * }
 * 2. 构建AC自动机
 * build();
 * 3. 查询
 * cin>>s;
 * query(s);
 */