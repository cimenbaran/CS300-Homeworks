#include <string>
#include <vector>
#ifndef BINARY_TREE
#define BINARY_TREE



struct DocumentItem {
	std::string documentName;
	int count;

	DocumentItem(std::string name, int cnt = 0) : 
		documentName(name), count(cnt) {};
};

struct WordItem {
	std::string word;
	std::vector<DocumentItem> store;

	WordItem() {};

	WordItem(std::string  wd) :
		word(wd) {};

	bool operator==(WordItem & rhs) {
		if(this->word == rhs.word) 
			return true;
		return false;
	}
	bool operator<=(WordItem & rhs) {
		if(this->word <= rhs.word) 
			return true;
		return false;
	}
	bool operator>=(WordItem & rhs) {
		if(this->word >= rhs.word) 
			return true;
		return false;
	}
	bool operator<(WordItem & rhs) {
		if(this->word < rhs.word) 
			return true;
		return false;
	}
	bool operator>(WordItem & rhs) {
		if(this->word > rhs.word) 
			return true;
		return false;
	}
	WordItem &operator=(WordItem & rhs) {
		this->store = rhs.store;
		this->word = rhs.word;
		return *this;
};
	
};



bool operator!=(const WordItem & lhs, const WordItem & rhs) {
		return (lhs.word != rhs.word);
};


template<class Key, class Value>
struct TreeNode {
	Value Item;
	TreeNode * left;
	TreeNode * right;

	TreeNode(Key x, TreeNode * lf, TreeNode * rt) :
		 left(lf), right(rt) {
			this->Item = new WordItem(x);
		};
};

template <class Key, class Value>
class BinaryTree {
public:
	BinaryTree(const Value & notFound);
	~BinaryTree();

	Value find(const Key & x);
	void insert(const Key & x);
	
	void makeEmpty();
	bool isEmpty() const;

private:
	TreeNode<Key,Value> * root;
	const Value ITEM_NOT_FOUND;

	void makeEmpty(TreeNode<Key,Value> * & t) const;

	Value find(const Key & x, TreeNode<Key,Value> * & t) const; 
	void insert(const Key & x, TreeNode<Key,Value> * & t) const;

};






#include "Binary_Tree_by_Baran_Cimen.cpp"
#endif