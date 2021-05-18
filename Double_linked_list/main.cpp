#include "list.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>


using namespace std;
//list:: is used to refer to the list class in list.h otherwise types are not recognized

int main(int argc, char** argv){

	list dlist;
	list::LinkedList*  L= dlist.LinkedList_create();
	char c = 'a';
	char d = 'b';
	char e = 'c';
	char f = 'd';

	char *cptr;
	cptr = &c;
	dlist.LinkedList_append(L, cptr);
	//c = 'b';
	dlist.LinkedList_append(L, &d);
	//c = 'c';
	dlist.LinkedList_append(L, &e);
	//c = 'd';
	dlist.LinkedList_append(L, &f);

	cout<<"First element of the list "<<*dlist.LinkedList_getFirst(L)->data;
	cout<<endl;
	cout<<"Last element of the list "<<*dlist.LinkedList_getLast(L)->data;
	cout<<endl;
	cout<<"Now deleting the list ";
	dlist.LinkedList_delete(L);
	cout<<endl;
	return 0;

}

