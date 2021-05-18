#ifndef LIST_H
#define LIST_H

using namespace std;

class list{ //name of the class and header file should be same
	public:
		struct LinkedListNode
		{
			char* data;
			LinkedListNode* next;
			LinkedListNode* prev;
		};
		struct LinkedList
		{
			//LinkedListNode ln;
			LinkedListNode* first;
			LinkedListNode* last;
		};

		LinkedList* LinkedList_create();
		void push( LinkedList* list, char* data);
		void empty(LinkedList* list );
		void pop(LinkedList* list );
		//LinkedListNode* LinkedList_getFirst( LinkedList* list );
		//LinkedListNode* LinkedList_getLast( LinkedList* list );
};
#endif