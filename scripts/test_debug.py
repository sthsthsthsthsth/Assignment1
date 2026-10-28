"""
SCRIPT DEBUG NHANH DÀNH CHO CTV.
Tự động test 3 thuật toán (Quick Sort, Selection Sort, Insertion Sort) với các mảng nhỏ (N <= 20)
và các ca biên (edge-cases). Nếu có lỗi, in toàn bộ Input, Expected và Actual.
"""

import subprocess
import sys
import os
import platform

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")

def get_ref_binary():
    sys_os = platform.system().lower()
    machine = platform.machine().lower()
    is_arm = machine in ("arm64", "aarch64")
    if sys_os == "windows":
        return "reference/ref_win_arm64.exe" if is_arm else "reference/ref_win_x64.exe"
    return "reference/ref_linux_arm64" if is_arm else "reference/ref_linux_x64"

REF_BIN = get_ref_binary()
STUDENT_BIN = "./student_bin" if os.name != "nt" else "student_bin.exe"
ALGOS = ["quick", "selection", "insertion"]

SMALL_TEST_CASES = [
    ("Mang rong", []),
    ("Mang 1 phan tu", [42]),
    ("Mang 2 phan tu da sort", [1, 2]),
    ("Mang 2 phan tu nguoc", [2, 1]),
    ("Mang 3 phan tu bang nhau", [5, 5, 5]),
    ("Mang co so am", [0, -5, 10, -20, 3, -1]),
    ("Mang trung lap nhieu (15 phan tu)", [5, 5, 1, 5, 5, 2, 5, 5, 5, 3, 5, 5, 1, 5, 5]),
    ("Mang nguoc hoan toan (16 phan tu)", list(range(16, 0, -1))),
    ("Mang gan nhu da sort (18 phan tu)", [0, 1, 2, 3, 9, 5, 6, 7, 8, 4, 10, 11, 12, 17, 14, 15, 16, 13]),
    ("Mang ngau nhien (20 phan tu)", [12, -3, 45, 0, 23, 7, -15, 88, 3, 19, -2, 14, 5, 9, 31, -9, 27, 6, 11, -1]),
]

def run(binary, algo, data):
    input_str = " ".join(map(str, data))
    proc = subprocess.run(
        [binary, algo], input=input_str.encode(),
        stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=5
    )
    if proc.returncode != 0:
        return None, f"Runtime Error (Exit Code {proc.returncode})"
    out = list(map(int, proc.stdout.decode().split()))
    return out, None

def main():
    if not os.path.exists(STUDENT_BIN):
        print(f"[LOI]: Khong tim thay {STUDENT_BIN}. Hay go 'make' de bien dich truoc.")
        sys.exit(1)

    print("=" * 65)
    print(f"CHAY UNIT TEST & DEBUG VOI MANG NHO (Reference: {REF_BIN})")
    print("=" * 65)

    all_passed = True
    for algo in ALGOS:
        print(f"\n---> Kiem tra thuat toan: {algo.upper()}")
        algo_passed = True
        for name, data in SMALL_TEST_CASES:
            ref_out, ref_err = run(REF_BIN, algo, data)
            stu_out, stu_err = run(STUDENT_BIN, algo, data)

            if stu_err:
                print(f"  [FAIL] {name}: {stu_err}")
                algo_passed = False
                all_passed = False
                continue

            if stu_out != ref_out:
                print(f"  [FAIL] {name}")
                print(f"         Input   : {data}")
                print(f"         Expected: {ref_out}")
                print(f"         Actual  : {stu_out}")
                algo_passed = False
                all_passed = False
            else:
                print(f"  [PASS] {name} (N = {len(data)})")

        if algo_passed:
            print(f"  => Ket qua: {algo.upper()} pass toan bo cac test case nho!")

    print("\n" + "=" * 65)
    if all_passed:
        print("[SUCCESS]: Tat ca unit test deu vuot qua! Ban co the chay 'make run' de cham diem.")
    else:
        print("[FAIL]: Co test case bi sai, hay kiem tra lai code trong src/sorts.cpp.")
    print("=" * 65)

if __name__ == "__main__":
    main()
