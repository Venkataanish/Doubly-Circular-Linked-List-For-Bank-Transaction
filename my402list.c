#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my402list.h"

extern int  My402ListLength(My402List*lst)
{
	return lst->num_members;
}

extern int  My402ListEmpty(My402List*lst)
{
	if(lst->anchor.next == &(lst->anchor))
		return TRUE;
	else 
		return FALSE;
	}

extern int My402ListAppend(My402List* lst, void* obj){
  My402ListElem *last = NULL;

  if(My402ListEmpty(lst))
  {
    
  My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  n->obj = obj;

  n->prev = &(lst->anchor);
  n->next = &(lst->anchor);

  lst->anchor.prev = n;
  lst->anchor.next = n;

  lst->num_members++;

  return TRUE;
    
  } 
  
  else 
  
  {
    last = My402ListLast(lst);
    My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  
  n->obj = obj;

  n->prev = last;
  n->next = &(lst->anchor);

  lst->anchor.prev = n;
  last->next = n;

  lst->num_members++;

  return TRUE;
   
  }
}

extern int My402ListPrepend(My402List* lst, void* obj)
{
  My402ListElem *first = NULL;

  if(My402ListEmpty(lst))
  {
  My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  n->obj = obj;
  
  n->prev = &(lst->anchor);
  n->next = &(lst->anchor);

  lst->anchor.prev = n;
  lst->anchor.next = n;

  lst->num_members++;

  return TRUE;
    
  } 
  
  else 
  
  {
  
  first = My402ListFirst(lst);

  My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  n->obj = obj;

  n->prev = &(lst->anchor); /*CHANGED HERE */
  n->next = first;

  lst->anchor.next = n;
  first->prev = n;

  lst->num_members++;

  return TRUE;

    
  }
}

extern void My402ListUnlink(My402List*lst, My402ListElem*elem)
{
	if(My402ListEmpty(lst) == TRUE)
	{

	}
	else
	{
	elem->prev->next=elem->next;
    elem->next->prev=elem->prev;
    lst->num_members--;
    }
}

extern void My402ListUnlinkAll(My402List*lst)
{
	My402ListElem *elem=NULL;

	while(elem!=NULL)
	{
    
    elem->prev->next=elem->next;
    elem->next->prev=elem->prev;
    free(elem);
    elem=My402ListNext(lst,elem);
    lst->num_members--;
	}
}

extern int My402ListInsertAfter(My402List *lst, void *obj, My402ListElem *element)
{
  if(element == NULL)
  {
    return My402ListAppend(lst, obj);
  }
  else
  {
  My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  n->obj = obj;

  n->next = element->next;
  n->prev = element;

  element->next->prev=n;
  element->next = n;
  
  
  lst->num_members++;

  return TRUE;
}
}

extern int My402ListInsertBefore(My402List *lst, void *obj, My402ListElem *element){
  if(element == NULL)
  {
    return My402ListPrepend(lst, obj);
  }

  else
  {

  My402ListElem *n = (My402ListElem*)malloc(sizeof(My402ListElem));
  n->obj = obj;

  n->prev = element->prev;
  n->next = element;

  element->prev->next = n;
  element->prev = n;

  lst->num_members++;

  return TRUE;
} 
}

extern My402ListElem *My402ListFirst(My402List*lst)
{
	if(My402ListEmpty(lst)==TRUE)
		return NULL;
	else
		return lst->anchor.next;
}

extern My402ListElem *My402ListLast(My402List*lst)
{
	if(My402ListEmpty(lst)==TRUE)
		return NULL;
	else
		return lst->anchor.prev;
}

extern My402ListElem *My402ListNext(My402List*lst, My402ListElem*elem)
{
	if(My402ListLast(lst)==elem)
		return NULL;
	else
		return elem->next;
}

extern My402ListElem *My402ListPrev(My402List*lst, My402ListElem*elem)
{
	if(My402ListFirst(lst) == elem)
		return NULL;
	else
		return elem->prev;
}

extern My402ListElem *My402ListFind(My402List*lst, void*obj)
{
    My402ListElem *element=NULL , *tofind=NULL;
	element = My402ListFirst(lst);
	while(element!=NULL)
	{
		if(element->obj == obj)
		{
			tofind=element;
		}
		element=My402ListNext(lst,element);
	}
	return tofind;
}

extern int My402ListInit(My402List*lst)
{
  lst->num_members=0;
  lst->anchor.next=lst->anchor.prev=&(lst->anchor);
  return TRUE;
}



