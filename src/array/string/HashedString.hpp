#pragma once

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
        long long normal(long long x){
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
}
