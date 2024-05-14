#ifndef _LIST_C_
#define _LIST_C_
#include "List.h"
#include <stdlib.h>

// Node
ListNode* nodeInit( Item* data ){
    ListNode* lnode = ( ListNode* ) malloc( sizeof( ListNode ) );
    if ( lnode == NULL )
        return NULL;
    lnode->data.data = data->data;
    lnode->data.type_data = data->type_data;
    lnode->previous = NULL;
    lnode->next = NULL;
    return lnode;
}

// Basics
List* listInit( void ){
    List* list = ( List* ) malloc( sizeof( List ) );
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

Bool listDestroy( List* list ){
    if ( list == NULL || list->length != 0 )
        return FALSE;
    free( list );
    return TRUE;
}

Bool emptyList( List* list ){
    if ( list == NULL || list->length == 0 )
        return FALSE;

    ListNode* current = list->first;
    ListNode* next = current->next;

    while ( current != NULL ) {
        if ( current->data.type_data == NONE ){
            free( current );
        } else {
            emptyItem( &current->data );
            destroyItem( &current->data );
            free( current );
        }
        current = next;
    }
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
}

unsigned int listGetLength( List* list ){
    return list->length;
}

Item* listQuery( List* list, Item* key, int ( *cmp )( Item*, Item* ) ){
    if ( list == NULL || list->length == 0 )
        return NULL;

    ListNode* previous,* current;
    current = list->first;

    while ( current != NULL ){
        if ( cmp( &current->data, key ) == 0 ){
            return &current->data;
        }

        current = current->next;
    }
    return NULL;
}

Item* listRemove( List* list, Item* key, int* ( *cmp )( Item*, Item* ) ){
    if ( list == NULL || list->length == 0 )
        return NULL;

    ListNode* previous,* current;
    current = list->first;

    while ( current != NULL ){
        if ( cmp( &current->data, key ) == 0 ){
            previous = current->previous;
            previous->next = current->next;
            return &current->data;
        }

        current = current->next;
    }
    return NULL;
}

ListNode* findFromFirst( List* list, unsigned int pos );
ListNode* findFromLast( List* list, unsigned int pos );

Bool listAppend( List* list, Item* data, unsigned int pos ){
    if ( list == NULL || list->length == 0 || pos > list->length - 1 )
        return NULL;
    
    ListNode* previous,* current;
    
    if ( list->length / 2 < pos ){
        current = &findFromFirst( list, pos )->data;
    } else {
        current = &findFromLast( list, pos )->data;
    }

    previous = current->previous;
    if ( previous == NULL ){
        list->first = 
    }
}

Bool listPop( List* list, unsigned int pos ){

}


Item* listGet( List* list, unsigned int pos ){
    if ( list == NULL || list->length == 0 || pos > list->length - 1 )
        return NULL;
    if ( list->length / 2 < pos )
        return &findFromFirst( list, pos )->data;
    else
        return &findFromLast( list, pos )->data;
}

// Stack
Bool listInsertFirst( List* list, Item* data );
Item* listRemoveFirst( List* list );
Item* listGetFirst( List* list );

// Queue
Bool listInsertLast( List* list, Item* data );
Item* listRemoveLast( List* list );
Item* listGetLast( List* list );

#endif