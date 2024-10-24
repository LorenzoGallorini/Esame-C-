# C++ Binary Search Tree Project

This project implements a generic class that represents a binary search tree (BST) in C++. The class prevents the insertion of duplicate data and allows users to define the strategy for comparing two data values. It also features an iterator and methods for manipulating and traversing the tree.

## Project Overview

The core of the project is the `ABR<T, C, D>` class, where:
- **T**: Data type stored in the tree.
- **C**: Comparison strategy to determine if a value is greater or less than another.
- **D**: Strategy to check if two values are equal, preventing duplicate entries.

### Key Features:
1. **Node Structure**: 
   - Each node holds a value, pointers to its left and right children, and a pointer to its parent for easy traversal.
   
2. **Class Methods**:
   - **Add**: Adds a node to the tree, ensuring correct placement according to the defined comparison strategy.
   - **Remove**: Removes a node from the tree, with special handling for leaf nodes, nodes with one child, and nodes with two children.
   - **Count**: Returns the total number of nodes in the tree.
   - **Find**: Checks if a value exists in the tree.
   - **SubTree**: Returns a new tree rooted at a specific node.

3. **Iterator**:
   - The tree can be traversed using a forward-only, read-only iterator that follows an in-order logic for printing the contents.
   
4. **Error Handling**: 
   - The project includes custom exceptions for common issues such as attempting to insert duplicate data or performing operations on uninitialized trees.

### Additional Functionality:
- **PrintIF**: A global function that prints all tree nodes that satisfy a given predicate.
- **MinimumValue**: Returns the smallest value (leftmost node) in the tree.

## Error Handling

The project includes robust error handling with custom exceptions for different cases:
- **Elemento_gia_inserito_exception**: Thrown when attempting to insert a duplicate element (error code: -1).
- **Elemento_non_trovato_exception**: Thrown when trying to perform operations on a non-existent node (error code: -2).
- **Albero_non_inizializzato_Exception**: Thrown when attempting operations on an uninitialized tree (error code: -3).
- **New_Nodo_Bad_Alloc_Exception**: Thrown when memory allocation fails during node creation (error code: -4).

## Debugging

The project was thoroughly tested using statement coverage and memory leak tests:
- **Statement Coverage**: Achieved 100% statement coverage.
- **Memory Leak Tests**: Performed using Valgrind on MacOS Mojave and Linux Mint, with no memory leaks detected.

## GUI Project (Qt)

The project also includes a simple graphical user interface (GUI) built using **Qt** to display artists from two major music labels. It downloads artist data and displays it in a table and renders graphs based on the initial letter of each artist.

### Key Features:
1. **Download Data**: Downloads artist data from a server and processes it into a string list.
2. **Table Display**: Displays artist data using `QLabel` widgets inside a table.
3. **Graphical Output**: Creates bar charts based on the initial letter of the artists' names.
4. **Debugging**: Memory leak tests were performed on Linux Mint, with no issues found.
