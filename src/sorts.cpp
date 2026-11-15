/*
 * FILE DÀNH CHO CTV.
 * Tên: [Nguyễn Thành Vinh]
 * MSSV: [202611629]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

// Hàm phụ trợ: hoán đổi 2 phần tử (tự cài đặt)
static inline void swapInt(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

// Hàm phụ trợ: trung vị của 3 giá trị (chọn pivot tốt hơn)
static int medianOfThree(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
}

// Quick Sort: pivot median-of-three, phân hoạch 3 phần (<, ==, >),
// đệ quy nửa nhỏ và lặp nửa lớn để độ sâu đệ quy tối đa O(log n).
static void quickSortHelper(int* arr, int low, int high) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        int pivot = medianOfThree(arr[low], arr[mid], arr[high]);

        // [low..lt-1] < pivot, [lt..gt] == pivot, [gt+1..high] > pivot
        int lt = low, i = low, gt = high;
        while (i <= gt) {
            if (arr[i] < pivot) {
                swapInt(arr[lt], arr[i]);
                lt++;
                i++;
            } else if (arr[i] > pivot) {
                swapInt(arr[i], arr[gt]);
                gt--;
            } else {
                i++;
            }
        }

        if (lt - low < high - gt) {
            quickSortHelper(arr, low, lt - 1);
            low = gt + 1;
        } else {
            quickSortHelper(arr, gt + 1, high);
            high = lt - 1;
        }
    }
}
void quickSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Quick Sort tại đây
    if (n < 2) return;
    quickSortHelper(arr, 0, n - 1);
    (void)arr;
    (void)n;
}

void selectionSort(int* arr, int n) {
    // CTV TODO: Cài đặt thuật toán Selection Sort tại đây
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapInt(arr[i], arr[minIdx]);
        }
    }
    (void)arr;
    (void)n;
}

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        // Đã đứng đúng vị trí thì bỏ qua
        if (arr[i] >= arr[i - 1]) {
            continue;
        }
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    // CTV TODO: Cài đặt thuật toán Insertion Sort tại đây
    (void)arr;
    (void)n;
}
