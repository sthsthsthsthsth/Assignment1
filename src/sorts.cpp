/*
 * FILE DÀNH CHO CTV.
 * Tên: [ NGO HONG DUONG ]
 * MSSV: [ 202610126 ]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"


    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây

// Ham chia mang
int partitionArray( int* arr, int low, int high ) {
    int pivot = arr[high];
    int i = low - 1;

    for ( int j = low; j < high; j++ ) {
        if (arr[j] < pivot) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Ham Quick Sort de quy
void quickSortHelper( int* arr, int low, int high ) 
{
    if ( low < high ) {
        int p = partitionArray( arr, low, high );

        quickSortHelper ( arr, low, p - 1 );
        quickSortHelper ( arr, p + 1, high );
    }
}

// Ham Quick Sort chinh
void quickSort ( int* arr, int n ) 
{
    quickSortHelper ( arr, 0, n - 1 );
}




void selectionSort( int* arr, int n ) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    for ( int i = 0; i < n - 1; i++ ) 
    {
        int minIndex = i;

        for ( int j = i + 1; j < n; j++ ) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSort( int* arr, int n ) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    for ( int i = 1; i < n; i++ ) 
    {
        int key = arr[i];
        int j = i - 1;

        while ( j >= 0 && arr[j] > key ) 
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
