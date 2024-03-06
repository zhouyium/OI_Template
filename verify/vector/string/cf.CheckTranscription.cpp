/***
https://codeforces.com/problemset/problem/1056/E
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
    HashedString(int mo=998244353):_n(0),_mo(mo){
        pref.push_back(0);
    }

    template <typename T>
    void init(const std::vector<T>& ar){
        _n=ar.size();
        assert(_n>0);
        //处理系数
        while(_pow.size()<_n){
            _pow.push_back(normal(1ll*_pow.back()*_base));
        }

        //生成前缀哈希值
        pref.resize(_n+3,0);
        for (int i=1;i<=_n;i++) {
            pref[i]=normal(normal(1ll*pref[i-1]*_base)+ar[i-1]%_mo);
        }

        //生成后缀哈希
        suff.resize(_n+3,0);
        for(int i=_n;i>=1;i--){
            suff[i]=normal(normal(1ll*suff[i+1]*_base)+ar[i-1]%_mo);
        }
    }
    void init(const string &s){
        init(vector<char>(s.begin(),s.end()));
    }
    void add(long long x){
        _n++;
        //处理系数
        while(_pow.size()<_n){
            _pow.push_back(normal(1ll*_pow.back()*_base));
        }

        //生成前缀哈希值
        if(pref.size()==0){
            pref.resize(_n,0);
        }
        int t=normal(normal(1ll*pref[_n-1]*_base)+x%_mo);
        pref.push_back(t);
    }
    void pop_back(){
        if(_n>0){
            _n--;
            pref.pop_back();
        }
    }

    int get_hash(int l=1,int r=-1){
        if(r<0){
            r=_n;
        }
        assert(1<=l&&l<=_n&&l<=r);
        assert(1<=r&&r<=_n);
        int h=normal(pref[r]-normal(1ll*_pow[r-l+1]*pref[l-1]));
        return h;
    }

    int rev_hash(int l=-1,int r=1){
        if(l<0){
            l=_n;
        }
        assert(1<=l&&l<=_n&&l>=r);
        assert(1<=r&&r<=_n);
        int h=normal(suff[l]-normal(1ll*_pow[r-l+1]*suff[r+1]));
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
    string a,b;
    cin>>a>>b;

    int n=a.size();
    int m=b.size();

    HashedString hs2;
    hs2.init(b);

    LL cnt1=count(a.begin(),a.end(),a[0]);
    LL cnt2=a.size()-cnt1;
    LL ans=0;
    for(LL len1=1;len1<=m;len1++){
        if((b.size()-cnt1*len1)%cnt2!=0){
            continue;
        }
        LL len2=(b.size()-cnt1*len1)/cnt2;
        if(len2<=0){
            break;
        }

        LL h1=-1, h2=-1;
        LL l=0;
        bool valid=true;
        for(LL i=0;i<n;i++){
            if(a[i]==a[0]){
                LL v1=hs2.get_hash(l+1,l+len1);
                if(h1!=v1 && h1!=-1){
                    valid=false;
                    break;
                }else{
                    h1=v1;
                }
                l+=len1;
            }else{
                LL v2=hs2.get_hash(l+1,l+len2);
                if(h2!=v2 && h2!=-1){
                    valid=false;
                    break;
                }else{
                    h2=v2;
                }
                l+=len2;
            }
        }
        if(h1==h2){
            valid=false;
        }
        ans+=valid;
    }
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //freopen("censor.in","r",stdin);
    //freopen("censor.out","w",stdout);
    int T=1;
    //cin>>T;
    while (T--){
        solve();
    }

    return 0;
}