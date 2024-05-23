#ifndef _GRAPH_C_
#define _GRAPH_C_

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "List.h"

Graph* initGraph( unsigned int size, RepresentationGraph representation_type ){
    if ( size < 1 )
        return NULL;
    Graph* graph = ( Graph* ) malloc( sizeof( Graph ) );
    if ( graph == NULL )
        return NULL;
    
    graph->vertices_items = ( Item* ) malloc( size * sizeof( Item ) );
    if ( graph->vertices_items == NULL ){
        free( graph );
        return NULL;
    }
    for ( int i = 0; i < size + 1; i++ ){
        graph->vertices_items[ i ].type_data = NONE;
    }

    graph->representation_type = representation_type;

    if ( representation_type == MATRIX_ADJ ){
        graph->adjacences = (void*) initMatrix( size, size );
    } else if ( representation_type == LIST_ADJ ){
        int i;
        List* *array_items = ( List** ) malloc( size * sizeof( List* ) );
        for ( i = 0; i < size; i++ ){
            array_items[ i ] = listInit(  );
            if ( array_items[ i ] == NULL ){
                break;
            }
        }
        if ( i < size ){
            for ( int j = i - 1; j > -1; j-- ){
                free( array_items[ j ] );
            }
            free( graph );
            return NULL;
        }

        graph->adjacences = ( void* ) array_items;
    } else {
        return NULL;
    }
}

void destroyGraph( Graph* graph ){
    if ( graph == NULL )
        return;
    
    if ( graph->representation_type == MATRIX_ADJ ){
        destroyMatrix( ( Matrix* ) graph->adjacences );
    } else if ( graph->representation_type == LIST_ADJ ){
        for ( int i = 0; i < graph->size; i++ ){
            List** array_lists = ( List** ) graph->adjacences;
            if ( listGetLength( ( List* ) array_lists[ i ] ) != 0 )
                return;
        }

        for ( int i = 0; i < graph->size; i++ ){
            List** array_lists = ( List** ) graph->adjacences;
            listDestroy( ( List* ) array_lists[ i ] );
        }
    }

    free( graph->vertices_items );
    free( graph );

    return;
}

void emptyGraph( Graph* graph ){
    if ( graph == NULL )
        return;
    
    if ( graph->representation_type == MATRIX_ADJ ){
        emptyMatrix( ( Matrix* ) graph->adjacences );
    } else if ( graph->representation_type == LIST_ADJ ){
        for ( int i = 0; i < graph->size; i++ ){
            List** array_lists = ( List** ) graph->adjacences;
            emptyGraph( ( List* ) array_lists[ i ] );
        }
    }

    free( graph );
    return;
}

Bool add_directed_edge( Graph* graph, unsigned int u, unsigned int v ){
    if ( graph == NULL || graph->adjacences == NULL || u > graph->size || v > graph->size )
        return FALSE;

    if ( graph->representation_type == MATRIX_ADJ ){
        Matrix* matrix = ( Matrix* ) graph->adjacences;

        Item item;
        item.type_data = INT;
        int* integer = ( int* ) malloc( sizeof( int ) );
        *integer = 0;
        item.data = ( void* ) integer;

        insert_item_matrix( matrix, &item, u, v );
        return TRUE;
    } else if ( graph->representation_type == LIST_ADJ ){
        Item item;
        GraphItem* graph_item = ( GraphItem* ) malloc( sizeof( GraphItem ) );

        item.type_data = GRAPH_ITEM;
        item.data = ( void* ) graph_item;

        graph_item->item.type_data = NONE;

        graph_item->go_to = v;

        listInsertLast( &graph->adjacences[ u ], &item );
        return TRUE;
    }
    return FALSE;
}

Bool add_non_directed_edge( Graph* graph, unsigned int u, unsigned int v ){
    if ( graph == NULL || graph->adjacences == NULL || u > graph->size || v > graph->size )
        return FALSE;

    if ( graph->representation_type == MATRIX_ADJ ){
        Matrix* matrix = ( Matrix* ) graph->adjacences;

        Item item;
        item.type_data = INT;
        int* integer = ( int* ) malloc( sizeof( int ) );
        *integer = 0;
        item.data = ( void* ) integer;

        insert_item_matrix( matrix, &item, u, v );
        insert_item_matrix( matrix, &item, v, u );
        return TRUE;
    } else if ( graph->representation_type == LIST_ADJ ){
        Item item;
        GraphItem* graph_item = ( GraphItem* ) malloc( sizeof( GraphItem ) );

        item.type_data = GRAPH_ITEM;
        item.data = ( void* ) graph_item;

        graph_item->item.type_data = NONE;

        graph_item->go_to = v;

        listInsertLast( &graph->adjacences[ u ], &item );

        graph_item->go_to = v;
        listInsertLast( &graph->adjacences[ v ], &item );
        return TRUE;
    }
    return FALSE;
}

Item* remove_directed_edge( Graph* graph, unsigned int u, unsigned int v ){
    if ( graph == NULL || graph->adjacences == NULL || u > graph->size || v > graph->size )
        return FALSE;

    if ( graph->representation_type == MATRIX_ADJ ){
        Matrix* matrix = ( Matrix* ) graph->adjacences;
        Item item;
        item.data = u;
        item.type_data = INT;
        return pop_item_matrix( matrix, u, v );
    } else if ( graph->representation_type == LIST_ADJ ){
        Item item;
        GraphItem* graph_item = ( GraphItem* ) malloc( sizeof( GraphItem ) );

        item.type_data = GRAPH_ITEM;
        item.data = ( void* ) graph_item;

        graph_item->item.type_data = NONE;

        graph_item->go_to = v;

        return listRemove( &graph->adjacences[ u ], &item, item_compare );
    }
    return FALSE;
}
Item* remove_non_directed_edge( Graph* graph, unsigned int u, unsigned int v ){
    if ( graph == NULL || graph->adjacences == NULL || u > graph->size || v > graph->size )
        return FALSE;

    if ( graph->representation_type == MATRIX_ADJ ){
        Matrix* matrix = ( Matrix* ) graph->adjacences;
        Item item;
        item.data = u;
        item.type_data = INT;
        pop_item_matrix( matrix, u, v );
        return pop_item_matrix( matrix, v, u );
    } else if ( graph->representation_type == LIST_ADJ ){
        Item item;
        GraphItem* graph_item = ( GraphItem* ) malloc( sizeof( GraphItem ) );

        item.type_data = GRAPH_ITEM;
        item.data = ( void* ) graph_item;

        graph_item->item.type_data = NONE;

        graph_item->go_to = v;

        listRemove( &graph->adjacences[ u ], &item, item_compare );
        graph_item->go_to = v;
        return listRemove( &graph->adjacences[ v ], &item, item_compare );
    }
    return FALSE;
}

// Printing
void display_graph( Graph* graph );
void display_matrix_graph( Graph* graph );
void display_list_graph( Graph* gaph );

#endif