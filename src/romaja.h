/**
 * The romaja_node is a doubly-linked list used for traversing back and forth
 * along a string or a word.
 */
typedef struct _romaja_node romaja_node;

struct _romaja_node {
    romaja_node* prev;
    romaja_node* next;
};

void romaja_init(romaja_node* node);
void romaja_push(romaja_node* list);
void romaja_unshift(romaja_node* list);
void romaja_insert(romaja_node* list, romaja_node* insert, unsigned int n);
void romaja_delete_index(romaja_node* list, unsigned int index);
void romaja_free(romaja_node* start);
