#ifndef _ITEMS_H_
#define _ITEMS_H_

typedef enum _types_items_{
    // Administration
    NONE,
    // Basics
    BOOL, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE,

    // Structures
    ITEM, WORD, MATRIX, LIST, GRAPH, GRAPH_ITEM
} TypeItems;

typedef enum _bool_{
    FALSE, TRUE
} Bool;

typedef struct _item_{
    TypeItems type_data;
    void* data;
} Item;

typedef struct _word_{
    Item key;
    Item value;
} Word;


typedef struct _graph_item_{
    unsigned int go_to;

    int weight_arrival; // Peso de chegada

    Item item;
} GraphItem;

#ifdef _ITEMS_C_

Item* initItem( TypeItems type, void* data );
void destroyItem( Item* item );
void emptyItem( Item* item );

Item* copy_item( Item* item );

char* to_string( Item* item );
void print_item( Item* item );

int item_compare( Item* a, Item* b );

#else

extern Item* initItem( TypeItems type, void* *data );
extern void destroyItem( Item* item );
extern void emptyItem( Item* item );

extern Item* copy_item( Item* item );

extern char* to_string( Item* item );
extern void print_item( Item* item );

extern int item_compare( Item* a, Item* b );

#endif

#endif