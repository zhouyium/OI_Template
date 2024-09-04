#pragma once

// assume -P <= x < 2P
int norm(int x, int P=1e9+7) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}

//快速幂
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