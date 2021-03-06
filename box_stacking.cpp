#include<stdio.h>
#include<stdlib.h>
#include <algorithm>
using namespace std;

/*  Box Stacking Problem: You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i),
    width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible,
    but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each
    strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side
    functions as its base. It is also allowable to use multiple instances of the same type of box.

    Input: { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} }
    Maximum possible height of stack: 60 */

struct Box {
    /* height, width, depth */
    int h, w, d;  /* for simplicity of solution, always keep w <= d */
};

/*  Following function is needed for library function qsort(). We
    use qsort() to sort boxes in decreasing order of base area.*/
int compare(const void *a, const void *b) {
    if((*(Box *) b).d * (*(Box *) b).w == (*(Box *) a).d * (*(Box *) a).w ) return 0;
    else if((*(Box *) b).d * (*(Box *) b).w > (*(Box *) a).d * (*(Box *) a).w) return 1;
    else return -1;
}

/* Returns the height of the tallest stack that can be formed. */
int maxStackHeight(Box arr[], int n) {
    /*   Create an array of all rotations of given boxes. For example:
    For a box {1, 2, 3}, we consider 3 instances {{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */

    Box rot[3*n];
    int index = 0;

    for(int i = 0; i < n; i++) {
        // Copy the original box
        rot[index] = arr[i];
        index++;

        // First rotation of box
        rot[index].h = arr[i].w;
        rot[index].d = max(arr[i].h, arr[i].d);
        rot[index].w = min(arr[i].h, arr[i].d);
        index++;

        // Second rotation of box
        rot[index].h = arr[i].d;
        rot[index].d = max(arr[i].h, arr[i].w);
        rot[index].w = min(arr[i].h, arr[i].w);
        index++;
    }

    // Now the number of boxes is 3n
    n = 3*n;

    /* Sort the array ‘rot[]’ in decreasing order, using quick sort */
    qsort(rot, n, sizeof(rot[0]), compare);

    // Uncomment following two lines to print all rotations
    // for(int i = 0; i < n; i++)
    //    printf("%d x %d x %d\n", rot[i].h, rot[i].w, rot[i].d);

    /* Initialize msh values for all indexes.
    msh[i] –> Maximum possible Stack Height with box i on top */
    int msh[n];

    for(int i = 0; i < n; i++) msh[i] = rot[i].h;

    /* Compute optimized msh values in bottom up manner */
    for(int i = 1; i < n; i++)
        for(int j = 0; j < i; j++)
            if(rot[i].w < rot[j].w && rot[i].d < rot[j].d && msh[i] < msh[j] + rot[i].h)
                msh[i] = msh[j] + rot[i].h;

    /* Pick maximum of all msh values */
    int max = -1;

    for(int i = 0; i < n; i++)
        if(max < msh[i]) max = msh[i];

    return max;
}

int main() {
    Box arr[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("The maximum possible height of stack is %d\n", maxStackHeight(arr, n));
    return 0;
}
