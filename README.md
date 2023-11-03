# Multithreaded-Sorting
A c program that utilizes multithreading to accomplish the task of integer sorting

Program Overview:
----------------------------------------------------------------------------------
 This is a C program that utilizes multithreading to accomplish the task of integer sorting. 
 Specifically, a list of integers should be divided into two sub-lists of integers by your 
 program. The size of the sub-lists should be the same (note that when the total number of 
 integers is odd, the integer in the middle of the list should only be included in one of the sub-lists). 
 Then two separate threads (which are called “sorting threads”) are created. 
 Each of them sorts a sub-list using a sorting algorithm of your choice. Finally, 
 the sorted sub-lists are merged into a single sorted list by a third thread 
 (which is called a “merging thread”).

 Program instruction:
----------------------------------------------------------------------------------
 using gcc -pthread -o main main.c to compile
 Then execute the main file using ./main
 User can use cat to display the SortedIntegerList.txt to see the result: cat SortedIntegerList.txt

Program Info:
---------------------------------------------------------------------------------
 Author: Tang-Y
