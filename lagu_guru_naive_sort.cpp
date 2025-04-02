#include <stdio.h>

#define MAX_SIZE 10000  // Maximum size for the array

// Function to find the smallest (Laghu) element from the first three elements
int selectLaghu(int arr[], int n) {
    int min_index = 0;
    for (int i = 1; i < 3 && i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

// Function to find the largest (Guru) element from the first three elements
int selectGuru(int arr[], int n) {
    int max_index = 0;
    for (int i = 1; i < 3 && i < n; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

// Function to perform Laghu-Guru sorting
void Laghu_Guru_Sort(int L[], int n, int Laghu_list[], int *laghu_size, 
                      int Guru_list[], int *guru_size) {
    *laghu_size = 0;
    *guru_size = 0;
    int lastAddedToLaghu = 0;

    while (n >= 3) {
        int min_index = selectLaghu(L, n);
        Laghu_list[(*laghu_size)++] = L[min_index];
        lastAddedToLaghu = 1;

        for (int i = min_index; i < n - 1; i++) {
            L[i] = L[i + 1];
        }
        n--;

        if (n >= 3) {
            int max_index = selectGuru(L, n);
            Guru_list[(*guru_size)++] = L[max_index];
            lastAddedToLaghu = 0;

            for (int i = max_index; i < n - 1; i++) {
                L[i] = L[i + 1];
            }
            n--;
        }
    }

    if (n == 2) {
        if (L[0] < L[1]) {
            Laghu_list[(*laghu_size)++] = L[0];
            Guru_list[(*guru_size)++] = L[1];
        } else {
            Laghu_list[(*laghu_size)++] = L[1];
            Guru_list[(*guru_size)++] = L[0];
        }
    } else if (n == 1) {
        if (lastAddedToLaghu) {
            Guru_list[(*guru_size)++] = L[0];
        } else {
            Laghu_list[(*laghu_size)++] = L[0];
        }
    }
}

// Function to perform Insertion Sort (ascending order)
void insertionSortAscending(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Function to merge two sorted arrays
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int merged[]) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        merged[k++] = arr1[i++];
    }
    while (j < size2) {
        merged[k++] = arr2[j++];
    }
}

// Function to print an array
void printArray(int arr[], int size, const char *name) {
    printf("%s: [", name);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// Main function
int main() {
    int L[MAX_SIZE], n = 0;

    // Open the file for reading
    FILE *file = fopen("file1.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    // Read numbers from the file
    while (fscanf(file, "%d", &L[n]) == 1 && n < MAX_SIZE) {
        n++;
    }
    fclose(file);  // Close the file after reading

    if (n == 0) {
        printf("No numbers found in the file!\n\n");
        return 1;
    }

    int Laghu_list[MAX_SIZE], Guru_list[MAX_SIZE], Merged_list[MAX_SIZE];
    int laghu_size = 0, guru_size = 0;

    printArray(L, n, "Original List\n\n");
    printf("\n\n\n");

    // Perform Laghu-Guru Sort
    Laghu_Guru_Sort(L, n, Laghu_list, &laghu_size, Guru_list, &guru_size);

    // Print original Laghu and Guru lists before sorting
    printArray(Laghu_list, laghu_size, "\n\nOriginal Laghu_list\n\n");
    printArray(Guru_list, guru_size, "\n\nOriginal Guru_list\n\n");

    // Sort Laghu_list in ascending order
    insertionSortAscending(Laghu_list, laghu_size);

    // Sort Guru_list in ascending order
    insertionSortAscending(Guru_list, guru_size);

    // Merge the sorted Laghu and Guru lists
    mergeArrays(Laghu_list, laghu_size, Guru_list, guru_size, Merged_list);

    // Print results
    printArray(Laghu_list, laghu_size, "\n\nSorted Laghu_list (Ascending)\n\n");
    printArray(Guru_list, guru_size, "\n\nSorted Guru_list (Ascending)\n\n");
    printArray(Merged_list, laghu_size + guru_size, "\n\nFinal Merged List (Ascending)\n\n");

    return 0;
}

