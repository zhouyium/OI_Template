# Segment Tree

## Feature

单点修改。

单点查询。

区间查询。

## Usage

### 包含命名空间

using namespace lz;

### 修改代码

这个部分代码需要根据具体题目确定。主要工作如下。

1. 修改结构体 Info

2. 重载 operator+

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

```C++
SegmentTree::init(ve);
```

### 单点修改数据

```C++
int pos=3;
Info c;
c.sum=5;
SegmentTree::modify(pos, c);
```

### 查询

```C++
int l=1;
int r=3;
Info res=SegmentTree::query(l, r);
```

## 例题

### 基础题

[创建线段树](https://paste.ubuntu.com/p/JQ5Jtp6Bs2/)

[单点更新](https://paste.ubuntu.com/p/KRncMTnnNv/)

[查询区域和](https://paste.ubuntu.com/p/R4NYq2HcVf/)

[查询区域最大值和出现次数](https://paste.ubuntu.com/p/mG7YtRQhFP/)
