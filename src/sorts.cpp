/*
 * FILE DÀNH CHO CTV.
 * Tên: Nguyễn Viết Phúc Hiếu
 * MSSV: 202610531
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

namespace {

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void quickSortHelper(int* arr, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = arr[high];
    int i = low;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }

    swap(arr[i], arr[high]);

    quickSortHelper(arr, low, i - 1);
    quickSortHelper(arr, i + 1, high);
}

}  // namespace

void quickSort(int* arr, int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }
    quickSortHelper(arr, 0, n - 1);
}

void selectionSort(int* arr, int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 0; i < n; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

void insertionSort(int* arr, int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}
