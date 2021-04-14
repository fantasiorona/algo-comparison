#include <iostream>

// From: https://www.geeksforgeeks.org/bubble-sort/
#pragma region BubbleSort
template <typename T>
void swap(T* xp, T* yp) {
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
template <typename T>
void bubbleSort(T arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false) break;
    }
}
#pragma endregion

// From: https://www.geeksforgeeks.org/insertion-sort/
#pragma region InsertionSort
/* Function to sort an array using insertion sort*/
template <typename T>
void insertionSort(T arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
#pragma endregion

// From: https://www.geeksforgeeks.org/heap-sort/
#pragma region HeapSort
// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
template <typename T>
void heapify(T arr[], int n, int i) {
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest]) largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest]) largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        std::swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
#pragma endregion

// From: https://www.geeksforgeeks.org/radix-sort/
#pragma region RadixSort
// A utility function to get maximum value in arr[]
template <typename T>
int getMax(T arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.

template <typename T>
void countSort(T arr[], int n, int exp) {
    int* output = (int*)alloca(n * sizeof(int)); // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
template <typename T>
void radixsort(T arr[], int n) {
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
#pragma endregion

// A utility function to print an array
void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
}

int main() {

    // Test Bubblesort
    {
        int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
        int n = sizeof(arr) / sizeof(arr[0]);

        // Function Call
        bubbleSort(arr, n);
        std::cout << "Bubblesort:" << std::endl;
        print(arr, n);
        std::cout << std::endl;
    }

    // Test Insertionsort
    {
        int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
        int n = sizeof(arr) / sizeof(arr[0]);

        // Function Call
        insertionSort(arr, n);
        std::cout << "Insertionsort:" << std::endl;
        print(arr, n);
        std::cout << std::endl;
    }

    // Test Heapsort
    {
        int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
        int n = sizeof(arr) / sizeof(arr[0]);

        // Function Call
        heapSort(arr, n);
        std::cout << "Heapsort:" << std::endl;
        print(arr, n);
        std::cout << std::endl;
    }

    // Test Radixsort
    {
        int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
        int n = sizeof(arr) / sizeof(arr[0]);

        // Function Call
        radixsort(arr, n);
        std::cout << "Radixsort:" << std::endl;
        print(arr, n);
        std::cout << std::endl;
    }

    return 0;
}
