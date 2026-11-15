/*
 * FILE DÀNH CHO CTV.
 * Tên: [Đặng Thị Ngọc Ánh ]
 * MSSV: [202614668]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"
int PhanHoach(int* arr, int left, int right){
        int pivot=arr[right];
        int i=left-1;
        for(int j=left; j<right; j++){
            if(arr[j]<pivot){
                i++;
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
        int temp=arr[i+1];
        arr[i+1]=arr[right];
        arr[right]=temp;
        return i+1;
    }
void quickSortHelper(int* arr, int left, int right) {
    if (left < right ){
        int pivotIndex=PhanHoach(arr,left,right);
        quickSortHelper(arr, left, pivotIndex - 1);
        quickSortHelper(arr, pivotIndex + 1, right);
    }
}

void quickSort(int* arr, int n) {
    quickSortHelper(arr, 0, n - 1);
    (void)arr;
    (void)n;
}

    

void selectionSort(int* arr, int n) {
    for ( int i=0; i<n-1; i++ ) {
        int minIndex = i;
        for ( int j=i+1; j<n; j++ ) {
            if ( arr[j] < arr[minIndex] ) {
                minIndex = j;
            }
        }
        if ( minIndex != i ) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    (void)arr;
    (void)n;
}

void insertionSort(int* arr, int n) {
    int i, key,j;
    for(i=1; i<n; i++){
        key=arr[i];
        j=i-1;
        while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
    (void)arr;
    (void)n;
}
