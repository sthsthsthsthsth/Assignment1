/*
 * TRÌNH ĐIỀU KHIỂN ĐỂ TEST THUẬT TOÁN.
 * CTV KHÔNG ĐƯỢC SỬA FILE NÀY.
 */

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "../include/sorts.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    if (argc < 2) {
        std::cerr << "Usage: ./student_bin <quick|selection|insertion>\n";
        return 1;
    }
    
    std::string algo = argv[1];
    std::vector<int> arr;
    int num;
    
    // Đọc input
    while (std::cin >> num) {
        arr.push_back(num);
    }

    int n = static_cast<int>(arr.size());
    int* data = arr.data();

    // Bắt đầu bấm giờ (Chỉ đo thời gian của thuật toán, không đo I/O)
    auto start = std::chrono::high_resolution_clock::now();

    if (algo == "quick") quickSort(data, n);
    else if (algo == "selection") selectionSort(data, n);
    else if (algo == "insertion") insertionSort(data, n);
    else {
        std::cerr << "Unknown algorithm: " << algo << "\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // In mảng kết quả ra stdout để Python kiểm tra tính đúng đắn
    for (int i = 0; i < n; ++i) {
        std::cout << data[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n";

    // In thời gian chạy ra stderr để Python thu thập
    std::cerr << duration.count() << "\n";

    return 0;
}
