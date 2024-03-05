/***
https://cses.fi/problemset/task/1733/
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

#if 1
#include "vector/string/HashedString.hpp"
using namespace laozhou;
#else
class HashedString {
public:
    HashedString(int mo=998244353):_n(0),_mo(mo){}

    template <typename T>
    void init(const std::vector<T>& ar){
        _n=ar.size();
        assert(_n>0);
        //处理系数
        while(_pow.size()<_n){
            _pow.push_back(1ll*_pow.back()*_base%_mo);
        }

        //生成前缀哈希值
        pref.resize(_n+3,0);
        for (int i=1;i<=_n;i++) {
            pref[i]=(1ll*pref[i-1]*_base+ar[i-1])%_mo;
        }

        //生成后缀哈希
        suff.resize(_n+3,0);
        for(int i=_n;i>=1;i--){
            suff[i]=(1ll*suff[i+1]*_base+ar[i-1])%_mo;
        }
    }
    void init(const string &s){
        init(vector<char>(s.begin(),s.end()));
    }

    int get_hash(int l=1,int r=-1){
        if(r<0){
            r=_n;
        }
        assert(1<=l&&l<=_n&&l<=r);
        assert(1<=r&&r<=_n);
        int h=pref[r]-(1ll*_pow[r-l+1]*pref[l-1])%_mo;
        h=(h+_mo)%_mo;
        return h;
    }

    int rev_hash(int l,int r){
        int h=suff[l]-(1ll*_pow[r-l+1]*suff[r+1])%_mo;
        h=(h+_mo)%_mo;
        return h;
    }
private:
    int normal(long long x){
        return (x%_mo+_mo)%_mo;
    }

private:
    int _n;
    int _mo;
    static int _base;//底数大家可以共用
    static std::vector<int> _pow;//pow大家可以共用
    std::vector<int> pref;//前缀哈希
    std::vector<int> suff;//后缀哈希
};
vector<int> HashedString::_pow = {1};
int HashedString::_base = 13331;
#endif

void solve(){
    string s;
    cin>>s;
    HashedString hs1;
    hs1.init(s);
    int n=s.size();

    for (int i = 0; i < n; i++) {
        int curidx = 0;
        bool ok = true;
        while (curidx < n) {
            int len = min(i + 1, n - curidx);
            ok &= hs1.get_hash(0+1, len - 1+1) == hs1.get_hash(curidx+1, curidx + len - 1+1);
            curidx += len;
        }
        if (ok) { cout << i + 1 << " "; }
    }
    cout<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    while (T--){
        solve();
    }

    return 0;
}