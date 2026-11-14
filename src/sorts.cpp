/*
 * FILE DÀNH CHO CTV.
 * Tên: Vũ Nam Khánh
 * MSSV: 202613160
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

static int partition(int* arr, int low, int high);
static void quickSortHelper(int* arr, int low, int high);

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    if (arr == nullptr || n <= 1) return;
    quickSortHelper(arr, 0, n - 1);
}
static int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    int t2 = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = t2;
    return i + 1;
}
static void quickSortHelper(int* arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSortHelper(arr, low, p - 1);
        quickSortHelper(arr, p + 1, high);
    }
}


void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    for (int i = 1; i < n; i++) {
        if (arr[i] >= arr[i - 1]) {
            continue;
        }
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; 
            j--;
        }
        arr[j + 1] = key;
    }
}

