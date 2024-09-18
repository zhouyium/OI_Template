#pragma once

/**
 * 维护字符串的集合。提供两种操作：
 * 1. 插入字符串
 * 2. 查询字符串出现的次数
 * 时间复杂度 O(N)
 * 需要外部提供 N 的大小
 */
#include<string>
#include<string>
struct TRIE{
    static const int M = 127;
    static const char BASE=' ';//空格开始为可见字符
    int trie[N][M]={};//存储从节点 p 沿着 j 这条边走到的子节点
    int fail[N]={};//存储以节点 p 结尾的单词插入的次数。
    int freq[N]={};//存储以节点 p 结尾的前缀插入的次数。
    int tot = 0;//当前操作位置
    int maxp = 0;
    /*这个部分增加额外数据*/
    /*这个部分增加额外数据*/

    TRIE(){
        init();
    }

    void init(){
        for(int i=0;i<=maxp;i++){
            fail[i]=freq[i]=0;
            for(int j=0;j<M;j++){
                trie[i][j]=0;
            }
        }
        tot=0;
    }

    //插入字符串 s
    void insert(const std::string &s) {
        int p=0;
        for (auto ch : s) {
            int t=ch-BASE;
            assert(0<=t && t<M);
            if (!trie[p][t]) {
                //字母映射没有出现
                trie[p][t]=++tot;
            }
            p=trie[p][t];
            freq[p]++;
        }
        //这里我们统计的是整个单词出现次数。如果是统计前缀，将这个部分放到循环内即可。
        fail[p]++;
        maxp=max(maxp,p);
    }

    //前缀查找
    int queryPrefix(const std::string &s){
        int p=0;
        for(auto ch : s){
            int t=ch-BASE;
            assert(0<=t && t<M);
            if(!trie[p][t]){
                return 0;
            }
            p=trie[p][t];
        }
        return freq[p];
    }

    //查询字符串 s 出现的次数
    int query(const std::string &s) {
        int p=0;
        for (auto ch : s)  {
            int t=ch-BASE;
            assert(0<=t && t<M);
            if (!trie[p][t]) {
                return 0;
            }
            p=trie[p][t];
        }
        return fail[p];
    }
};
