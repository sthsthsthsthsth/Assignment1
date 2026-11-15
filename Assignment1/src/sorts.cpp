/*
 * FILE DÀNH CHO CTV.
 * Tên: Cao Tuấn Kiệt
 * MSSV: 202619388
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

static void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    if (!arr || n <= 1) {
        return;
    }
    int stack[64];
    int top = -1;

    stack[++top] = 0;
    stack[++top] = n - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        int leftSize = (pi - 1) - low;
        int rightSize = high - (pi + 1);
        if (leftSize > rightSize) {
            if (low < pi - 1) {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
            if (pi + 1 < high) {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        } else {
            if (pi + 1 < high) {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
            if (low < pi - 1) {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
        }
    }
    (void)arr;
    (void)n;
}

void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    if (!arr || n <= 1) return;
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
    (void)arr;
    (void)n;
}

void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    if (!arr || n <= 1) return;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    (void)arr;
    (void)n;
}
