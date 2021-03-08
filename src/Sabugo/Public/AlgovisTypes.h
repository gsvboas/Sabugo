#ifndef ALGOVIS_TYPES_H_
#define ALGOVIS_TYPES_H_

typedef struct Node_bpii Node_bpii;
struct Node_bpii
{
    Node_bpii* parent;
    Node_bpii* right_child;
    Node_bpii* left_child;

    int key;
    int value;
    Color color;
};


#endif

