/*
 * FILE DÀNH CHO CTV.
 * Tên: [Vũ Thị Tuyết Như]
 * MSSV: [202514308]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

void quickSortHelp(int* arr, int low, int high)
{
    if (low<high)
    {
        int pivot= arr[high];
        int i=low-1;
        for(int j=low;j<high;j++)
        {
            if (arr[j]<=pivot){
                i++;
                int tmp = arr[i];
                arr[i]=arr[j];
                arr[j]=tmp;

            }
        }
        int tmp =arr[i+1];
        arr[i+1]= arr[high];
        arr[high]=tmp;

        int pi =i+1;

        quickSortHelp(arr, low, pi-1);
        quickSortHelp(arr, pi+1, high);
        
    }
}

void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    (void)arr;
    (void)n;
    if (arr==nullptr|| n<=1)
        return;
    quickSortHelp(arr, 0 , n-1);
    

}

void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    (void)arr;
    (void)n;
    if (arr== nullptr|| n<=1)
        return;
    for(int i=0;i<n;i++)
    {
        int min_idx=i;
        for(int j=i+1;j<n;j++)
        {
            if (arr[j]<arr[min_idx]){
                min_idx=j;

            }
        }

        if (min_idx!=i)
        {
            int tmp=arr[i];
            arr[i]=arr[min_idx];
            arr[min_idx]=tmp;
        }
    }
}

void insertionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    (void)arr;
    (void)n;
    if(arr==nullptr||n<=1)
    return;

    for(int i=1;i<n;i++)
    {
        int key=arr[i];
        int j=i-1;
        while(j>=0&& arr[j]>key)
        {
            arr[j+1]= arr[j];
            j=j-1;
        }
        arr[j+1]=key;

    }
}
