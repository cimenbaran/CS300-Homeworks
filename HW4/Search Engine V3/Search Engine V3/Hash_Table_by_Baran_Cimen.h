#include <string>
#include <vector>
#ifndef HASH_TABLE
#define HASH_TABLE


template<class HashedObj>
unsigned long hash(const HashedObj & key, int tableSize);


template<class HashedObj>
class HashTable {
public:
	explicit HashTable(const HashedObj & notFound, int size = 53);
	
	HashedObj * find(const HashedObj & x) ;

	void makeEmpty();
	void insert(const HashedObj & x);
	void remove(const HashedObj & x);
	void preprocessPrint();

	enum EntryStatus { ACTIVE, EMPTY, DELETED };

private:
	struct HashEntry {
		HashedObj element;
		EntryStatus info;
		HashEntry(const HashedObj & el = HashedObj(""), EntryStatus i = EMPTY) :
			element(el), info(i) {}
	};

	std::vector<HashEntry> list;
	unsigned int currentSize;
	HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const;
	int findPos(const HashedObj & x) const;
	void rehash();

	int nextPrime(int n);
	bool isPrime(int n);
};






#include "Hash_Table_by_Baran_Cimen.cpp"
#endif