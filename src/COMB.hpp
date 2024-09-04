#pragma once
/*
 * Code for Combination
 */
#include <vector>

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
};

/* How to use
 * 1. define Z
 *  If we use modint.
#include "MInt.hpp"
constexpr int P = 998244353;
using Z = MInt<P>;

 *  If we use int
using Z = int;
 *
 *  2. define a variable
#include "COMB.hpp"
COMB comb;
 * */