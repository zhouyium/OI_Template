#pragma once
/*
 * 扩欧一般用来求不定方程 a*x+b*y=c，其中 a,b,c 已知，求 x,y。
 int d=exgcd(a,b,x,y);
 if(c%d==0){
    //有解
    x*=c/d;
    y*=c/d;
    //dx, dy是满足等式两边平衡的x, y的最小变化量
    int dx=abs(b/d);
    int dy=abs(a/d);
 }else{
    //无解
 }
 */
//扩展欧几里得算法
//a*x+b*y=gcd(a,b)
int exgcd(int a, int b, int &x, int &y) {
    if (b==0) {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
//使用扩欧求逆元
//时间复杂度 O(logP)
int inv(int n, int P=1e9+7) {
    // n * x = 1 (mod M) -> n * x + M * y = 1
    int x, y;
    exgcd(n, P, x, y);
    x = (x % P + P) % P;
    return x;
}
