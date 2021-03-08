#include "Sabugo.h"
#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* const NAME = "SABUGO WINDOW";

typedef struct Node Node;
struct Node
{
    Node* parent;
    Node* left_child;
    Node* right_child;

    int key;
    int value;
    Color color;
};

Node* ROOT = NULL;


Node* insert(Node* root, int value, Color color)
{
    if (!root)
    {
	Node* nnode = (Node*)malloc(sizeof(Node));
	if (!nnode)
	    return NULL;
	nnode->value = value;
	nnode->color = color;
	nnode->parent = NULL;
	nnode->left_child = NULL;
	nnode->right_child = NULL;
	return nnode;
    }

    if (value > root->value){
	root->right_child = insert(root->right_child, value, color);
	root->right_child->parent = root;
    }
    else if (value < root->value){
	root->left_child = insert(root->left_child, value, color);
	root->left_child->parent = root;
    }
    return root;
}

#if 0
void drawTraversal(Node* root, Vec2f rootCenter, float rootRadius, float factor)
{
    Vec2f rightChildCenter, leftChildCenter;
    float childRadius;
    if (!root)
    {
	Vec2f dim;

	dim.x = rootRadius / 2;
	dim.y = rootRadius / 2;

	rootCenter.x -= dim.x / 2;

	drawFillRectangle(rootCenter, dim, BLACK);
	return;
    }

    if (!root->parent)
	root->color = BLUE;
    /*
    else if (root->parent->value > root->value)
	rootCenter.x -= 0.2f;
    else if (root->parent->value < root->value)
	rootCenter.x += 0.2f;
    else
	root->color = GREEN;
    */

    childRadius = rootRadius;

    rightChildCenter.x = rootCenter.x + 0.2f * factor;
    rightChildCenter.y = rootCenter.y - 0.2f;
    drawTraversal(root->right_child, rightChildCenter, childRadius, factor / 2);

    leftChildCenter.x = rootCenter.x - 0.2f * factor;
    leftChildCenter.y = rootCenter.y - 0.2f;
    drawTraversal(root->left_child, leftChildCenter, childRadius, factor / 2);

    /* draw root */
    drawFillCircle(rootCenter, rootRadius, root->color);

}
#endif


int main()
{
    Vec2f v;
    createWindow(WIDTH, HEIGHT, NAME);

    v.x = +0.0f;
    v.y = -0.7f;

    ROOT = insert(ROOT, 6, RED);
    ROOT = insert(ROOT, 3, GREEN);
    ROOT = insert(ROOT, 9, RED);
    ROOT = insert(ROOT, 2, RED);
    ROOT = insert(ROOT, 4, RED);
    ROOT = insert(ROOT, 1, RED);
    ROOT = insert(ROOT, 5, RED);
    ROOT = insert(ROOT, 7, RED);
    ROOT = insert(ROOT, 8, RED);
    ROOT = insert(ROOT, 10, RED);


    while (windowIsOpen())
    {
	drawTraversal_bpii((Node_bpii*)ROOT, v, 0.1f, 4.0f);
	display();
    }
    return 0;
}

