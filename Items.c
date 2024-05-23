#ifndef _ITEMS_C_
#define _ITEMS_C_
#include "Items.h"
#include <stdio.h>
#include <stdlib.h>

/* Private */
void empty_data( void* data, TypeItems type_data ){
    switch ( type_data ){
        case NONE:
            return;
        case BOOL:
        case CHAR:
        case SHORT:
        case INT:
        case LONG:
        case FLOAT:
        case DOUBLE:
            free( data );
            break;
        case ITEM:
            Item* item = ( Item* ) data;
            if ( item->type_data == NONE )
                item->data = NULL;
            empty_data( item->data, item->type_data );
            item->type_data = NONE;
            break;
        case GRAPH_ITEM:
            GraphItem* graph_item = ( GraphItem* ) data;
            if ( graph_item->item.type_data == NONE )
                item->data = NULL;
            empty_data( ( void * )&graph_item->item, graph_item->item.type_data );
            item->type_data = NONE;
            break;
    }
}

/* Public */
Item* initItem( TypeItems type, void* data ){

}

void destroyItem( Item* item ){

}

void emptyItem( Item* item ){
    if ( item->type_data == NONE )
        return;
    empty_data( item, ITEM );
}

Item* copy_item( Item* item ){

}

char* to_string( Item* item ){
    
}

void print_item( Item* item ){

}

int item_compare( Item* a, Item* b ){
    
}

#endif