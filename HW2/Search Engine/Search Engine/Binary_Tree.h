#include <string>
#include <vector>
#ifndef AVLTREE
#define AVLTREE



struct DocumentItem {
	std::string documentName;
	int count;

	DocumentItem(std::string name, int cnt = 0) : 
		documentName(name), count(cnt) {};
};

struct WordItem {
	std::string word;
	std::vector<DocumentItem> store;

	WordItem(std::string  wd) :
		word(wd) {};
};


template<class Key, class Value>
struct AVLNode {
	Value Item;
	AVLNode * left;
	AVLNode * right;
	int height;

	AVLNode(Key x, AVLNode * lf, AVLNode * rt, int hg = 0) :
		 left(lf), right(rt), height(hg) {
			this->Item = new WordItem(x);
		};
};

template <class Key, class Value>
class AVLTree {
public:
	AVLTree(const Value & notFound);
	~AVLTree();

	Value find(const Key & x);
	void insert(const Key & x);
	
	void makeEmpty();
	bool isEmpty() const;

private:
	AVLNode<Key,Value> * root;
	const Value ITEM_NOT_FOUND;

	void makeEmpty(AVLNode<Key,Value> * & t) const;

	Value find(const Key & x, AVLNode<Key,Value> * & t) const; 
	void insert(const Key & x, AVLNode<Key,Value> * & t) const;

	int height(AVLNode<Key,Value> * t) const;

	int max( int lhs, int rhs ) const;
	void rotateWithLeftChild(AVLNode<Key,Value> * & k2) const;
    void rotateWithRightChild(AVLNode<Key,Value> * & k1) const;
    void doubleWithLeftChild(AVLNode<Key,Value> * & k3) const;
    void doubleWithRightChild(AVLNode<Key,Value> * & k1) const;



};






#include "AVLTree_by_Baran_Cimen.cpp"
#endif