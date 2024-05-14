#ifndef _LIST_H_
#define _LIST_H_
#include "Items.h"

#ifdef _LIST_C_

typedef struct _list_node_{
    Item data;
    struct _list_node_ *previous;
    struct _list_node_ *next;
} ListNode;

typedef struct _list_{
    ListNode* first;
    ListNode* last;

    unsigned int length;
} List;

// Node
ListNode* nodeInit( Item* data );

// Basics
List* listInit( void );
Bool listDestroy( List* list );
Bool emptyList( List* list );
unsigned int listGetLength( List* list );

Item* listQuery( List* list, Item* key, int ( *cmp )( Item*, Item* ) );
Item* listRemove( List* list, Item* key, int* ( *cmp )( Item*, Item* ) );

Bool listAppend( List* list, Item* data, unsigned int pos );
Bool listPop( List* list, unsigned int pos );
Item* listGet( List* list, unsigned int pos );

// Stack
Bool listInsertFirst( List* list, Item* data );
Item* listRemoveFirst( List* list );
Item* listGetFirst( List* list );

// Queue
Bool listInsertLast( List* list, Item* data );
Item* listRemoveLast( List* list );
Item* listGetLast( List* list );


#else

typedef struct _list_ List;

extern List* listInit( void );
extern Bool listDestroy( List* list );
extern Bool emptyList( List* list );
extern unsigned int listGetLength( List* list );

extern Item* listQuery( List* list, Item* key, int ( *cmp )( Item*, Item* ) );
extern Item* listRemove( List* list, Item* key, int* ( *cmp )( Item*, Item* ) );

extern Bool listAppend( List* list, Item* data, unsigned int pos );
extern Bool listPop( List* list, unsigned int pos );
extern Item* listGet( List* list, unsigned int pos );

extern Bool listInsertFirst( List* list, Item* data );
extern Item* listRemoveFirst( List* list );
extern Item* listGetFirst( List* list );

extern Bool listInsertLast( List* list, Item* data );
extern Item* listRemoveLast( List* list );
extern Item* listGetLast( List* list );

#endif

#endif