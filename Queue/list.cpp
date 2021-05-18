#include <iostream>
#include "list.h"
#include <cstdlib>
#include <stdio.h>

using namespace std;

//list:: is used to denote both where the function came from and the type of the function

list::LinkedList* list::LinkedList_create()
{
	//LinkedList *L = new LinkedList();
	LinkedList *L = (LinkedList*)malloc(sizeof(char)); 
	L->first = NULL;
	L->last = NULL;
	return L;
}
void list::push( LinkedList* list, char* data)
{
	//LinkedListNode* temp = list->first;
	if(list->first == NULL)
	{
		cout<<*data<<" "; //print the first node data youre about to append
		LinkedListNode* temp = new LinkedListNode();
		temp->data=data;
		temp->prev=NULL;
		temp->next=NULL;
		list->first = temp; //Both the first and the last nodes of the linked list are temp
		list->last = temp;
	}
	else
	{	
		LinkedListNode* temp = list->first;
		cout << *temp->data <<" "; //print the first node data
		while(temp->next!=NULL) //This condition misses the first and last elements
		{
			temp = temp->next;
			cout << *temp->data <<" ";
		}
		cout<<*data<<" "; //print the last node data youre about to append
		LinkedListNode* node = new LinkedListNode();
		node->data = data;
		node->next = NULL;
		node->prev = temp;

		temp->next = node;
		list->last = node;
	}
	cout <<endl;
}
void list::pop( LinkedList* list) //removes the topmost element in the queue
{
	//LinkedListNode* temp = list->first;
	if(list->first == NULL)
	{
		cout<<"Cannot pop out of an empty Queue";
	}
	else
	{	
		LinkedListNode* temp = list->first;
		cout<<"Popping the element :";
		cout << *temp->data <<" "; //print the first node data
		if(temp->next==NULL) //Only one element was there in the queue
		{
			list->first = NULL;
			list->last = NULL;
			delete temp;
		}
		else
		{
			LinkedListNode* ntemp = temp->next;
			ntemp->prev = NULL;
			delete temp;
			list->first = ntemp;
			cout<<"First element changed to "<<*ntemp->data;
		}
	}
	cout <<endl;
}
/*
list::LinkedListNode* list::LinkedList_getFirst( LinkedList* list )
{
	return list->first;
}
list::LinkedListNode* list::LinkedList_getLast( LinkedList* list )
{
	return list->last;
}
*/
void list::empty(LinkedList* list )
{
	while(list->first!=NULL) //This condition misses the first and last elements
	{
		list::pop(list);
	}
}
