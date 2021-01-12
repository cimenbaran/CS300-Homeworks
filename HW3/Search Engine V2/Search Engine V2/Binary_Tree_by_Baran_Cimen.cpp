#ifndef BINARY_TREE
#include "Binary_Tree_by_Baran_Cimen.h"
#endif


// PUBLIC

template<class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(const Value & notFound):
		ITEM_NOT_FOUND(notFound), root(NULL) {};

template<class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree() {
	makeEmpty();
};


template<class Key, class Value>
Value BinaryTree<Key, Value>::find(const Key & key) {
	return find(key,root);
}


template<class Key, class Value>
void BinaryTree<Key, Value>::insert(const Key & x) {
	insert(x,root);
};

template<class Key, class Value>
void BinaryTree<Key, Value>::makeEmpty() {
	makeEmpty(root);
};


template<class Key, class Value>
bool BinaryTree<Key, Value>::isEmpty() const {
	return root == NULL;
};




// PRIVATE



template<class Key, class Value>
void BinaryTree<Key, Value>::makeEmpty(TreeNode<Key,Value> * & t) const {
	if(t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t->Item;
		delete t;
	}
	t = NULL;
};





template<class Key, class Value>
Value BinaryTree<Key,Value>::find(const Key & x, TreeNode<Key,Value> * & t) const {
	if(t == NULL) {
		return ITEM_NOT_FOUND;
	}
	if(x < t->Item->word) {
		return find(x, t->left);
	}
	if(t->Item->word < x) {
		return find(x, t->right);
	}
	return t->Item;
}

template<class Key, class Value>
void BinaryTree<Key,Value>::insert(const Key & x, TreeNode<Key,Value> * & t) const {
	if(t == NULL) {
		
		t = new TreeNode<Key, Value>(x,NULL,NULL);
	}
	else if(x < t->Item->word) { // Left
		insert(x, t->left); 
	}

	else if(t->Item->word < x) {
		insert(x, t->right);
	}
}

