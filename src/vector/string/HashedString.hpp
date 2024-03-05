#pragma once

#include <vector>
#include <string>
#include <cassert>

namespace laozhou {
/**
 @brief 单模字符串哈希
 @section HashedString
 @section 用法
 HashedString<> hs1; //缺省长度(5e5)
 hs1.init("abcd");
 int val=hs1.get_hash();//获得"abcd"的哈希结果
 val=hs1.get_hash(2);//获得"bcd"的哈希结果
 val=hs2.get_hash(2,3);//获得"bc"的哈希结果

 HashedString<10010> hs2; //长度为10,000
 HashedString<10010> hs3("ab");
 HashedString<10010> hs4("ab",131,1e9+7);
 ***/
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
}
