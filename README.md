# OI_Template
 OI相关的模板。计算写两个版本，一个数组版本，一个基于std::vector。

# 目录结构
OI_Template

│   README.md

├───document_ch

├───document_en

├───src

│   ├───array

│   │   └───string

│   │           HashedString.hpp

│   └───vector

└───verify

│   └───array

│       └───string

│   │          DoubleHash.cpp

│   │          SingleHash.cpp

# 数组版本
## 文件
<table width="500px">
<tr><th width="10%">文件名</th><th width="30%">功能</th><th width="40%">使用方法</th><th width="20%">模板题</th></tr>
<tr>
    <th>HashedString.hpp</th>
    <th>单模数字符串哈希</th>
    <th>
        <pre align="left">
            <code>
HashedString<> hs1("abcd"); //缺省长度(5e5),缺省底数(13331),缺省模数(998244353)
int val=hs1.get_hash();//获得"abcd"的哈希结果
val=hs1.get_hash(2);//获得"bcd"的哈希结果
val=hs2.get_hash(2,3);//获得"bc"的哈希结果
            </code>
        </pre>
    </th>
    <th></th>
</tr>
</table>