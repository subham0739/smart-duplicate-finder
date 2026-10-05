# Smart Duplicate File Finder

## 1. Project Overview

Smart Duplicate File Finder is a C++17 command-line application that scans a directory and identifies duplicate files.

The program recursively scans files inside the given directory, groups files based on their size, and then compares files byte-by-byte to accurately identify duplicate files.

It also calculates the amount of storage space that could potentially be recovered by removing duplicate copies.

---

## 2. Problem Statement

Duplicate files can occupy unnecessary storage space and make file management difficult.

Manually finding duplicate files in large directories can be time-consuming.

This project provides a simple automated solution that:

- Scans directories recursively
- Groups files based on file size
- Compares files byte-by-byte
- Identifies duplicate files
- Displays duplicate groups
- Calculates potentially recoverable storage space

---

## 3. Features

- Recursive directory scanning
- Duplicate detection using file size and byte-by-byte comparison
- Handles files inside subdirectories
- Displays duplicate file groups
- Shows individual file sizes
- Calculates potentially recoverable storage space
- Handles inaccessible files gracefully
- Command-line interface
- Written using standard C++17 filesystem functionality

---

## 4. Technologies Used

- **Programming Language:** C++
- **Standard:** C++17
- **Compiler:** g++
- **Build Tool:** Make
- **Libraries:** C++ Standard Library
- **File System:** `std::filesystem`

---

## 5. Project Structure

```text
smart-duplicate-finder/
│
├── README.md
├── Makefile
├── src/
│   └── main.cpp
│
└── test_files/
    ├── file1.txt
    ├── file2.txt
    ├── file3.txt
    └── backup/
        └── file4.txt
```

---

## 6. How the Program Works

The application follows these steps:

### Step 1: Directory Input

The user provides the directory that needs to be scanned.

Example:

```bash
./duplicate_finder test_files
```

### Step 2: Recursive Scanning

The program recursively searches through the selected directory and its subdirectories.

### Step 3: File Size Grouping

Files are first grouped according to their file size.

Files with different sizes cannot be identical, so this reduces unnecessary comparisons.

### Step 4: Byte-by-Byte Comparison

Files having the same size are compared byte-by-byte to confirm whether they are actually identical.

### Step 5: Duplicate Groups

Identical files are placed into duplicate groups.

### Step 6: Storage Calculation

The program calculates the amount of storage that could potentially be recovered if duplicate copies were removed.

---

## 7. Requirements

Before running the project, make sure the following are installed:

- C++ compiler supporting C++17
- g++
- Make

### Check g++ installation

```bash
g++ --version
```

### Check Make installation

```bash
make --version
```

---

## 8. Compilation

Navigate to the project directory:

```bash
cd smart-duplicate-finder
```

Then compile the project using:

```bash
make
```

This creates the executable:

```text
duplicate_finder
```

---

## 9. Running the Program

To scan the included test directory:

```bash
make run
```

Alternatively, run the executable directly:

```bash
./duplicate_finder test_files
```

---

## 10. Clean the Build

To remove the compiled executable:

```bash
make clean
```

---
ARCHITECHTURE
                    ┌──────────────────────┐
                    │        USER          │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │   Folder Selection   │
                    │      / Input         │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │     File Scanner     │
                    │                      │
                    │ • Find files         │
                    │ • Read file details  │
                    │ • Get file size      │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │ Duplicate Detection  │
                    │       Engine         │
                    │                      │
                    │ • Compare files      │
                    │ • Generate/compare   │
                    │   file fingerprints  │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │  Duplicate Grouping  │
                    │                      │
                    │ • Group duplicates   │
                    │ • Separate unique    │
                    │   files              │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │    Results / UI      │
                    │                      │
                    │ • Duplicate files    │
                    │ • File information   │
                    │ • Results summary    │
                    └──────────┬───────────┘
                               │
                               ▼
                    ┌──────────────────────┐
                    │   User Decision      │
                    │                      │
                    │ Review / Manage      │
                    │ duplicate files      │
                    └──────────────────────┘
## 11. Example Usage

```text
============================================
       SMART DUPLICATE FILE FINDER
============================================

Scanning: /project/smart-duplicate-finder/test_files

Files scanned: 4

Duplicate Groups
--------------------------------------------

Group 1
  1. "test_files/file1.txt"
  2. "test_files/backup/file4.txt"
  File size: 50.00 B
  Recoverable: 50.00 B

============================================
Total duplicate groups: 1
Potentially recoverable space: 50.00 B
============================================

Scan completed successfully.
```

The exact output may vary depending on the contents of the files.

---

## 12. Algorithm

The duplicate detection process uses the following approach:

1. Recursively scan the directory.
2. Store files according to their file size.
3. Ignore files that have unique sizes.
4. Compare files with matching sizes byte-by-byte.
5. Group identical files together.
6. Calculate recoverable storage.

### Time Complexity

If `n` files are present, the initial directory scan is approximately **O(n)**.

File comparisons depend on the number and sizes of files having the same size.

### Space Complexity

The program stores file paths grouped by file size, requiring approximately **O(n)** additional storage for the file metadata.

---

## 13. Error Handling

The application checks for:

- Missing directory paths
- Invalid directory paths
- Inaccessible files
- File reading errors
- Invalid command-line arguments

Example:

```text
Usage:
  ./duplicate_finder <directory>
```

---

## 14. Limitations

- The program currently works through the command line.
- It does not automatically delete duplicate files.
- Duplicate detection is based on exact byte-by-byte equality.
- Very large directories may require significant scanning time.
- A cryptographic hash-based comparison could be added in a future version for improved performance.

---

## 15. Future Enhancements

Possible future improvements include:

- Hash-based duplicate detection using SHA-256 or MD5
- Graphical user interface
- Option to safely delete duplicate files
- Export duplicate reports to CSV or JSON
- Progress bar for large directories
- File filtering by extension
- Improved performance using multithreading
- Cross-platform executable releases

---

## 16. Author

**Subham Subhadarsan Sahoo**

B.Tech – Computer Science and Engineering

---

## 17. License

This project is created for academic and educational purposes.
