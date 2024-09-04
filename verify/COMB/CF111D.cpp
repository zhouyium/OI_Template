//https://codeforces.com/contest/111/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ull = unsigned long long;
using PII = pair<int,int>;

/*梅森旋转器*/
random_device rd;
mt19937 mt(rd());

const int N=2e5+10;

template<class T>
constexpr T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(int x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1ll * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        int v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 1;
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
constexpr int P = 1000000007;
using Z = MInt<P>;

struct COMB {
    int _n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    COMB() : _n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    COMB(int n) : COMB() {
        init(n);
    }

    void init(int m) {
        if (m <= _n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = _n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > _n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        _n = m;
    }

    Z fac(int m) {
        if (m > _n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > _n) {
            init(2 * m);
        }
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > _n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

void solve(){
    int n,m,K;
    cin>>n>>m>>K;
    std::vector<vector<Z>> S(n + 1, std::vector<Z>(n + 1));
    for(int i=0;i<=n;i++){
        S[i][0]=(!i);
        for(int j=1;j<=i;j++){
            S[i][j]=S[i-1][j]*j+S[i-1][j-1];
        }
    }
    if(m==1){
        cout<<power(Z(K),n)<<"\n";
        return;
    }

    Z ans=0;
    for(int i=0;i<=n;i++){
        for(int j=0;i+j<=n;j++){
            ans+=comb.binom(K,i)*comb.binom(K-i,j)*comb.binom(K-i-j,j)*comb.fac(i+j)*comb.fac(i+j)*S[n][i+j]*S[n][i+j]*power(Z(i),n*(m-2));
        }
    }
    cout<<ans<<"\n";
}

signed main(){
#if 1
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif

    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
