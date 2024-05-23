#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Items.h"

#ifdef _MATRIX_C_

// Adapt the struct in the future to be able to receive undefined dimensions

typedef struct _matrix_{
    int m;
    int n;

    Item** mat; // Items matrix
} Matrix;

// Basics
Matrix* initMatrix( int m, int n );

void destroyMatrix( Matrix* matrix );
void emptyMatrix( Matrix* matrix );

Item** get_items_mat( Matrix* matrix );

void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y );

Item* get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

Item* remove_item_matrix( Matrix* matrix, Item* item, int ( *cmp )( void*, void* ) );
Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

void display_matrix( Matrix* matrix );

// Utilitary
void fill_matrix( Matrix* matrix, Item item );

Matrix* copy_matrix( Matrix* matrix );

Bool is_simetric( Matrix* matrix, int ( *cmp )( Item*, Item* ) );

unsigned int count_non_null_cells( Matrix* matrix );

#else

typedef struct _matrix_ Matrix;

// Basics
extern Matrix* initMatrix( int m, int n );

extern void destroyMatrix( Matrix* matrix );

extern void emptyMatrix( Matrix* matrix );

extern Item** get_items_mat( Matrix* matrix );

extern void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y );

extern Item* get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

extern Item* remove_item_matrix( Matrix* matrix, Item* item, int ( *cmp )( void*, void* ) );
extern Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

extern void display_matrix( Matrix* matrix );

// Utilitary
extern void fill_matrix( Matrix* matrix, Item item );

extern Matrix* copy_matrix( Matrix* matrix );

extern Bool is_simetric( Matrix* matrix, int ( *cmp )( Item*, Item* ) );

extern unsigned int count_non_null_cells( Matrix* matrix );

#endif

#endif