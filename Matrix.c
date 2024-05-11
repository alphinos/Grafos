#ifndef _MATRIX_C_
#define _MATRIX_C_
#include "Matrix.h"

Matrix* initMatrix(  );
Matrix* initMatrix( int m, int n );
Matrix* initMatrix( int m, int n, Item** mat );

void destroyMatrix( Matrix* matrix );

Item** get_items_mat( Matrix* matrix );

void set_m_matrix( Matrix* matrix, int m );
void set_n_matrix( Matrix* matrix, int n );
void set_mat_matrix( Matrix* matrix, Item** mat );

void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y );
void insert_item_matrix( Matrix* matrix, Item* item );

Item get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );

Item* remove_item_matrix( Matrix* matrix, Item* item );
Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y );
Item* pop_item_matrix( Matrix* matrix );

#endif