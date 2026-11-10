/*
 * FILE DÀNH CHO CTV.
 * Tên: [Đồng Minh Đức]
 * MSSV: [202616420]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"
int partition(int*arr, int low, int high){
    int pivot = arr[high];
    int i = low -1; 
    for (int j = low; j < high; j++) {
        if(arr[j]<pivot){
            i++; 
            int thaythe = arr[i]; 
            arr[i] = arr[j];
            arr[j] = thaythe;
        }
    }
    int temp = arr[i+1]; 
    arr[i+1] = arr[high]; 
    arr[high] = temp; 

    return i+1;
}

void quickSortHelper(int*arr, int low, int high){
    if(low<high){
        int chiso = partition(arr, low , high); 
        quickSortHelper(arr,low, chiso-1); 
        quickSortHelper(arr, chiso+1, high); 
    } 
}

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    if(n>1){
        quickSortHelper(arr,0,n-1); 
    }
    (void)arr;
    (void)n;
}

void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
        for(int i=0;i<n-1;i++){
            int minIndex = i;
            for(int j=i+1;j<n;j++){
                if(arr[j]<arr[minIndex]){
                    minIndex = j;
                }
            }
            if(minIndex != i){
                int thaythe = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = thaythe;
            }
        }
        (void)arr;
        (void)n;
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
}
