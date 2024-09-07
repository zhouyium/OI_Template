# Tree

## 功能

主要是重链剖分求LCA

### 函数说明

#### void addEdge(int u, int v);

u和v之间有一个无向边

#### void init(int root = 1);

参数:

root 树根节点编号

功能:

从 root 出发，调用 dfs1 和 dfs2。

#### void dfs1(int u);

参数：

u 当前节点

功能：

计算 siz, dep, parent, son

#### void dfs2(int u, int h);

输入参数：

u:当前节点

h:节点u的重链头节点

功能：

计算 top, in, out

#### int lca(int u, int v);

输入参数：

u:节点

v:节点

输出参数

u,v 的 LCA。

功能：

使用重链剖分，求 u,v 的最近公共祖先。




## 用法

### 头文件
#include "Tree.hpp"

### 定义变量

根据题目树节点的数量，定义。

我们使用的节点编号从 $1$ 开始，$1 \sim n$。

```
TREE tr(n)
```

### 加边
tr.addEdge(u,v);//u和v之间有一个无向边




## 例子

[洛谷P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/record/176193753)

[LOJ10135 祖孙询问](https://loj.ac/s/2154009)

[LOJ10130 点的距离](https://loj.ac/s/2154011)

[CF832D Misha, Grisha and Underground](https://codeforces.com/contest/832/submission/280182797)

