/*
 * FILE DÀNH CHO CTV.
 * Tên: Bùi Mạnh Hoạt
 * MSSV: 202611761
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    if (n<=1) return;
    int temp=0;
    int be=0;
    int pivot = arr[n-1];

    for (int i=0;i<n-1;i++)
    {

    if (arr[i]<=pivot)
    {
      temp=arr[be];
      arr[be]=arr[i];
      arr[i]=temp;
      be++;
    }
    }
    arr[n-1]=arr[be];
    arr[be]=pivot;
    quickSort(arr,be);
    quickSort(arr + be + 1 , n-be-1);

}


void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    if (n<=1) return;

    int temp=0;
    for (int i=0;i<n;i++)
    {
        int min=i;
        for (int j=i+1;j<n;j++)
        {
            if(arr[j]<=arr[min]) min=j;
        }
        temp=arr[min];
        arr[min]=arr[i];
        arr[i]=temp;
    }
}

void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    if (n<=1) return;

    int key=0;
    for (int i=1;i<n;i++)
    {
        key=arr[i];
        int j=i-1;
        while (j>=0)
        {
            if (arr[j]<=key)break;
            else{
                arr[j+1]=arr[j];
                j--;
            }
        }
        arr[j+1]=key;
    }
}
