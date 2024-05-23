#ifndef _GRAPH_H_
#define _GRAPH_H_
#include "Items.h"

typedef enum _representation_graph_{
    MATRIX_ADJ, LIST_ADJ
} RepresentationGraph;

#ifdef _GRAPH_C_

typedef struct _graph_{
    RepresentationGraph representation_type;
    void* adjacences;
    Item* vertices_items;
    unsigned int size;
} Graph;

Graph* initGraph( unsigned int size, RepresentationGraph representation_type );
void destroyGraph( Graph* graph );
void emptyGraph( Graph* graph );

Bool add_directed_edge( Graph* graph, unsigned int u, unsigned int v );
Bool add_non_directed_edge( Graph* graph, unsigned int u, unsigned int v );

Item* remove_directed_edge( Graph* graph, unsigned int u, unsigned int v );
Item* remove_non_directed_edge( Graph* graph, unsigned int u, unsigned int v );

// Printing
void display_graph( Graph* graph );
void display_matrix_graph( Graph* graph );
void display_list_graph( Graph* gaph );

#else

typedef struct _graph_ Graph;

extern Graph* initGraph( unsigned int size, RepresentationGraph representation_type );
extern void destroyGraph( Graph* graph );
extern void emptyGraph( Graph* graph );

extern Bool add_directed_edge( Graph* graph, unsigned int u, unsigned int v );
extern Bool add_non_directed_edge( Graph* graph, unsigned int u, unsigned int v );

extern Item* remove_directed_edge( Graph* graph, unsigned int u, unsigned int v );
extern Item* remove_non_directed_edge( Graph* graph, unsigned int u, unsigned int v );

extern void display_graph( Graph* graph );

#endif

#endif