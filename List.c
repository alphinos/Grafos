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

char sizeofList( void ){
    return sizeof( List );
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

ListNode* findFromFirst( List* list, unsigned int pos ){
    if ( list == NULL || pos > list->length )
        return FALSE;
    unsigned int amt = 0;
    ListNode* current = list->first;
    while ( amt != pos && current != NULL ){
        current = current->next;
        amt++;
    }
    if ( amt == pos )
        return current;
    else
        return NULL;
}
ListNode* findFromLast( List* list, unsigned int pos ){
    if ( list == NULL )
        return FALSE;
    unsigned int middle = list->length / 2;
    unsigned int amt = 0;
    ListNode* current = list->last;
    while ( amt != pos && amt != middle ){
        current = current->previous;
        amt++;
    }
    if ( middle + amt == pos )
        return current;
    else
        return NULL;
}

Bool listAppend( List* list, Item* data, unsigned int pos ){
    if ( list == NULL || pos > list->length )
        return FALSE;
    
    ListNode* previous,* current;
    
    if ( list->length / 2 < pos ){
        current = findFromFirst( list, pos );
    } else {
        current = findFromLast( list, pos );
    }

    ListNode* newNode = nodeInit( data );
    if ( newNode == NULL )
        return FALSE;

    if ( current == NULL ){
        if ( list->first == NULL ){
            list->first = newNode;
            list->last = newNode;
        } else if ( list->last == NULL ){
            previous = list->last;
            list->last = newNode;
            previous->next = newNode;
            newNode->previous = previous;
        }
    } else if ( current->previous == NULL ){
        list->first = newNode;
        newNode->next = current;
        current->previous = newNode;
    } else {
        previous = current->previous;
        previous->next = current;

        newNode->next = current;
        newNode->previous = previous;

        current->previous = newNode;
    }
    return TRUE;
}

Item* listPop( List* list, unsigned int pos ){
    if ( list == NULL || list->length == 0 || pos > list->length - 1 )
        return NULL;
    
    ListNode* previous,* current, *next;
    Item* item;
    
    if ( list->length / 2 < pos ){
        current = &findFromFirst( list, pos )->data;
    } else {
        current = &findFromLast( list, pos )->data;
    }

    if ( current == NULL )
        return NULL;
    
    previous = current->previous;
    next = current->next;

    if ( previous == NULL ){
        list->first = NULL;
        list->last = NULL;
        list->length = 0;
        
        item = &current->data;
    } else if ( next == NULL ){
        list->last = previous;
        previous->next = NULL;
        list->length--;

        item = &current->data;
    } else {
        previous->next = next;
        next->previous = previous;

        item = &current->data;
    }

    free( current );

    return item;
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
Bool listInsertFirst( List* list, Item* data ){
    if ( list == NULL )
        return FALSE;
    
    ListNode* newNode = nodeInit( data );
    if ( newNode == NULL )
        return FALSE;
    
    ListNode* current = list->first;

    if ( current == NULL ){
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->next = current;
        current->previous = newNode;
        list->first = newNode;
    }
}
Item* listRemoveFirst( List* list ){
    if ( list == NULL || list->first == NULL )
        return NULL;
    ListNode* current = list->first;
    Item* item = copy_item( &current->data );

    list->first = current->next;
    list->first->previous = NULL;

    free( current );

    if ( list->first->next == NULL )
        list->last = list->first;
    
    return item;
}

Item* listGetFirst( List* list ){
    if ( list == NULL || list->first == NULL )
        return NULL;
    return &list->first->data;
}

// Queue
Bool listInsertLast( List* list, Item* data ){
    if ( list == NULL )
        return FALSE;
    
    ListNode* newNode = nodeInit( data );
    if ( newNode == NULL )
        return FALSE;
    
    ListNode* current = list->last;

    if ( current == NULL ){
        list->first = newNode;
        list->last = newNode;
    } else {
        newNode->previous = current;
        current->next = newNode;
        list->last = newNode;
    }
}

Item* listRemoveLast( List* list ){
    if ( list == NULL || list->last == NULL )
        return NULL;
    ListNode* current = list->last;
    Item* item = copy_item( &current->data );

    list->last = current->previous;
    list->last->next = NULL;

    free( current );

    if ( list->last->next == NULL )
        list->last = list->last;
    
    return item;
}

Item* listGetLast( List* list ){
    if ( list == NULL || list->last == NULL )
        return NULL;
    return &list->last->data;
}

#endif