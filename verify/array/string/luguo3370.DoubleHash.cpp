/***
https://www.luogu.com.cn/problem/P3370
http://47.110.135.197/problem.php?id=8710
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

#include "array/string/HashedString.hpp"

const int N=1e4+10;
laozhou::HashedString<> hs1;
laozhou::HashedString<> hs2(133, 1e9+7);

struct pairHash
{
    template<typename T,typename U>
    size_t operator()(const pair<T, U> & p) const
    {
        return hash<T>()(p.first) ^ hash<U>()(p.second);
    }

    template<typename T, typename U>
    bool operator() (const pair<T, U> & p1, const pair<T, U> & p2) const
    {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

unordered_map<PLL, LL, pairHash, pairHash> mp;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;

        hs1.init(s);
        int v1 = hs1.get_hash();
        hs2.init(s);
        int v2 = hs2.get_hash();
        mp[{int(v1), int(v2)}]++;
    }
    cout<<mp.size()<<"\n";
    return 0;
}