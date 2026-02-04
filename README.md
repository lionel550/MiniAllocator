# MiniAllocator

A minimal, educational memory allocator written in C. The goal of this project was to learn the fundamentals of memory management, pointer arithmetic, and fragmentation handling.

## Learning Resources

This project was heavily inspired by **gingerBill's** excellent series on memory allocation strategies:

* [Memory Allocation Strategies - gingerBill](https://www.gingerbill.org/series/memory-allocation-strategies/)

## Features

* **First-Fit Strategy**: Searches the free list for the first block that fits the requested size.
* **Alignment Support**: Handles custom memory alignment (e.g., 8-byte or 16-byte alignment).
* **Coalescence**: Automatically merges adjacent free memory blocks to prevent fragmentation.
* **Simple API**: Easy-to-use `init_heap`, `my_alloc`, and `my_free` functions.

## How to Build

To compile the project using the provided Makefile, run:

```bash
make

```

To run the included demo:

```bash
./allocator_demo

```
