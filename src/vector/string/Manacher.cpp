#include<vector>
#include<string>
/*
 * Manacher
 * d[i]表示以 i 为中心点构成回文字符串的最大半径。
 * 时间复杂度：O(n)，其中n是字符串长度
 */
std::vector<int> d;//回文半径
void manacher(const string &s){
    //特别注意：s是处理好的字符串
    //假设原始字符串为 abcba
    //处理好的字符串为 $#a#b#c#b#a#
    //字符串从下标 1 开始
    int n=s.size()-1;
    //重置数组z数据
    d.assign(n+1,0);
    d[1]=1;
    for(int i=2,l,r=1; i<=n; i++){
        //不管以i为对称中心的回文串的右边界是不是超过了r,
        //取以l ~ r的中点为对称中心的对称点的d值和到r的最小值
        if(i<=r){
            d[i]=min(d[r-i+l], r-i+1);
        }
        while(s[i-d[i]]==s[i+d[i]]){
            d[i]++;
        }
        // 判断一下超过r之后的字符是不是还是包含在以i为中心的回文串内
        if(i+d[i]-1>r){
            l=i-d[i]+1;
            r=i+d[i]-1;
        }
    }
}

/*
 * 使用方法
 * string a;
 * cin>>a;
 * //处理字符串
 * int n=a.size()+1;
 * string s("$#");
 * for(int i=1;i<n;i++){
 *   s.push_back(a[i-1]);
 *   s.push_back('#');
 * }
 * n=s.size()-1;
 * manacher(s);
 */