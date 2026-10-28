/*
 * REFERENCE IMPLEMENTATION (OPTIMIZED SEQUENTIAL SORTS)
 * - Sequential execution only (NO multi-threading / OpenMP).
 * - Quick Sort: NON-RECURSIVE (Iterative) implementation with explicit stack,
 *   Median-of-3 pivot selection, and 3-way Dutch National Flag partitioning.
 * - Selection & Insertion Sort: C/C++ modern optimizations (__restrict__,
 *   __builtin_assume_aligned, __builtin_expect branch hints, 4x unrolling, and 1-line asm fence).
 */

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O3,unroll-loops,tree-vectorize,fast-math")
#endif

#include "../include/sorts.h"
#include <utility>
#include <cstring>

#if defined(__clang__) || defined(__GNUC__)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#define UNLIKELY(x) (x)
#endif

namespace {

// Hint to tell compiler pointer is aligned & non-null for fast memory access
static inline int* assume_aligned_ptr(int* ptr) noexcept {
#if defined(__clang__) || defined(__GNUC__)
    return static_cast<int*>(__builtin_assume_aligned(ptr, 16));
#else
    return ptr;
#endif
}

// Single-line inline asm memory barrier to prevent redundant reloads
static inline void cpu_fence() noexcept {
    __asm__ volatile ("" ::: "memory");
}

// Branchless swap helper for median-of-3 network
static inline void cond_swap(int& a, int& b) noexcept {
    int tmp = a;
    bool gt = (a > b);
    a = gt ? b : tmp;
    b = gt ? tmp : b;
}

} // namespace

// 1. Quick Sort (NON-RECURSIVE / Iterative):
// - Explicit local stack (zero recursion call overhead, O(log N) bounded stack)
// - Median-of-3 pivot selection (immune to sorted / reverse-sorted worst cases)
// - 3-way partitioning (Dutch National Flag: handles duplicate keys in O(N))
void quickSort(int* __restrict__ raw_arr, int n) {
    if (n <= 1) return;
    int* __restrict__ arr = assume_aligned_ptr(raw_arr);

    struct Range {
        int low;
        int high;
    };

    // Explicit stack replaces recursion (depth never exceeds 64)
    Range stack[64];
    int top = 0;
    stack[top++] = {0, n - 1};

    while (top > 0) {
        Range cur = stack[--top];
        int low = cur.low;
        int high = cur.high;

        if (low >= high) continue;

        // Sort 3 elements (low, mid, high) branchlessly to pick median pivot
        int mid = low + ((high - low) >> 1);
        cond_swap(arr[low], arr[mid]);
        cond_swap(arr[low], arr[high]);
        cond_swap(arr[mid], arr[high]);
        int pivot = arr[mid];

        // 3-way partition: [low .. lt-1] < pivot, [lt .. gt] == pivot, [gt+1 .. high] > pivot
        int lt = low;
        int i = low;
        int gt = high;

        while (i <= gt) {
            int val = arr[i];
            if (val < pivot) {
                arr[i++] = arr[lt];
                arr[lt++] = val;
            } else if (val > pivot) {
                arr[i] = arr[gt];
                arr[gt--] = val;
            } else {
                ++i;
            }
        }

        // Push larger partition first to guarantee stack depth <= 2 * log2(N)
        int left_len = (lt - 1) - low;
        int right_len = high - (gt + 1);
        if (left_len > right_len) {
            if (low < lt - 1) stack[top++] = {low, lt - 1};
            if (gt + 1 < high) stack[top++] = {gt + 1, high};
        } else {
            if (gt + 1 < high) stack[top++] = {gt + 1, high};
            if (low < lt - 1) stack[top++] = {low, lt - 1};
        }
    }
    cpu_fence();
}

// 2. Selection Sort:
// - Double-ended (Min-Max) Selection Sort + 4x loop unrolling + __builtin_expect branch prediction hint
// - Halves the number of passes and breaks dependency chains
void selectionSort(int* __restrict__ raw_arr, int n) {
    if (n <= 1) return;
    int* __restrict__ arr = assume_aligned_ptr(raw_arr);

    int left = 0;
    int right = n - 1;

    while (left < right) {
        int min_idx = left;
        int max_idx = right;
        if (arr[min_idx] > arr[max_idx]) {
            int tmp = arr[min_idx];
            arr[min_idx] = arr[max_idx];
            arr[max_idx] = tmp;
        }

        int min_val = arr[left];
        int max_val = arr[right];

        int j = left + 1;
        const int limit = right - 3;

#if defined(__clang__)
        #pragma clang loop unroll_count(4)
#elif defined(__GNUC__)
        #pragma GCC unroll 4
#endif
        for (; j < limit; j += 4) {
            int v0 = arr[j], v1 = arr[j + 1], v2 = arr[j + 2], v3 = arr[j + 3];
            if (UNLIKELY(v0 < min_val)) { min_val = v0; min_idx = j; }
            else if (UNLIKELY(v0 > max_val)) { max_val = v0; max_idx = j; }

            if (UNLIKELY(v1 < min_val)) { min_val = v1; min_idx = j + 1; }
            else if (UNLIKELY(v1 > max_val)) { max_val = v1; max_idx = j + 1; }

            if (UNLIKELY(v2 < min_val)) { min_val = v2; min_idx = j + 2; }
            else if (UNLIKELY(v2 > max_val)) { max_val = v2; max_idx = j + 2; }

            if (UNLIKELY(v3 < min_val)) { min_val = v3; min_idx = j + 3; }
            else if (UNLIKELY(v3 > max_val)) { max_val = v3; max_idx = j + 3; }
        }

        for (; j < right; ++j) {
            int v = arr[j];
            if (UNLIKELY(v < min_val)) { min_val = v; min_idx = j; }
            else if (UNLIKELY(v > max_val)) { max_val = v; max_idx = j; }
        }

        arr[min_idx] = arr[left];
        arr[left] = min_val;

        if (max_idx == left) {
            max_idx = min_idx;
        }
        arr[max_idx] = arr[right];
        arr[right] = max_val;

        ++left;
        --right;
    }
    cpu_fence();
}

// 3. Insertion Sort:
// - Fast early skip when key >= arr[i - 1] (O(N) for sorted/nearly-sorted)
// - Prefix sorted guarantee: block shift 4 elements using std::memmove
void insertionSort(int* __restrict__ raw_arr, int n) {
    if (n <= 1) return;
    int* __restrict__ arr = assume_aligned_ptr(raw_arr);

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        if (key >= arr[i - 1]) continue;

        int j = i - 1;

        while (j >= 3 && arr[j - 3] > key) {
            std::memmove(&arr[j - 2], &arr[j - 3], 4 * sizeof(int));
            j -= 4;
        }

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
    cpu_fence();
}
