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

Bool add_directed_edge( Graph* graph, Item* u, Item* v );
Bool add_non_directed_edge( Graph* graph, Item* u, Item* v );

Item* remove_directed_edge( Graph* graph, Item* u, Item* v );
Item* remove_non_directed_edge( Graph* graph, Item* u, Item* v );

// Printing
void display_graph( Graph* graph );
void display_matrix_graph( Graph* graph );
void display_list_graph( Graph* gaph );

#endif