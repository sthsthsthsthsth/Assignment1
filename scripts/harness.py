"""
Script chấm điểm và đo thời gian tự dộng.
CTV KHÔNG ĐƯỢC CHỈNH SỬA FILE NÀY.
"""

import subprocess
import random
import statistics
import sys
import os
import platform

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8", errors="replace")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8", errors="replace")

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import PchipInterpolator

ALGOS = ["quick", "selection", "insertion"]

# 2 quy mo kich thuoc: bo hoan toan quy mo medium
SIZE_TIERS = {
    "small": {
        "sizes": [0, 50, 100, 200, 300, 400, 500],
        "runs": 5,
        "filename": "small_0_500.png",
        "label": "Small Scale (N = 0 - 500)",
    },
    "large": {
        "sizes": [10000, 12500, 15000, 17500, 20000],
        "runs": 2,
        "filename": "large_10000_20000.png",
        "label": "Large Scale (N = 10000 - 20000)",
    },
}

CASES = ["random", "nearly_sorted", "reverse", "few_unique"]

CASE_TITLES = {
    "random": "Random Uniform (Du lieu ngau nhien phan bo deu)",
    "nearly_sorted": "Nearly Sorted (Du lieu gan nhu da sap xep)",
    "reverse": "Reverse Sorted (Du lieu sap xep nguoc hoan toan)",
    "few_unique": "Few Unique Keys (Du lieu trung lap cuc lon)",
}

CASE_SHORT_NAMES = {
    "random": "Random",
    "nearly_sorted": "Nearly Sorted",
    "reverse": "Reverse",
    "few_unique": "Few Unique",
}

CASE_COLORS = {
    "random": "#1f77b4",        # Xanh duong
    "nearly_sorted": "#2ca02c", # Xanh la
    "reverse": "#d62728",       # Do
    "few_unique": "#9467bd",    # Tim
}

def get_ref_binary():
    sys_os = platform.system().lower()
    machine = platform.machine().lower()
    is_arm = machine in ("arm64", "aarch64")
    if sys_os == "windows":
        return "reference/ref_win_arm64.exe" if is_arm else "reference/ref_win_x64.exe"
    return "reference/ref_linux_arm64" if is_arm else "reference/ref_linux_x64"

REF_BIN = get_ref_binary()
STUDENT_BIN = "./student_bin" if os.name != "nt" else "student_bin.exe"

def _place_medians_for_nearly_sorted(arr, low, high, depth):
    if low >= high or depth <= 0:
        return
    mid = (low + high) // 2
    _place_medians_for_nearly_sorted(arr, low, mid - 1, depth - 1)
    _place_medians_for_nearly_sorted(arr, mid + 1, high, depth - 1)
    med = arr[mid]
    for i in range(mid, high):
        arr[i] = arr[i + 1]
    arr[high] = med

def generate_edge_cases(size, case_type):
    if size <= 0:
        return []

    rng = random.Random(42 + size)

    if case_type == "random":
        return [rng.randint(-100000, 100000) for _ in range(size)]

    elif case_type == "nearly_sorted":
        arr = list(range(size))
        _place_medians_for_nearly_sorted(arr, 0, size - 1, 5)
        return arr

    elif case_type == "reverse":
        return list(range(size, 0, -1))

    elif case_type == "few_unique":
        arr = [5] * size
        num_noise = max(1, size // 50)
        for _ in range(num_noise):
            arr[rng.randint(0, size - 1)] = rng.randint(1, 9)
        return arr

    return [rng.randint(-1000, 1000) for _ in range(size)]

def run_sort(binary, algo, input_data):
    input_str = " ".join(map(str, input_data))
    try:
        process = subprocess.run(
            [binary, algo], input=input_str.encode(),
            stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=15
        )
        if process.returncode != 0:
            print(f"\n[LOI C++]: Chuong trinh bi crash (Exit code {process.returncode}) o thuat toan {algo.upper()}.")
            sys.exit(1)
        
        out_arr = list(map(int, process.stdout.decode().split()))
        time_us = int(process.stderr.decode().strip())
        return out_arr, time_us
    except subprocess.TimeoutExpired:
        print(f"\n[LOI TIMEOUT]: Chuong trinh chay qua 15s hoac bi lap vo tan o thuat toan {algo.upper()}!")
        sys.exit(1)

def run_small_precheck():
    rng = random.Random(2026)
    precheck_cases = [
        ("Mang ngau nhien (15 phan tu)", [rng.randint(-50, 50) for _ in range(15)]),
        ("Mang sap xep nguoc (16 phan tu)", list(range(16, 0, -1))),
        ("Mang trung lap nhieu (18 phan tu)", [rng.choice([1, 2, 2, 2, 3]) for _ in range(18)]),
        ("Mang gan nhu da sort (20 phan tu)", [0, 1, 2, 8, 4, 5, 6, 7, 3, 9, 10, 11, 17, 13, 14, 15, 16, 12, 18, 19]),
    ]

    for algo in ALGOS:
        for label, data in precheck_cases:
            expected_out, _ = run_sort(REF_BIN, algo, data)
            actual_out, _ = run_sort(STUDENT_BIN, algo, data)
            if actual_out != expected_out:
                print("\n" + "=" * 65)
                print(f"[FAIL PRE-CHECK]: THUAT TOAN {algo.upper()} SAI TREN MANG NHO!")
                print("=" * 65)
                print(f"Test case : {label}")
                print(f"Input     : {data}")
                print(f"Expected  : {expected_out}")
                print(f"Actual    : {actual_out}")
                print("=" * 65)
                sys.exit(1)

    print("[PRE-CHECK]: Kiem tra do chinh xac tren mang nho (15-20 phan tu) -> PASS")

def print_debug_info(algo, case_name, input_arr, expected, actual):
    n = len(input_arr)
    print(f"\n" + "=" * 65)
    print(f"[FAIL] THUAT TOAN {algo.upper()} CHO KET QUA SAI")
    print(f"       Bai test: {case_name} | Kich thuoc N = {n}")
    print("=" * 65)
    
    first_diff = -1
    for i in range(min(len(expected), len(actual))):
        if expected[i] != actual[i]:
            first_diff = i
            break
            
    if first_diff != -1:
        print(f"-> Vi tri loi dau tien: index [{first_diff}]")
        print(f"   Ky vong (Expected): {expected[first_diff]}")
        print(f"   Thuc te (Actual)  : {actual[first_diff]}")
        
        start_w = max(0, first_diff - 3)
        end_w = min(n, first_diff + 4)
        print(f"\n-> Snapshot xung quanh index [{first_diff}]:")
        print(f"   Expected[{start_w}:{end_w}]: {expected[start_w:end_w]}")
        print(f"   Actual  [{start_w}:{end_w}]: {actual[start_w:end_w]}")
    else:
        print(f"-> So luong phan tu tra ve bi sai (Ky vong: {len(expected)}, Nhan duoc: {len(actual)})")

    print(f"\n-> Goi y: Chay 'make test' de debug chi tiet tren mang nho.")
    print("=" * 65)
    sys.exit(1)

def plot_near_linear_curve(ax, x_pts, y_pts, linestyle, linewidth, alpha, color, label, marker=None):
    x_arr = np.array(x_pts, dtype=float)
    y_arr = np.array(y_pts, dtype=float)

    if len(x_arr) >= 3:
        x_dense = np.linspace(x_arr.min(), x_arr.max(), 200)
        y_linear = np.interp(x_dense, x_arr, y_arr)
        y_pchip = PchipInterpolator(x_arr, y_arr)(x_dense)
        y_dense = np.clip(0.85 * y_linear + 0.15 * y_pchip, 0, None)
        ax.plot(
            x_dense, y_dense,
            linestyle=linestyle, linewidth=linewidth,
            alpha=alpha, color=color, label=label
        )
        if marker:
            ax.plot(x_arr, y_arr, linestyle='none', marker=marker, color=color)
    else:
        ax.plot(
            x_arr, y_arr,
            linestyle=linestyle, linewidth=linewidth,
            alpha=alpha, color=color, label=label, marker=marker
        )

def save_case_graphs(case, tier_data_student, tier_data_ref):
    algo_colors = {
        "quick": "#1f77b4",     # Xanh duong
        "selection": "#ff7f0e", # Cam
        "insertion": "#2ca02c", # Xanh la
    }

    case_dir = os.path.join("graphs", case)
    os.makedirs(case_dir, exist_ok=True)
    case_title = CASE_TITLES.get(case, case.upper())

    for tier_key, tier_cfg in SIZE_TIERS.items():
        sizes = tier_cfg["sizes"]
        fig, ax = plt.subplots(figsize=(10, 5.5))

        for algo in ALGOS:
            color = algo_colors.get(algo, None)
            plot_near_linear_curve(
                ax, sizes, tier_data_student[tier_key][algo],
                linestyle='-', linewidth=2.2, alpha=0.95, color=color,
                label=f"{algo.upper()} (Student)", marker='o'
            )
            plot_near_linear_curve(
                ax, sizes, tier_data_ref[tier_key][algo],
                linestyle='--', linewidth=1.6, alpha=0.45, color=color,
                label=f"{algo.upper()} (Ref)", marker=None
            )

        ax.set_title(f"{case_title}\n{tier_cfg['label']}", fontsize=11.5, pad=10)
        ax.set_xlabel("So luong phan tu (N)", fontsize=11)
        ax.set_ylabel("Thoi gian chay (us)", fontsize=11)
        ax.legend(loc="upper left", framealpha=0.9)
        ax.grid(True, linestyle=":", alpha=0.6)
        plt.tight_layout()
        out_path = os.path.join(case_dir, tier_cfg["filename"])
        plt.savefig(out_path, dpi=150)
        plt.close()

def save_algorithm_comparison_graphs(all_data_student, all_data_ref):
    """Xuat 3 bieu do so sanh rieng cho tung thuat toan tren ca 4 kich ban du lieu.
    Moi bieu do chia 2 panel: Small Scale (N = 0 - 500) va Large Scale (N = 10000 - 20000)."""
    os.makedirs("graphs", exist_ok=True)

    algo_display_names = {
        "selection": "Selection Sort",
        "insertion": "Insertion Sort",
        "quick": "Quick Sort",
    }

    for algo in ALGOS:
        display_name = algo_display_names.get(algo, algo.upper())
        fig, (ax_small, ax_large) = plt.subplots(1, 2, figsize=(14, 5.8))

        # Panel 1: Small Scale (0 - 500)
        sizes_small = SIZE_TIERS["small"]["sizes"]
        for case in CASES:
            color = CASE_COLORS[case]
            short_name = CASE_SHORT_NAMES[case]
            y_stu = all_data_student[case]["small"][algo]
            y_ref = all_data_ref[case]["small"][algo]

            plot_near_linear_curve(
                ax_small, sizes_small, y_stu,
                linestyle='-', linewidth=2.2, alpha=0.95, color=color,
                label=f"{short_name} (Student)", marker='o'
            )
            plot_near_linear_curve(
                ax_small, sizes_small, y_ref,
                linestyle='--', linewidth=1.5, alpha=0.45, color=color,
                label=f"{short_name} (Ref)", marker=None
            )

        ax_small.set_title(f"{display_name} - Small Scale (N = 0 - 500)", fontsize=11, pad=8)
        ax_small.set_xlabel("So luong phan tu (N)", fontsize=10.5)
        ax_small.set_ylabel("Thoi gian chay (us)", fontsize=10.5)
        ax_small.legend(loc="upper left", framealpha=0.9, fontsize=8.5)
        ax_small.grid(True, linestyle=":", alpha=0.6)

        # Panel 2: Large Scale (10000 - 20000)
        sizes_large = SIZE_TIERS["large"]["sizes"]
        for case in CASES:
            color = CASE_COLORS[case]
            short_name = CASE_SHORT_NAMES[case]
            y_stu = all_data_student[case]["large"][algo]
            y_ref = all_data_ref[case]["large"][algo]

            plot_near_linear_curve(
                ax_large, sizes_large, y_stu,
                linestyle='-', linewidth=2.2, alpha=0.95, color=color,
                label=f"{short_name} (Student)", marker='o'
            )
            plot_near_linear_curve(
                ax_large, sizes_large, y_ref,
                linestyle='--', linewidth=1.5, alpha=0.45, color=color,
                label=f"{short_name} (Ref)", marker=None
            )

        ax_large.set_title(f"{display_name} - Large Scale (N = 10000 - 20000)", fontsize=11, pad=8)
        ax_large.set_xlabel("So luong phan tu (N)", fontsize=10.5)
        ax_large.set_ylabel("Thoi gian chay (us)", fontsize=10.5)
        ax_large.legend(loc="upper left", framealpha=0.9, fontsize=8.5)
        ax_large.grid(True, linestyle=":", alpha=0.6)

        fig.suptitle(f"So sanh Hieu nang: {display_name} giua 4 Kich ban Du lieu", fontsize=13, fontweight="bold", y=0.98)
        plt.tight_layout()

        out_path = os.path.join("graphs", f"compare_{algo}.png")
        plt.savefig(out_path, dpi=150)
        plt.close()

def main():
    if not os.path.exists(STUDENT_BIN):
        print("[LOI]: Khong tim thay file thuc thi student_bin. Hay chay 'make' truoc.")
        return

    if not os.path.exists(REF_BIN):
        print(f"[LOI]: Khong tim thay binary chuan ({REF_BIN}).")
        return

    print(f"--- BAT DAU CHAY AUTO-GRADER (Reference: {REF_BIN}) ---")

    # Buoc 1: Kiem tra do chinh xac tren mang nho 15-20 phan tu
    run_small_precheck()

    all_data_student = {}
    all_data_ref = {}

    # Buoc 2: Chay benchmark tren 4 bai do va 2 khoang kich thuoc (small & large)
    for case in CASES:
        case_title = CASE_TITLES.get(case, case.upper())
        print(f"\n[Case]: {case_title}")

        tier_data_student = {t: {algo: [] for algo in ALGOS} for t in SIZE_TIERS}
        tier_data_ref = {t: {algo: [] for algo in ALGOS} for t in SIZE_TIERS}

        datasets = {}
        expected_outputs = {}
        for tier_key, tier_cfg in SIZE_TIERS.items():
            for size in tier_cfg["sizes"]:
                data = generate_edge_cases(size, case)
                datasets[(tier_key, size)] = data
                expected_outputs[(tier_key, size)] = sorted(data)

        for algo in ALGOS:
            for tier_key, tier_cfg in SIZE_TIERS.items():
                num_runs = tier_cfg["runs"]
                for size in tier_cfg["sizes"]:
                    data = datasets[(tier_key, size)]
                    expected_out = expected_outputs[(tier_key, size)]

                    student_times, ref_times = [], []
                    for run_idx in range(num_runs):
                        actual_out, s_time = run_sort(STUDENT_BIN, algo, data)
                        if run_idx == 0 and actual_out != expected_out:
                            print_debug_info(algo, case, data, expected_out, actual_out)
                        _, r_time = run_sort(REF_BIN, algo, data)
                        student_times.append(s_time)
                        ref_times.append(r_time)

                    tier_data_student[tier_key][algo].append(statistics.median(student_times))
                    tier_data_ref[tier_key][algo].append(statistics.median(ref_times))

            print(f"  [{algo.upper():<9}] -> PASS")

        save_case_graphs(case, tier_data_student, tier_data_ref)
        all_data_student[case] = tier_data_student
        all_data_ref[case] = tier_data_ref

    # Buoc 3: Xuat 3 bieu do so sanh xuyen suot tung thuat toan qua 4 kich ban
    save_algorithm_comparison_graphs(all_data_student, all_data_ref)

    print("\n[INFO]: Tat ca test deu dung! Da xuat bieu do vao thu muc graphs/:")
    for case in CASES:
        print(f"  - graphs/{case}/ (small_0_500.png, large_10000_20000.png)")
    print("  - graphs/compare_selection.png (So sanh Selection Sort qua 4 kich ban)")
    print("  - graphs/compare_insertion.png (So sanh Insertion Sort qua 4 kich ban)")
    print("  - graphs/compare_quick.png     (So sanh Quick Sort qua 4 kich ban)")

if __name__ == "__main__":
    main()
