#ifndef HASH_TABLE
#include "Hash_Table_by_Baran_Cimen.h"
#endif




// Hashing function is taken from http://www.cse.yorku.ca/~oz/hash.html and modified by me
template<class HashedObj>
unsigned long hash(const HashedObj & key, int tableSize) {
	unsigned long hash = 5381;
    int c;
	for (unsigned int i=0; i < key.word.length(); i++) {
		c = key.word.at(i);
		hash = ((hash << 5) + hash) + c;
	}

    return hash % tableSize;
}

template<class HashedObj>
void HashTable<HashedObj>::makeEmpty() {
	int capacity = list.capacity();
	for(int i=list.size(); i < capacity; i++) {
		list.push_back(HashEntry(HashedObj(""), EMPTY));
	}
	for(unsigned int i=0; i < list.size(); i++) {
		list[i].info = EMPTY;
	}
}

template<class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size = 53) :
	ITEM_NOT_FOUND(notFound), list(nextPrime(size)), currentSize(0) {
		makeEmpty();	
};


template<class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj & x) {
	int currentPos = findPos(x);
	if(isActive(x)) {
		list[currentPos].info = DELETED;
	}
}

template<class HashedObj>
HashedObj * HashTable<HashedObj>::find(const HashedObj & x)  {
	int currentPos = findPos(x);
	if(isActive(currentPos)) {
		
		return &(list.at(currentPos).element);
	}
	return &(ITEM_NOT_FOUND);
}

template<class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj & x) {
	unsigned int currentPos = findPos(x);
	if(!isActive(currentPos)) {
		list[currentPos] = HashEntry(x, ACTIVE);

		currentSize++;
		if(double(currentSize)/ list.size() >= 0.9) { // load factor will be always be lower than 0
			rehash();
		}
	}

}

template<class HashedObj>
void HashTable<HashedObj>::preprocessPrint() {
	std::cout << "After preprocessing, the unique word count is " << currentSize << ". Current load ratio is " << double(currentSize)/list.size() << std::endl;
}

// Private Functions

template<class HashedObj>
void HashTable<HashedObj>::rehash() {
	std::vector<HashEntry> oldList = list;
	list.resize(nextPrime(2* oldList.size()));
	makeEmpty();

	currentSize = 0;
	for(unsigned int i=0; i < oldList.size(); i++) {
		if(oldList[i].info == ACTIVE) {
			insert(oldList[i].element);
		}
	}
	std::cout << "rehashed... \n" << "previous table size: " << oldList.size() << ", new table size: " <<\
				 list.size() << ", current unique word count: " << currentSize << ", current load factor: " <<\
				 double(currentSize)/list.size() << std::endl;
}



template<class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj & x) const {
	int collisionNum = 0;
	 unsigned int currentPos = hash(x, list.size());

	while(list[currentPos].info != EMPTY && list[currentPos].element != x) {
		currentPos += 2 * ++collisionNum -1;

		if(currentPos >= list.size()) {
			currentPos -= list.size();
		}
	}

	return currentPos;
}

template<class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const {
	return list[currentPos].info == ACTIVE;
}



template<class HashedObj>
int HashTable<HashedObj>::nextPrime(int n) {
	if(n % 2 == 0) {
		n++;
	}
	while(!isPrime(n)) {
		n += 2;
	}
	return n;
}

template<class HashedObj>
bool HashTable<HashedObj>::isPrime(int n) {
	if(n == 2 || n == 3)
		return true;
	if(n == 1 || n % 2 == 0)
		return false;
	for(int i=3; i*i <= n; i +=2) {
		if(n % i == 0)
			return false;
	} 
	return true;
}
