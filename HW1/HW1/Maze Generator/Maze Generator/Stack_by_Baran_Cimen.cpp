#ifndef STACK_HEADER
#include "Stack_by_Baran_Cimen.h"
#endif

using namespace std;

template<class Object>
Stack<Object>::Stack() {
	top = NULL;
}

template<class Object>
Stack<Object>::~Stack() {
	makeEmpty();
}

template<class Object>
bool Stack<Object>::isEmpty() const{
	return top==NULL;
}

template<class Object>
const Object & Stack<Object>::getTop() const{
	if(isEmpty()) {
		throw "Stack is Empty!";
	}
	return  top->element;
}

template<class Object>
void Stack<Object>::pop() {
	if(isEmpty()) {
		throw "Stack is Empty!";
	}
	ListNode * oldNode = top;
	top = top->next;
	delete oldNode;
}

template<class Object>
void Stack<Object>::push(const Object & obj) {
	top = new ListNode(obj, top);
}

template<class Object>
Object Stack<Object>::topAndPop() {
	Object topElement = getTop();
	pop();
	return topElement;
}

template<class Object>
void Stack<Object>::makeEmpty() {
	while(!isEmpty()) {
		pop();
	}
}

