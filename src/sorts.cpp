/*
 * FILE DÀNH CHO CTV.
 * Tên: Hoàng Vân Khánh
 * MSSV: 202617976
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

int partition(int* arr, int lower, int higher) {
    int pivot = arr[higher];
    int i = lower - 1;
    for (int j = lower; j < higher; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[higher];
    arr[higher] = temp;

    return i + 1;
}

void quickSortHelper(int* arr, int lower, int higher) {
    if (lower < higher) {
        int p = partition(arr, lower, higher);
        quickSortHelper(arr, lower, p - 1);
        quickSortHelper(arr, p + 1, higher);
    }
}

void quickSort(int* arr, int n) {
    quickSortHelper(arr, 0, n - 1);
}


void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    (void)arr;
    (void)n;
        for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIdx];
        arr[minIdx] = temp;
    }
}


void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    (void)arr;
    (void)n;
        for (int i = 1; i < n; i++) {
        if (arr[i] >= arr[i - 1]) continue;
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}