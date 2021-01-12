#ifndef STACK_HEADER
#define STACK_HEADER
#include <iostream>


using namespace std;

template <class Object> 
class Stack {
	public:
		Stack();
		~Stack();

		bool isEmpty() const;
		void makeEmpty();
		void pop();
		void push(const Object & obj);
		Object topAndPop();
		const Object & getTop() const;

	private:
		struct ListNode {
			Object element;
			ListNode *next;

			ListNode(const Object & theElement, ListNode * n= NULL) :
				element(theElement), next(n) {}
		};
		ListNode *top;
};

#include "Stack_by_Baran_Cimen.cpp"
#endif