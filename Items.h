#ifndef _ITEMS_H_
#define _ITEMS_H_

typedef enum _types_items_{
    // Basics
    BOOL, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE,

    // Structures
    GRAPH_ITEM
} TypeItems;

typedef struct _item_{
    TypeItems type;
    void* *data;
} Item;

Item* initItem( TypeItems type, void* *data );


typedef struct _graph_item_{
    int weight;
    void* *data;
} GraphItem;

#endif