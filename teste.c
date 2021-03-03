#include <stdio.h>

typedef float Mat4f[4][4];

int main()
{
    int i, j;
    Mat4f m;

    for (i = 0; i < 4; i++)
	for (j = 0; j < 4; j++)
	    m[i][j] = i + j * 4;

    for (i = 0; i < 4; i++){
	for (j = 0; j < 4; j++)
	    printf("%.3f ", m[i][j]);
	printf("\n");
    }
}

