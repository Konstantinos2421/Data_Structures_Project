# Data Structures Project
A project on Data Structures. An implementation of usual sorting and searching algorithms, AVL trees, and hash tables.  
The whole project is implemented with C++.  
At first we collect data from ocean.csv file, which contains measurements of the temperature (in °C) of the ocean water and the recordings of Phosphate, Nitrite, Nitrate, Salinity, Oxygen for the period 2000 to 2015.
The purpose of the project is to create data structures with the given data and execute several algorithms on these structures.

### Files In Project:
- **sorting_algorithms**
  - heap_sort-counting_sort.cpp: Code that implements the Heap Sort and Counting Sort algorithms in order to sort the csv file data in ascending temperature order.
  - insertion_sort-quick_sort.cpp: Code that implements the Insertion Sort and Quick Sort algorithms in order to sort the csv file data in ascending order of phosphate. values.
- **searching_algorithms**
  - binary_search-interrpolation_search.cpp: Code that implements the Binary Search and Interpolation Search algorithms in order to find the temperature and phosphate values for a specific date given by the user.
  - BIS-BIS_optimized.cpp: Code that implements the BIS(Binary Interpolation Search) algorithm and an optimized version of it in order to find the temperature and phosphate values for a specific date given by the user.
- **AVL_trees**
  - AVL_ordered_by_date.cpp: Code that implements an AVL tree data structure in which data of the csv file are ordered by date. User has the choice to depict the AVL tree using in-order traversal, search temperature for a specific date, modify temperature value for a specific date and delete a record for a specific date.
  - AVL_ordered_by_temperature.cpp: Code that implements an AVL tree data structure in which data of the csv file are ordered by temperature. User has the choice to see the date/dates with the lower and higher temperature values.
- **hash_tables**
  - hash_table_with_chaining.cpp: Code than implements hash table with chaining data structure to store data from the csv file. Hashing is performed based on date values of the csv file records. User has the choice to search temperature for a specific date, modify temperature value for a specific date and delete a record for a specific date.

