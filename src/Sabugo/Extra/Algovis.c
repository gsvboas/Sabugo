#include "Sabugo.h"
#include "Public/AlgovisTypes.h"

void drawTraversal_bpii(Node_bpii* root, Vec2f rootCenter, float radius, float spacingFactor)
{
    Vec2f rightChildCenter, leftChildCenter;
    float childRadius;
    if (!root)
    {
	Vec2f dim;

	dim.x = radius / 2;
	dim.y = radius / 2;

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

    childRadius = radius;

    rightChildCenter.x = rootCenter.x + 0.2f * spacingFactor;
    rightChildCenter.y = rootCenter.y - 0.2f;
    drawTraversal_bpii(root->right_child, rightChildCenter, childRadius, spacingFactor / 2);

    leftChildCenter.x = rootCenter.x - 0.2f * spacingFactor;
    leftChildCenter.y = rootCenter.y - 0.2f;
    drawTraversal_bpii(root->left_child, leftChildCenter, childRadius, spacingFactor / 2);

    /* draw root */
    drawFillCircle(rootCenter, radius, root->color);

}

