# MAKEFILE - Tự động hóa quá trình cài đặt môi trường, build và test.
# CTV sử dụng:
# - make venv  : Cài đặt môi trường ảo Python và thư viện
# - make       : Biên dịch mã nguồn C++
# - make test  : Chạy unit test nhanh với mảng nhỏ để debug (in rõ Input/Expected/Actual)
# - make run   : Chạy harness chấm điểm và xuất biểu đồ vào thư mục graphs/

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

ifeq ($(OS),Windows_NT)
    PYTHON ?= python
    VENV_PYTHON = .venv/Scripts/python.exe
    VENV_PIP = .venv/Scripts/pip.exe
    # Tăng kích thước stack trên Windows lên 64MB để Quick Sort đệ quy không bị tràn stack ở N=20000
    LDFLAGS = -Wl,--stack,67108864
else
    PYTHON ?= python3
    VENV_PYTHON = .venv/bin/python
    VENV_PIP = .venv/bin/pip
    LDFLAGS =
endif

.PHONY: all venv setup test run clean

all: student_bin

student_bin: src/main.cpp src/sorts.cpp include/sorts.h
	$(CXX) $(CXXFLAGS) -Iinclude src/main.cpp src/sorts.cpp $(LDFLAGS) -o student_bin

venv:
	$(PYTHON) -m venv .venv
	$(VENV_PYTHON) -m pip install --upgrade pip
	$(VENV_PYTHON) -m pip install -r requirements.txt

setup: venv

test: student_bin
	$(PYTHON) scripts/test_debug.py

run: student_bin
	$(PYTHON) scripts/harness.py

clean:
	rm -rf student_bin student_bin.exe *.png graphs
