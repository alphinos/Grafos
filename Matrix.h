#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Items.h"

#ifdef _MATRIX_C_

typedef struct _matrix_{
    int m;
    int n;

    Item** mat; // Items matrix
} Matrix;

// Basics
Matrix* initMatrix(  );
Matrix* initMatrix( int m, int n );
Matrix* initMatrix( int m, int n, Item** mat );

void destroyMatrix( Matrix* matrix );

Item** get_items_mat( Matrix* matrix );

void set_m_matrix( Matrix* matrix, int m );
void set_n_matrix( Matrix* matrix, int n );
void set_mat_matrix( Matrix* matrix, Item** mat );

void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y );
void insert_item_matrix( Matrix* matrix, Item* item ); // Default: inserts in the first cell that is different of NULL

Item get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

Item* remove_item_matrix( Matrix* matrix, Item* item );
Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );
Item* pop_item_matrix( Matrix* matrix ); // Default: removes the first cell that is different of NULL

// Utilitary
void fill_matrix( Matrix* matrix, Item item );

Matrix* copy_matrix( Matrix* matrix );
void copy_matrix( Matrix* a, Matrix* b ); // Copies Matrix a to Matrix b if mb >= ma and nb >= na

Bool is_simetric( Matrix* matrix );

unsigned int count_non_null_cells( Matrix* matrix );

#else

typedef struct _matrix_ Matrix;

extern Matrix* initMatrix(  );
extern Matrix* initMatrix( int m, int n );
extern Matrix* initMatrix( int m, int n, Item** mat );

extern void destroyMatrix( Matrix* matrix );

extern Item** get_items_mat( Matrix* matrix );

extern void set_m_matrix( Matrix* matrix, int m );
extern void set_n_matrix( Matrix* matrix, int n );
extern void set_mat_matrix( Matrix* matrix, Item** mat );

extern void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y );
extern void insert_item_matrix( Matrix* matrix, Item* item );

extern Item get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

extern Item* remove_item_matrix( Matrix* matrix, Item* item );
extern Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );
extern Item* pop_item_matrix( Matrix* matrix );

#endif

#endif