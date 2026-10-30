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

void swap(int& obj1, int& obj2){
    int tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        if (i >= j)
            return j;
        swap(arr[i], arr[j]);
    }
}

void quickSort(int arr[], int n) {
    if (n <= 1) return;
    int p = partition(arr, 0, n - 1);
    quickSort(arr, p + 1);
    quickSort(arr + p + 1, n - p - 1);
}

void selectionSort(int* arr, int n) {
    if (n==1) return;
        
    int idxM=0;
    for (int i=1;i<n;i++){
        if (arr[i]<arr[idxM]){idxM=i;}
    }
    swap(arr[0], arr[idxM]);
    selectionSort(arr+1,n-1);
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i<n; i++){
        int j = i;
        while ((j>=1) && (arr[j-1] > arr[j])){
            swap(arr[j],arr[j-1]);
            j--;
        }
    }

}
