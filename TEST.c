#include <stdio.h>

void shift_right(int arr[], int size) {
    int temp = arr[size - 1];
    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = 7;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Arreglo original: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    shift_right(arr, size);

    printf("\nArreglo desplazado a la derecha: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
