import argparse
import random
import time

# Argument parsing
parser = argparse.ArgumentParser()
parser.add_argument("algorithm", choices=["bubble", "insert", "heap", "radix", "python", "all"])
parser.add_argument('--struct', action="store_true")
args = parser.parse_args()

# All algorithm implementations from https://www.geeksforgeeks.org/

# -------------------------------------------------------------------------------
# Bubble Sort


def bubbleSort(arr):
    n = len(arr)

    # Traverse through all array elements
    for i in range(n-1):
        # range(n) also work but outer loop will repeat one time more than needed.

        # Last i elements are already in place
        for j in range(0, n-i-1):

            # traverse the array from 0 to n-i-1
            # Swap if the element found is greater
            # than the next element
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]


# -------------------------------------------------------------------------------
# Insertion Sort
def insertionSort(arr):

    # Traverse through 1 to len(arr)
    for i in range(1, len(arr)):

        key = arr[i]

        # Move elements of arr[0..i-1], that are
        # greater than key, to one position ahead
        # of their current position
        j = i-1
        while j >= 0 and key < arr[j]:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key


# -------------------------------------------------------------------------------
# Heap Sort

# To heapify subtree rooted at index i.
# n is size of heap
def heapify(arr, n, i):
    largest = i  # Initialize largest as root
    l = 2 * i + 1     # left = 2*i + 1
    r = 2 * i + 2     # right = 2*i + 2

    # See if left child of root exists and is
    # greater than root
    if l < n and arr[i] < arr[l]:
        largest = l

    # See if right child of root exists and is
    # greater than root
    if r < n and arr[largest] < arr[r]:
        largest = r

    # Change root, if needed
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # swap

        # Heapify the root.
        heapify(arr, n, largest)

# The main function to sort an array of given size


def heapSort(arr):
    n = len(arr)

    # Build a maxheap.
    # Since last parent will be at ((n//2)-1) we can start at that location.
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    # One by one extract elements
    for i in range(n-1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]   # swap
        heapify(arr, i, 0)


# -------------------------------------------------------------------------------
# Radix Sort

# A function to do counting sort of arr[] according to
# the digit represented by exp.
def countingSort(arr, exp1):

    n = len(arr)

    # The output array elements that will have sorted arr
    output = [0] * (n)

    # initialize count array as 0
    count = [0] * (10)

    # Store count of occurrences in count[]
    for i in range(0, n):
        index = (int(arr[i])/exp1)
        count[int((index) % 10)] += 1

    # Change count[i] so that count[i] now contains actual
    #  position of this digit in output array
    for i in range(1, 10):
        count[i] += count[i-1]

    # Build the output array
    i = n-1
    while i >= 0:
        index = (int(arr[i])/exp1)
        output[count[int((index) % 10)] - 1] = arr[i]
        count[int((index) % 10)] -= 1
        i -= 1

    # Copying the output array to arr[],
    # so that arr now contains sorted numbers
    i = 0
    for i in range(0, len(arr)):
        arr[i] = output[i]

# Method to do Radix Sort


def radixSort(arr):

    # Find the maximum number to know number of digits
    max1 = max(arr)

    # Do counting sort for every digit. Note that instead
    # of passing digit number, exp is passed. exp is 10^i
    # where i is current digit number
    exp = 1
    while int(max1)/exp > 0:
        countingSort(arr, exp)
        exp *= 10


class UselessStruct:
    i: int

    f1: float
    f2: float
    f3: int
    f4: int
    f5: int
    f6: float
    f7: float
    f8: int

    def __init__(self, number):
        self.i = number

        self.f1 = 1
        self.f2 = 2
        self.f3 = 3
        self.f4 = 4
        self.f5 = 5
        self.f6 = 6
        self.f7 = 7
        self.f8 = 8

    def __lt__(self, other):
        return self.i < other.i

    def __int__(self):
        return self.i


def readData(use_struct):
    #max = 0;
    arr = []

    with open("randomNumbers.txt") as file:
        for line in file.readlines():
            # if max > 10:
            #    return arr
            if use_struct:
                arr.append(UselessStruct(int(line)))
            else:
                arr.append(int(line))
            #max += 1
    return arr


def reset(arr, start):
    arr = readData(args.struct)
    start = time.time()
    return arr, start


# Driver code to test above
arr = readData(args.struct)

print("Running benchmarks with ", len(arr), " elements per algorithm...")
start = time.time()

if args.algorithm == "bubble":
    bubbleSort(arr)
elif args.algorithm == "heap":
    heapSort(arr)
elif args.algorithm == "insert":
    insertionSort(arr)
elif args.algorithm == "radix":
    radixSort(arr)
elif args.algorithm == "python":
    arr.sort()
elif args.algorithm == "all":
    bubbleSort(arr)
    print("bubbleSort took\t\t", time.time() - start, " seconds")

    arr, start = reset(arr, start)
    insertionSort(arr)
    print("InsertionSort took\t", time.time() - start, " seconds")

    arr, start = reset(arr, start)
    heapSort(arr)
    print("HeapSort took\t\t", time.time() - start, " seconds")

    arr, start = reset(arr, start)
    radixSort(arr)
    print("RadixSort took\t\t", time.time() - start, " seconds")

    arr, start = reset(arr, start)
    arr.sort()
    print("Python TimSort took\t\t", time.time() - start, " seconds")
    exit()
else:
    print("Unknown sort algorithm!")

print("Sorting took", time.time() - start, " seconds")
