#include <string>
template<int N=(int)5e5+10>
struct TRIE {
  int _son[N][26]={}, _idx=0;
  int _cnt[N]={};//cnt[i]表示节点为i的出现次数 

  void insert(const std::string &s) {  // 插入字符串
    int p=0;
    for (const auto &ch : s) {
        int t=ch-'a';
        if (!_son[p][t]) {
            _son[p][t]=++_idx;// 如果没有，就添加结点
        }
        p=_son[p][t];
        //_cnt[p]++; //标记以当前字符为结尾的字符串出现的次数 
    }
    _cnt[p]++; //标记以当前字符为结尾的字符串出现的次数 
  }

  int find(const std::string &s) {  // 查找字符串
    int p=0;
    for (const auto &ch : s) {
        int t=ch-'a';
        if (!_son[p][t]) {
            return 0;
        }
        p=_son[p][t];
    }
    return _cnt[p];
  }
};