 MP2: Acceleration Computation with SIMD in x86-64

Group Members
- Wesley Sy
- Ian Sayat

 Program Overview

- The `main.c` file handles:
  - Input collection (manual or randomized)
  - Memory allocation
  - Output printing

- The `asmfunc.asm` file (in x86-64 SIMD) handles:
  - Velocity conversion from km/h to m/s
  - Acceleration calculation
  - Conversion from `float` to `int`


Performance Analysis

We tested the ASM function for different values of input size `Y`:
- `Y = 10`
- `Y = 100`
- `Y = 1000`
- `Y = 10000` 

Execution Times (averaged over 30 runs)

| Input Size | Average Time (ms) |
|------------|-------------------|
| 10         | 0.000000            |
| 100        | 0.000000           |
| 1000       | 0.000000           |
| 10000      | 0.000033            |

 Performance Insights
- SIMD reduces computation time significantly due to parallelism.
- Performance gain is more evident with larger input sizes.


Output Correctness Check




## 📹 Video Demonstration

The video below shows:
- Code explanation
- Compilation of both C and ASM
- Running the program and checking results

Gdrive Link:
https://drive.google.com/file/d/1tp6i1VTGvmv3dQIAhC85Qpbu3YTeLz6r/view?usp=sharing
