# LBYARCH-MP2: Car Acceleration Calculator (C + x86-64 ASM with Scalar SIMD)

Section: S11A

Group #10
- Cansino, Joehanna
- Caya, Mary Faye
- Sena, Sophia Pauline

Date: July 27, 2025

# PROBLEM DESCRIPTION
This project computes the acceleration of multiple cars over a 1KM distance using initial and final velocities (in KM/H) and time taken (in seconds). The goal is to implement a high-performance solution using C for orchestration and x86-64 Assembly with Scalar SIMD floating-point instructions for computation.

Given:
vi = initial velocity (double, km/h)
vf = final velocity (double, km/h)
t = time elapsed (double, seconds)

Formula:
1. Convert velocities from KM/H to m/s:
   m/s = (KM/H × 1000) / 3600 = KM/H × 0.27777777778
   
2. Compute acceleration:
   a = (vf - vi) / t

3. Convert to integer:
   Final result is truncated using SIMD instruction cvttsd2si

# COMPILATION AND EXECUTION INSTRUCTIONS

Prerequisites:
- NASM Assembler (We used version 2.16rc12 (compiled Dec 7, 2022) )
- GCC Compiler (We used TDM64 GCC 10.3.0)

For Windows:
1. Open CMD and navigate to your project folder (your/path/here).
2. Run these commands.
  nasm -f win64 compute_acceleration.asm -o compute_acceleration.obj
  gcc -std=c99 -c Main.c -o Main.obj -m64
  gcc Main.obj compute_acceleration.obj -o main.exe -m64 -mconsole
  main.exe

For macOS:
1. Open Terminal and navigate to your project folder (your/path/here).
2. Run these commands:
  nasm -f macho64 accel.asm -o accel.o
  gcc -O2 -arch x86_64 main.c accel.o -o main
  ./main

Notes:
- Replace "your/path/here" with the full path to your project directory.
- On Windows, use Command Prompt or PowerShell.
- On macOS, use Terminal.
- Ensure NASM and GCC are installed and available in your system PATH.

# SAMPLE INPUT AND OUTPUT

INPUT:
  Enter number of rows: 3
  Enter Vi, Vf, and T for each row:
  Row 1:
    Vi (km/h): 0.0
    Vf (km/h): 62.5
    T (s): 10.1
  Row 2:
    Vi (km/h): 60.0
    Vf (km/h): 122.3
    T (s): 5.5
  Row 3:
    Vi (km/h): 30.0
    Vf (km/h): 160.7
    T (s): 7.8

OUTPUT:
  Results: Acceleration values (in m/s^2):
    Row 1: 2 m/s^2
    Row 2: 3 m/s^2
    Row 3: 5 m/s^2

# CORRECTNESS VERIFICATION
To ensure the accuracy of our acceleration calculations, we cross-checked the results using the Online Acceleration Calculator (Symbolab and Omni).

How to verify:
1. Input the initial velocity (Vi) in km/h.
2. Input the final velocity (Vf) in km/h.
3. Input the time (T) in seconds.
4. The calculator outputs acceleration in m/s².

Our program’s computed acceleration values match the results from this reliable tool, validating the correctness of our assembly and C code implementation.

# SIMD Notes

SIMD Used:
- The assembly function utilizes the SSE2 scalar floating-point registers (xmm0–xmm7).
- Instructions such as movsd (move scalar double), subsd (subtract scalar double), mulsd (multiply scalar double), divsd (divide scalar double), and roundsd (round scalar double) implement the arithmetic operations.
- The conversion from floating-point to integer uses cvtsd2si, which converts a scalar double in an xmm register to a 32-bit integer.
- This approach provides efficient vectorized floating-point operations without the complexity of full vector SIMD (like AVX) and is well suited for scalar computations on double values.

