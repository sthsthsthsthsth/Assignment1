/*
 * FILE DÀNH CHO CTV.
 * Tên: [Đinh Công Dũng]
 * MSSV: [202613520]
 *
 * YÊU CẦU:
 * - Các bạn chỉ được phép viết code bên trong các hàm dưới đây 
 *   (có thể viết thêm các hàm để phụ trợ).
 * - KHÔNG được sử dụng các hàm hoặc các thư viện xắp sếp có sẵn của C/C++.
 * - KHÔNG thay đổi tên hàm hay tham số đầu vào.
 */

#include "../include/sorts.h"

void quickSortHelper(int* arr, int a, int b) {//chọn 3 tham số: con trỏ, vị trí đầu và cuối
    if (a < b) {//nếu vị trí đầu bằng cuối thì không cần chạy
        int t = arr[b];//t là giá trị của số cuối - giá trị chốt VD 1 4 5 6 2 thì t=5 và arr t =2 
        int x = (a - 1);//tạo ranh giới với x ở vị trí trước a
        for (int y = a; y <= b - 1; y++) {//dùng biến j duyệt các phần tử từ vị trí a đến b-1
            if (arr[y] < t) {//nếu giá trị tại y nhỏ hơn giá trj chốt
                x++;//dịch ranh giới về bên phải
                int z = arr[x]; // đảo vị trí của số nhỏ hơn sang trái
                arr[x] = arr[y];
                arr[y] = z;//nếu giá trị y lớn hơn/bằng chốt thì bỏ qua
            }
        }
        int z = arr[x + 1];//sau khi chuyển các số nhỏ hơn chốt sang trái thì chuyển vị trí của b về giữa
        arr[x + 1] = arr[b];//x+1 là vị trí giữa của 2 khoảng lớn và bé
        arr[b] = z;
        
        int n = x + 1; //lưu vị trí của chốt
        quickSortHelper(arr, a, n - 1); // cho hàm chạy để sắp xếp nửa bên trái
        quickSortHelper(arr, n + 1, b); // cho hàm chạy để sắp xếp nửa bên phải
    }
}
void quickSort(int* arr, int m) {//xét hàm với con trỏ arr trên toàn bộ m phầN tử
    if (m > 1) {//nếu <1 hoặc =1 thì không cần sắp xếp
        quickSortHelper(arr, 0, m - 1);// cho hàm chạy trên m phần tử
    }
}

void selectionSort(int* arr, int a) { //chọn trỏ arr, giá trị a lớn nhất
    for (int x = 0; x < a - 1; x++) { //xét khoảng 3 tham số vị trí 
        int m = x; // chọn min =x
        for (int y = x + 1; y < a; y++) {  //xét khoảng 3 tham số trừ bỏ vị trí xét đầu tiên
            if (arr[y] < arr[m]) {  // nếu giá trị tại đó nhỏ hơn min
                m = y; //không cần đổi chỗ, vị trí y là min
            }
        }
        if (m != x) { //m khác x
            int t = arr[x];  
            arr[x] = arr[m];     // đổi chỗ
            arr[m] = t;
        }
    }
}

void insertionSort(int* arr, int n) {
    for (int x = 1; x < n; x++) {
        int k = arr[x];
        int y = x - 1;
        while (y >= 0 && arr[y] > k) {
            arr[y + 1] = arr[y];
            y--;
        }
        arr[y + 1] = k;
    }
}
