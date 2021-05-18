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
	dlist.push(L, cptr);
	//c = 'b';
	dlist.push(L, &d);
	//c = 'c';
	dlist.push(L, &e);
	//c = 'd';
	dlist.push(L, &f);

	cout<<"First element of the list ";
	dlist.pop(L);
	cout<<endl;
	//cout<<"Last element of the list "<<*dlist.LinkedList_getLast(L)->data;
	//cout<<endl;
	cout<<"Now emptying the list ";
	cout<<endl;
	dlist.empty(L);
	cout<<endl;
	return 0;

}

