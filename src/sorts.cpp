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

void swap(int* arr, int idx1, int idx2){
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    (void)arr;
    (void)n;
}

void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    if (n==1) return;
        
    int idxM=0;
    for (int i=1;i<n;i++){
        if (arr[i]<arr[idxM]){idxM=i;}
    }
    swap(arr, 0,idxM);
    selectionSort(arr+1,n-1);
}

void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    (void)arr;
    (void)n;
}
