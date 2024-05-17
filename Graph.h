#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef enum _representation_graph_{
    MATRIX_ADJ, LIST_ADJ
} RepresentationGraph;

#ifdef _GRAPH_C_


typedef struct _graph_{
    RepresentationGraph representation_type;
    void* *adjacences;
} Graph;

Graph* initGraph( RepresentationGraph representation_type );
void destroyGraph( Graph* graph );

// Printing
void print_graph( Graph* graph );
void print_matrix_graph( Graph* graph );
void print_list_graph( Graph* gaph );

#else

typedef struct _graph_ Graph;

extern Graph* initGraph( RepresentationGraph representation_type );
extern void print_graph( Graph* graph );

#endif
#endif