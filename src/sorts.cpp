/*
 * FILE DÀNH CHO CTV.
 * Tên: [Vũ Trường Giang]
 * MSSV: [202613531]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"
#include <algorithm>
using namespace std;
void quickSort(int* arr, int n) {
    if (n <= 1) {
        return;
    }
    int pivot=arr[n-1];
    int i = -1;
    for (int j = 0; j < n - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
        swap(arr[i + 1], arr[n - 1]); 
        int pi=i+1;
        quickSort(arr, pi);
        quickSort(arr + pi + 1, n - pi - 1);
    }
    
void selectionSort(int* arr, int n) {
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
    
   
}

void insertionSort(int* arr, int n) {
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
