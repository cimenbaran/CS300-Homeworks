#ifndef AVLTREE
#include "AVLTree_by_Baran_Cimen.h"
#endif


// PUBLIC

template<class Key, class Value>
AVLTree<Key, Value>::AVLTree(const Value & notFound):
		ITEM_NOT_FOUND(notFound), root(NULL) {};

template<class Key, class Value>
AVLTree<Key, Value>::~AVLTree() {
	makeEmpty();
};


template<class Key, class Value>
Value AVLTree<Key, Value>::find(const Key & key) {
	return find(key,root);
}


template<class Key, class Value>
void AVLTree<Key, Value>::insert(const Key & x) {
	insert(x,root);
};

template<class Key, class Value>
void AVLTree<Key, Value>::makeEmpty() {
	makeEmpty(root);
};


template<class Key, class Value>
bool AVLTree<Key, Value>::isEmpty() const {
	return root == NULL;
};




// PRIVATE

template<class Key, class Value>
int AVLTree<Key, Value>::max( int lhs, int rhs ) const {
	return (lhs > rhs ? lhs : rhs);
}

template<class Key, class Value>
void AVLTree<Key, Value>::makeEmpty(AVLNode<Key,Value> * & t) const {
	if(t != NULL) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t->Item;
		delete t;
	}
	t = NULL;
};



template<class Key, class Value>
int AVLTree<Key, Value>::height(AVLNode<Key,Value> * t) const {
	return t == NULL ? -1 : t->height;
};



template<class Key, class Value>
Value AVLTree<Key,Value>::find(const Key & x, AVLNode<Key,Value> * & t) const {
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
void AVLTree<Key,Value>::insert(const Key & x, AVLNode<Key,Value> * & t) const {
	if(t == NULL) {
		
		t = new AVLNode<Key, Value>(x,NULL,NULL);
	}
	else if(x < t->Item->word) { // Left
		insert(x, t->left); 

		if(height(t->left) - height(t->right) == 2) {
			if(x < t->left->Item->word) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
	}

	else if(t->Item->word < x) {
		insert(x, t->right);

		if(height(t->right) - height(t->left) == 2) {
			if(t->right->Item->word < x) {
				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}

	}
	t->height = max(height(t->left), height(t->right)) + 1;
}


template<class Key, class Value>
void AVLTree<Key,Value>::rotateWithLeftChild( AVLNode<Key,Value> * & k2 ) const {
	AVLNode<Key,Value> * k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    k2 = k1;
};



template<class Key, class Value>
void AVLTree<Key,Value>::rotateWithRightChild( AVLNode<Key,Value> * & k1 ) const {
	AVLNode<Key,Value> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max(height(k1->left), height(k1->right)) + 1;
    k2->height = max(height(k2->right), k1->height) + 1;
    k1 = k2;
};


template<class Key, class Value>
void AVLTree<Key,Value>::doubleWithLeftChild( AVLNode<Key,Value> * & k3 ) const {
	rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
};
    

template<class Key, class Value>
void AVLTree<Key,Value>::doubleWithRightChild( AVLNode<Key,Value> * & k1 ) const {
	rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);

};