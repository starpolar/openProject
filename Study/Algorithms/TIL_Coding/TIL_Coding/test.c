#include <stdio.h>

int main() {

    int arr[5] = { 1, 2, 3, 4, 5 };
    int *parr = arr;

    printf("arr size : %d\n", sizeof(arr));
    printf("pointer size : %d\n", sizeof(parr));

    return 0;
}