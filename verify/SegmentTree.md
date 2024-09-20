# Segment Tree

## Feature

单点修改。

单点查询。

区间查询。

## Usage

### 特别注意

本模板存储的线段树和标准线段树不一样。

标准线段树的范围是 [1, n]。

本模板线段树的范围是 [0, n)。即节点从 0 开始计算。

### 包含命名空间

using namespace lz;

### 修改代码



这个部分代码需要根据具体题目确定。主要工作如下。

1. 根据题目要求，修改结构体 Info

```C++
struct Info {
    //to add 根据题目定义需要维护的数据
    //本例我们维护：和，最大值
    int sum;//和
    int mx;//最大值
    //缺省构造函数
    Info(){
        //to add
        sum = 0;
        mx  = -INF;
    }
    //带参数构造函数
    Info(int val){
        //to add
        sum = mx =val;
    }
};
```

2. 实现 merge() 函数或者重载 operator+

```C++
Info merge(const Info &n1, const Info &n2);

Info operator+(Info a, Info b) {
    Info c;
    // 对 a（左儿子） 和 b（右儿子） 一通操作合成 c（父结点）
    // to do
    c.sum = a.sum + b.sum;
    c.mx  = std::max(a.mx, b.mx);
    return c;
}
```

该函数用于将节点 p 的左儿子 2*p 和右儿子 2*p+1 合并称为一个新的 Info。

该函数用于 pull_up(), query() 函数。

### 构造 Info 数据
根据题目要求，读取数据，并构造 vector<Info> 数据。

该数据将用于初始化线段树。

特别注意，```C++ vector<Info> ``` 从下标零开始。

下面是一个简单的构造例子。

```C++
vector<Info> ve(n);
for(int i=1;i<=n;i++){
    int x;
    cin>>x;
    ve[i]=SegmentTree::Info();
    ve[i].sum=x;
}

```

### 初始化线段树

可以根据构造的 ```C++ vector<Info> ``` 来初始化线段树。
```C++
SegmentTree<Info> sgt(ve);
```

可以初始化空线段树。
```C++
//本例初始化 100 个节点的线段树
SegmentTree<Info> sgt(100);
```

### 单点修改数据

```C++
Info val(5);
sgt.modify(pos, val);
```

### 查询

特别注意，查询的区间为 [l,r)
```C++
int l=1;
int r=3;
Info res=sgt.rangeQuery(l, r);
```

## 例题

### 基础题

[查询区域和](https://paste.ubuntu.com/p/3wzfybXvZG/)

[查询区域最大值](https://paste.ubuntu.com/p/WdHzQr4vbg/)

[查询区域最小值和出现次数](https://paste.ubuntu.com/p/VRHR9XWnSJ/)

[CF EDU A. Segment Tree for the Sum](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/281929346)

[CF EDU B. Segment Tree for the Minimum](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/281930695)

[CF EDU C. Number of Minimums on a Segment](https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/submission/281931340)

### 进阶题

[SPOJ GSS1](https://paste.ubuntu.com/p/8yrdw83zRN/)

[CF1696 G. Fishingprince Plays With Array Again](https://codeforces.com/contest/1696/submission/281310638)
