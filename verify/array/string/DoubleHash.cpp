/***
https://www.luogu.com.cn/problem/P3370
http://47.110.135.197/problem.php?id=8710
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

#include <string>
#include <cassert>

template<int N=(int)5e5+10>
class HashedString {
public:
    HashedString(int base=13331, int mo=998244353){
        _n = 0;
        _base = base;
        _mo = mo;
    }
    HashedString(const std::string &s, int base=13331, int mo=998244353){
        _n = 0;
        _base = base;
        _mo = mo;
        calc(s);
    }
    void init(const std::string &s){
        _n = s.size();
        calc(s);
    }
    int get_hash(int l=1, int r=-1){
        if (r<0){
            r=_n;
        }
        assert(_n);
        assert(1<=l&&l<=_n&&l<=r);
        assert(1<=r&&r<=_n);
        int val = normal(1ll*_hash[l-1]*_pow[r-l+1]);
        val = normal(_hash[r]-val);
        return val;
    }
private:
    long long normal(int x){
        assert(_mo>0);
        return (x%_mo+_mo)%_mo;
    }
    void calc(const string &s) {
        assert(_n);
        _pow[0] = 1;
        _hash[0] = 0;
        for(int i=1;i<=_n;i++){
            _pow[i] = normal(1ll*_pow[i-1]*_base);
            _hash[i] = normal(1ll*_hash[i-1]*_base+s[i-1]);
        }
    }
private:
    int _n;//长度
    int _base;//底
    int _mo;//模
    int _pow[N];
    int _hash[N];
};

const int N=1e4+10;
HashedString<> hs1;
HashedString<> hs2(133, 1e9+7);

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
