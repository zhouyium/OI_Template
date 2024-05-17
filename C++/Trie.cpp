#include<bits/stdc++.h>
#include<string>
using namespace std;
class TRIE{
public:
  //N is number of possible characters in a string
  const static int N=26;
  //baseChar defines the base character for possible characters
  //like '0' for '0','1','2'... as possible characters in string
  const static char baseChar='a';
  struct TrieNode{
    int next[N];
    //if isEnd is set to true , a string ended here
    bool isEnd;
    //freq is how many times this prefix occurs
    int freq;
public:
    TrieNode(){
      for(int i=0;i<N;i++){
        next[i]=-1;
      }
      isEnd=false;
      freq=0;
    }
  };
  std::vector<TrieNode> tree;

  //Base Constructor
  TRIE(){
    tree.push_back(TrieNode());
  }

  //inserting a string in trie
  void insert(const std::string &s){
    int p=0;
    tree[p].freq++;
    for(const auto &ch:s){
      int t=ch-baseChar;
      if(tree[p].next[t]==-1){
        tree.push_back(TrieNode());
        tree[p].next[t]=tree.size()-1;
      }
      p=tree[p].next[t];
      tree[p].freq++;
    }
    tree[p].isEnd=true;
  }

  //check if a string exists as prefix
  int findPrefix(const std::string &s){
    int p=0;
    for(const auto &ch:s){
      int t=ch-baseChar;
      if(tree[p].next[t]==-1){
        return 0;
      }
      p=tree[p].next[t];
    }
    return tree[p].freq;
  }

  //check is string exists
  int find(const std::string &s){
    int p=0;
    for(const auto &ch:s){
      int t=ch-baseChar;
      if(tree[p].next[t]==-1){
        return 0;
      }
      p=tree[p].next[t];
    }
    if(tree[p].isEnd){
    	return tree[p].freq;
	}else{
		return 0;
	}
  }

  //persistent insert
  //returns location of new head
  int persistentInsert(int head, const std::string &s){
    int old=head;
    tree.push_back(TrieNode());
    int now=tree.size()-1;
    int newHead=now;

    for(const auto &ch:s){
      int t=ch-baseChar;
      if(old==-1){
        tree.push_back(TrieNode());
        tree[now].next[t]=tree.size()-1;
        tree[now].freq++;
        now=tree[now].next[t];
        continue;
      }

      for(int j=0;j<N;j++){
        tree[now].next[j]=tree[old].next[j];
      }
      tree[now].freq=tree[old].freq;
      tree[now].isEnd=tree[old].isEnd;
      tree[now].freq++;
      tree.push_back(TrieNode());
      tree[now].next[t]=tree.size()-1;

      old=tree[old].next[t];
      now=tree[now].next[t];
    }
    tree[now].freq++;
    tree[now].isEnd=true;
    return newHead;
  }

  //persistent check prefix
  int persistentFindPrefix(int head, const std::string &s){
    int p=head;
    for(const auto &ch:s){
      int t=ch-baseChar;
      if(tree[p].next[t]==-1){
        return 0;
      }
      p=tree[p].next[t];
    }
    return tree[p].freq;
  }

  //persistent check string
  int persistentFind(int head, const std::string &s){
    int p=head;
    for(const auto &ch:s){
      int t=ch-baseChar;
      if(tree[p].next[t]==-1){
        return 0;
      }
      p=tree[p].next[t];
    }
    if(tree[p].isEnd){
    	return tree[p].freq;
	}else{
		return 0;
	}
  }
};

string s,temp;
int main()
{
    TRIE trie = TRIE();

    cout << trie.find("hello") << "\n";	//output : 0

    trie.insert("hello");
    cout << trie.findPrefix("hell") << "\n";	//output : 1
    cout << trie.find("hell") << "\n";	//output : 0
    cout << trie.find("hello") << "\n";	//output : 1
    trie.insert("hello");
    cout << trie.find("hello") << "\n";	//output : 2
    trie.insert("hello");
    cout << trie.find("hello") << "\n";	//output : 3
    trie.insert("hello");
    cout << trie.find("hello") << "\n";	//output : 4
    trie.insert("hello");
    cout << trie.find("hello") << "\n";	//output : 5


    //Example for persistent trie 
    TRIE persistentTrie = TRIE();
    vector <int> heads;

    //insert words 
    heads.push_back(0);
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "hello"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "world"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "persistent"));
    heads.push_back(persistentTrie.persistentInsert(heads[heads.size()-1] , "trie"));

    cout << persistentTrie.persistentFind(heads[0] , "hello") << "\n";	//output : 0
    cout << persistentTrie.persistentFind(heads[1] , "hello") << "\n";	//output : 1

    cout << persistentTrie.persistentFind(heads[1] , "world") << "\n";	//output : 0
    cout << persistentTrie.persistentFind(heads[2] , "world") << "\n";	//output : 1

    cout << persistentTrie.persistentFind(heads[2] , "persistent") << "\n";	//output : 0
    cout << persistentTrie.persistentFind(heads[3] , "persistent") << "\n";	//output : 1

    cout << persistentTrie.persistentFind(heads[3] , "trie") << "\n";	//output : 0
    cout << persistentTrie.persistentFind(heads[4] , "trie") << "\n";	//output : 1

    
    return 0;
}