/**
 * The romaja_node is a doubly-linked list used for traversing back and forth
 * along a string or a word.
 */
typedef struct _hangul_node hangul_node;

struct _hangul_node {
    hangul_node* prev;
    hangul_node* next;
};
