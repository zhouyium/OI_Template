#pragma once

//特别注意：本模板不是完整代码。只是二分的框架代码
/*
 * 整数二分
 */

//以m为边界，检查是否满足题目要求
bool check(int mid){
    ...
}

/*
 * 根据单调性，二分的结果必然是左部分返回 false，右边部分返回 true
 *     000...00111...111
 *             ↑
 */
//二分的范围 [l,r)
//int l=1, r=n+1;
int bsearch(int l, int r){
    while(l<r){
        //注意，当 l,r 是负数的时候 (l+r)/2 在C++会出错。因为 C++ 负数是向零取整
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    //答案是 l 或者 l-1。
    //一般最小值的答案是 l，最大值的答案是 l-1。
    return l;//l-1;
}

/*
 * 浮点数二分
 */