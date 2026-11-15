/*
 * FILE DÀNH CHO CTV.
 * Tên: [CTV điền họ và tên vào đây]
 * MSSV: [CTV điền mssv vào đây]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"
// Hàm phụ trợ để phân hoạch và sắp xếp
void quickSortRange(int* arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    int pivotIndex = i + 1;

    quickSortRange(arr, left, pivotIndex - 1);
    quickSortRange(arr, pivotIndex + 1, right);
}
void quickSort(int* arr, int n) {
   if (arr == nullptr || n <= 1) {
        return;
    }
 quickSortRange(arr, 0, n - 1);
}

void selectionSort(int* arr, int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
    
}

void insertionSort(int* arr, int n) {
   if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
    
}
