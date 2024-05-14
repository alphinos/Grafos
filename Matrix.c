#ifndef _MATRIX_C_
#define _MATRIX_C_
#include "Matrix.h"
#include <stdlib.h>

Matrix* initMatrix( int m, int n ){
    if ( m < 1 || n < 1 )
        return NULL;
    Matrix* matrix = ( Matrix* ) malloc( sizeof( Matrix ) );
    if ( matrix == NULL ){
        return NULL;
    }

    matrix->m = m;
    matrix->n = n;
    matrix->mat = (Item**) malloc( m * sizeof( Item* ) );
    if ( matrix->mat == NULL ){
        return NULL;
    }

    int i, j;
    for ( i = 0; i < n; i++ ){
        matrix->mat[ i ] = ( Item* ) malloc( n * sizeof( Item ) );

        if ( matrix->mat[ i ] == NULL ){
            break;
        }
    }

    if ( i < n ){
        for ( j = i - 1; j > -1; j-- ){
            free( matrix->mat[ j ] );
        }

        return matrix;
    }

    return matrix;
}

void destroyMatrix( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return;

    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            if ( matrix->mat[ i ][ j ].type_data != NONE )
                return;
        }
    }

    for ( int i = 0; i < matrix->m; i++ ){
        free( matrix->mat[ i ] );
    }
    free( matrix->mat );
    free( matrix );
}

void emptyMatrix( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return;

    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            emptyItem( &matrix->mat[ i ][ j ] );
        }
    }
}

Item** get_items_mat( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return NULL;
    
    return matrix->mat;
}

// Copia item na posição x, y
void insert_item_matrix( Matrix* matrix, Item* item, unsigned int x, unsigned int y ){
    if ( matrix == NULL || matrix->mat == NULL || x < 0 || y < 0 || x > matrix->m - 1 || y > matrix->n - 1 )
        return;
    if ( matrix->mat[ x ][ y ].type_data == NONE ){
        matrix->mat[ x ][ y ].type_data = item->type_data;
        matrix->mat[ x ][ y ].data = item->data;
    }
}

Item* get_item_matrix( Matrix* matrix, unsigned int x, unsigned int y ){
    if ( matrix == NULL || matrix->mat == NULL || x < 0 || y < 0 || x > matrix->m - 1 || y > matrix->n - 1 )
        return NULL;
    if ( matrix->mat[ x ][ y ].type_data == NONE )
        return NULL;
    
    return &matrix->mat[ x ][ y ];
}

Item* remove_item_matrix( Matrix* matrix, Item* key, int ( *cmp )( Item*, Item* ) ){
    if ( matrix == NULL || matrix->mat == NULL )
        return NULL;
    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            if ( cmp( &matrix->mat[ i ][ j ], key ) == 0 ){
                Item* item = copy_item( &matrix->mat[ i ][ j ] );
                matrix->mat[ i ][ j ].data = NULL;
                matrix->mat[ i ][ j ].type_data = NONE;
                return item;
            }
        }
    }
    return NULL;
}

Item* pop_item_matrix( Matrix* matrix, unsigned int x, unsigned int y ){
    if ( matrix == NULL || matrix->mat == NULL || x < 0 || y < 0 || x > matrix->m - 1 || y > matrix->n - 1 )
        return NULL;
    if ( matrix->mat[ x ][ y ].type_data == NONE )
        return NULL;
    
    Item* item = copy_item( &matrix->mat[ x ][ y ] );
    matrix->mat[ x ][ y ].data = NULL;
    matrix->mat[ x ][ y ].type_data = NONE;
    return item;
}

void display_matrix( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return;
    
    printf( "[\n" );

    for ( int i = 0; i < matrix->m; i++ ){
        printf( "[ %s", to_string( &matrix->mat[ i ][ 0 ] ) );
        for ( int j = 1; j < matrix->n; j++ ){
            printf( ", %s", to_string( &matrix->mat[ i ][ j ] ) );
        }
        printf( " ]\n" );
    }

    printf( "]\n" );
}

void fill_matrix( Matrix* matrix, Item item ){
    if ( matrix == NULL || matrix->mat == NULL )
        return;
    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            matrix->mat[ i ][ j ].data = item.data;
            matrix->mat[ i ][ j ].type_data = item.type_data;
        }
    }
}

Matrix* copy_matrix( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return NULL;
    Matrix* copy_matrix = initMatrix( matrix->m, matrix->n );
    if ( copy_matrix == NULL )
        return NULL;

    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            copy_matrix->mat[ i ][ j ].data = matrix->mat[ i ][ j ].data;
            copy_matrix->mat[ i ][ j ].type_data = matrix->mat[ i ][ j ].type_data;
        }
    }

    return matrix;
}

Bool is_simetric( Matrix* matrix, int ( *cmp )( Item*, Item* ) ){
    if ( matrix == NULL || matrix->mat == NULL || matrix->m != matrix->n )
        return NULL;
    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < i; j++ ){
            if ( cmp( &matrix->mat[ i ][ j ], &matrix->mat[ j ][ i ] ) != 0 )
                return FALSE;
        }
    }
    return TRUE;
}

unsigned int count_non_null_cells( Matrix* matrix ){
    if ( matrix == NULL || matrix->mat == NULL )
        return NULL;
    
    unsigned int non_nulls = 0;

    for ( int i = 0; i < matrix->m; i++ ){
        for ( int j = 0; j < matrix->n; j++ ){
            if ( matrix->mat[ i ][ j ].type_data != NONE )
                non_nulls++;
        }
    }
    return non_nulls;
}

#endif