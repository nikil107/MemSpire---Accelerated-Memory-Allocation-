### **Project Name: MemSpire - High-Speed Memory Allocation Benchmark**  

---

### **README.md**  

# **MemSpire - High-Speed Memory Allocation Benchmark**  

## **Overview**  
MemSpire is a benchmarking project designed to compare standard memory allocation (using `new` and `malloc`) against an optimized approach using object pooling and slab allocation techniques. This project demonstrates how memory allocation strategies affect performance, particularly when dealing with a large number of objects.  

---

## **Features**  
✅ Standard memory allocation using `new` and `delete`  
✅ Optimized memory allocation using object pools and slab allocation  
✅ Benchmarking to measure allocation speed  
✅ Comparison of allocation strategies for large datasets  

---

## **How It Works**  

1. **Standard Allocation:**  
   - Dynamically allocates memory for `Question` and `StudentAnswer` objects using `new`.  
   - Deallocates memory using `delete`.  
   - Slower due to frequent heap allocations and deallocations.  

2. **Optimized Allocation:**  
   - Uses **object pooling** for `Question` objects.  
   - Implements **slab allocation** for `StudentAnswer` objects.  
   - Pre-allocates memory to minimize heap fragmentation and improve speed.  

---

## **Performance Test**  

The project runs two allocation tests with the following parameters:  
- **Number of Questions:** 10,000  
- **Number of Students:** 1,000  

It then measures and prints the execution time for both allocation methods.  

---

## **Installation & Usage**  

### **Requirements**  
- C++ Compiler (g++ / MSVC / Clang)  
- C++11 or later  

### **Compiling the Code**  
To compile the code, run:  
```sh
g++ -o memspire memspire.cpp -O2
```

### **Running the Benchmark**  
Execute the compiled program:  
```sh
./memspire
```

### **Expected Output (Sample)**  
```
Starting Standard Memory Allocation Test...
Standard Allocation Time: 2.35s
Starting Optimized Memory Allocation Test...
Optimized Allocation Time: 0.67s
```
(Note: Execution times may vary based on system hardware and optimization level.)

---

## **Why Use This Approach?**  

🚀 **Speed Improvement** – Avoids frequent heap allocations, reducing overhead.  
💾 **Memory Efficiency** – Uses pre-allocated pools to minimize fragmentation.  
🔄 **Performance Scaling** – Works well for high-performance applications like game engines, databases, and real-time systems.  

---

## **Future Improvements**  
🔹 Multi-threaded allocation support  
🔹 Custom memory allocator for even finer control  
🔹 More extensive benchmarking with different data sizes  

