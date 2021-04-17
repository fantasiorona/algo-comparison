#include <iostream>
#include <string>
#include <cstdlib>

#include "Timer.h"

// From: https://www.geeksforgeeks.org/bubble-sort/
#pragma region BubbleSort
template <typename T>
void bubbleSort(T arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // IF no two elements were swapped by inner loop, then break
        if (swapped == false) break;
    }
}

template <typename T>
void bubbleSortPointers(T* arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (*arr[j] > *arr[j + 1]) {
                std::swap(*arr[j], *arr[j + 1]);
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
    int i, j;
    T key;
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

template <typename T>
void insertionSortPointers(T* arr[], int n) {
    int i, j;
    T key;
    for (i = 1; i < n; i++) {
        key = *arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && *arr[j] > key) {
            *arr[j + 1] = *arr[j];
            j = j - 1;
        }
        *arr[j + 1] = key;
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
template <typename T>
void heapSort(T arr[], int n) {
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

template <typename T>
void heapifyPointers(T* arr[], int n, int i) {
    int largest = i;   // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && *arr[l] > *arr[largest]) largest = l;

    // If right child is larger than largest so far
    if (r < n && *arr[r] > *arr[largest]) largest = r;

    // If largest is not root
    if (largest != i) {
        std::swap(*arr[i], *arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSortPointers(T* arr[], int n) {
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
T getMax(T arr[], int n) {
    T mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.

template <typename T>
void countSort(T arr[], int n, int exp) {
    T* output = (T*)alloca(n * sizeof(T)); // output array
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
    T m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countSort(arr, n, exp);
    }
}

template <typename T>
T* getMaxPointer(T* arr[], int n) {
    T* mx = arr[0];
    for (int i = 1; i < n; i++)
        if (*arr[i] > *mx) mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.

template <typename T>
void countSortPointers(T* arr[], int n, int exp) {
    T** output = new T*[n]; // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(*arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(*arr[i] / exp) % 10] - 1] = arr[i];
        count[(*arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
template <typename T>
void radixsortPointers(T* arr[], int n) {
    // Find the maximum number to know number of digits
    T* m = getMaxPointer(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; *m / exp > 0; exp *= 10) {
        countSortPointers(arr, n, exp);
    }
}
#pragma endregion

// A utility function to print an array
template <typename T>
void print(T arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " | ";
}

template <typename T>
void printPointers(T* arr[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << *arr[i] << " | ";
}

struct A {
    int i;

    float f1;
    double f2;
    int f3;
    long f4;
    long f5;
    double f6;
    float f7;
    short f8;
    A() : i(1), f1(2.0f){};
    A(int i) : i(i) {};
    operator int() const {
        return i;
    }
};

const int SEED = 81;

template <typename T>
T* generateData(int num) {
    srand(SEED);
    T* array = new T[num];
    for (int i = 0; i < num; i++) {
        array[i] = T(rand() % 100000);
    }
    return array;
}

template <typename T>
T** generateDataSeparateAllocations(int num) {
    srand(SEED);
    T** array = new T*[num];
    for (int i = 0; i < num; i++) {
        array[i] = new T(rand() % 100000);
    }
    return array;
}

inline std::ostream& operator<<(std::ostream& os, const A& obj) {
    os /*<< "int: " */
        << obj.i /*<< " string: " << obj.s*/;
    return os;
}
inline bool operator<(const A& lhs, const A& rhs) {
    return lhs.i < rhs.i;
}
inline bool operator>(const A& lhs, const A& rhs) {
    return rhs < lhs;
}
inline bool operator<=(const A& lhs, const A& rhs) {
    return !(lhs > rhs);
}
inline bool operator>=(const A& lhs, const A& rhs) {
    return !(lhs < rhs);
}
inline bool operator==(const A& lhs, const A& rhs) {
    return (lhs.i == rhs.i);
}
inline bool operator!=(const A& lhs, const A& rhs) {
    return !(lhs == rhs);
}

int main() {
    int n = 70000;
    std::cout << "Running benchmarks with " << n << " elements per algorithm." << std::endl;

    // Test Bubblesort
    {
        int* arr = generateData<int>(n);
        Timer timer("Bubblesort with int (data-driven)");
        bubbleSort(arr, n);
    }
    {
        int** arr = generateDataSeparateAllocations<int>(n);
        Timer timer("Bubblesort with int (separate allocations)");
        bubbleSortPointers(arr, n);
    }
    {
        A *arr = generateData<A>(n);
        Timer timer("Bubblesort with struct (data-driven)");
        bubbleSort(arr, n);
    }
    {
        A** arr = generateDataSeparateAllocations<A>(n);
        Timer timer("Bubblesort with struct (separate allocations)");
        bubbleSortPointers(arr, n);
    }

    // Test Insertionsort
    {
        int* arr = generateData<int>(n);
        Timer timer("Insertion sort with int (data-driven)");
        insertionSort(arr, n);
    }
    {
        int** arr = generateDataSeparateAllocations<int>(n);
        Timer timer("Insertion sort with int (separate allocations)");
        insertionSortPointers(arr, n);
    }
    {
        A* arr = generateData<A>(n);
        Timer timer("Insertion sort with struct (data-driven)");
        insertionSort(arr, n);
    }
    {
        A** arr = generateDataSeparateAllocations<A>(n);
        Timer timer("Insertion sort with struct (separate allocations)");
        insertionSortPointers(arr, n);
    }

    // Test Heapsort
    {
        int* arr = generateData<int>(n);
        Timer timer("Heap sort with int (data-driven)");
        heapSort(arr, n);
    }
    {
        int** arr = generateDataSeparateAllocations<int>(n);
        Timer timer("Heap sort with int (separate allocations)");
        heapSortPointers(arr, n);
    }
    {
        A* arr = generateData<A>(n);
        Timer timer("Heap sort with struct (data-driven)");
        heapSort(arr, n);
    }
    {
        A** arr = generateDataSeparateAllocations<A>(n);
        Timer timer("Heap sort with struct (separate allocations)");
        heapSortPointers(arr, n);
    }

    // Test Radixsort
    {
        int* arr = generateData<int>(n);
        Timer timer("Radix sort with int (data-driven)");
        radixsort(arr, n);
    }
    {
        int** arr = generateDataSeparateAllocations<int>(n);
        Timer timer("Radix sort with int (separate allocations)");
        radixsortPointers(arr, n);
    }
    {
        A* arr = generateData<A>(n);
        Timer timer("Radix sort with struct (data-driven)");
        radixsort(arr, n);
    }
    {
        A** arr = generateDataSeparateAllocations<A>(n);
        Timer timer("Radix sort with struct (separate allocations)");
        radixsortPointers(arr, n);
    }

    return 0;
}
