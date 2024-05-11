#ifndef _ITEMS_H_
#define _ITEMS_H_

typedef enum _types_items_{
    // Basics
    BOOL, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE,

    // Structures
    GRAPH_ITEM
} TypeItems;

typedef enum _bool_{
    FALSE, TRUE
} Bool;

typedef struct _item_{
    TypeItems type;
    void* *data;
} Item;

Item* initItem( TypeItems type, void* *data );
void destroyItem( Item* item );

Item* copy_item( Item* item );
void copy_item( Item* a, Item* b ); // Copies Item a to Item b

typedef struct _graph_item_{
    unsigned int go_to;

    int weight;
    void* *data;
} GraphItem;

#endif