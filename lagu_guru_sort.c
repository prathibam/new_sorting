#include <stdio.h>

// Function to find the smallest, middle, and largest of three numbers
void find_min_mid_max(int a, int b, int c, int *min, int *mid, int *max) {
    if (a < b && a < c) {
        *min = a;
        if (b < c) {
            *mid = b;
            *max = c;
        } else {
            *mid = c;
            *max = b;
        }
    } else if (b < a && b < c) {
        *min = b;
        if (a < c) {
            *mid = a;
            *max = c;
        } else {
            *mid = c;
            *max = a;
        }
    } else {
        *min = c;
        if (a < b) {
            *mid = a;
            *max = b;
        } else {
            *mid = b;
            *max = a;
        }
    }
}

// Function to remove an element from an array
void remove_element(int arr[], int *size, int index) {
	int i;
    for (i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

// Function to perform the Laghu-Guru sorting process
void laghu_guru_sort(int arr[], int n) {
    int laghu_list[n], guru_list[n]; // To store Laghu and Guru elements
    int laghu_count = 0, guru_count = 0;
    int size = n,i;

    while (size >= 3) {
        // Laghu Step
        int min, mid, max,i;
        find_min_mid_max(arr[0], arr[1], arr[2], &min, &mid, &max);

        laghu_list[laghu_count++] = min; // Add min to Laghu list

        // Remove min from array
        for (i = 0; i < size; i++) {
            if (arr[i] == min) {
                remove_element(arr, &size, i);
                break;
            }
        }

        // Move mid to end of array
        for (i = 0; i < size; i++) {
            if (arr[i] == mid) {
                remove_element(arr, &size, i);
                arr[size] = mid;
                size++;
                break;
            }
        }

        // Guru Step (only if 3 elements remain)
        if (size >= 3) {
            find_min_mid_max(arr[0], arr[1], arr[2], &min, &mid, &max);

            guru_list[guru_count++] = max; // Add max to Guru list

            // Remove max from array
            for (i = 0; i < size; i++) {
                if (arr[i] == max) {
                    remove_element(arr, &size, i);
                    break;
                }
            }

            // Move mid to end of array
            for (i = 0; i < size; i++) {
                if (arr[i] == mid) {
                    remove_element(arr, &size, i);
                    arr[size] = mid;
                    size++;
                    break;
                }
            }
        }
    }

    // Handling last remaining elements
    if (size == 2) {
        // If two elements remain, move smallest to Laghu and largest to Guru
        if (arr[0] < arr[1]) {
            laghu_list[laghu_count++] = arr[0];
            guru_list[guru_count++] = arr[1];
        } else {
            laghu_list[laghu_count++] = arr[1];
            guru_list[guru_count++] = arr[0];
        }
    } else if (size == 1) {
        // If one element remains, move it to Laghu
        laghu_list[laghu_count++] = arr[0];
    }

    // Print Laghu List
    printf("Laghu List: ");
    for (i = 0; i < laghu_count; i++) {
        printf("%d ", laghu_list[i]);
    }
    printf("\n");

    // Print Guru List
    printf("Guru List: ");
    for (i = 0; i < guru_count; i++) {
        printf("%d ", guru_list[i]);
    }
    printf("\n");
}

// Main function to execute the program
int main() {
    int arr[] = {57, 85, 13, 7, 28, 42, 35, 14, 17, 78, 46, 99};
    int n = sizeof(arr) / sizeof(arr[0]);

    laghu_guru_sort(arr, n); // Call sorting function

    return 0;
}

