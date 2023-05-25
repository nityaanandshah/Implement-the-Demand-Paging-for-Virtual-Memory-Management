# Implement the Demand Paging for Virtual Memory Management

## Program Description

The program implements demand paging for virtual memory management. The inputs to the program include:
1. Total number of processes (k)
2. Maximum number of pages required per process (m)
3. Total number of frames in main memory (f) [m > f]
4. Size of the TLB (s) [s < f]

## Implementation

1. The program uses a hashmap of integers to implement the TLB and vectors of length equal to the size of total pages to implement the page table. A list of integers is used to represent the free frames. All frames are initially set to -1.

2. When the operating system requests a page, the program first searches the TLB map. If the page number is found, it's a TLB hit, and the program prints the TLB hit message along with the associated frame number.

3. If the page number is not found in the TLB and there is a miss, the program consults the page table to search for the entry of the referred page. If the page number is valid (present in main memory), the program prints the TLB miss message, valid page table, and the frame number.

4. If the requested page is invalid and not found in the page table, it is considered a page fault.

5. When a page fault occurs, the program checks if any empty free frame is available. If there are free frames, the program updates the page table and assigns a free frame.

6. If all free frames are exhausted, a page replacement policy is used to accommodate the new frame in the page table. In our case, the LRU (Least Recently Used) page replacement policy is used to select the victim page and replace it with the required frame in the page table.

## Running the Program

1. Download the provided zip folder and extract all the files.
2. Open the "Lab05" folder and open the terminal in that folder.
3. Run the following commands:
  - $ g++ code.cpp -o code
  - $ ./out

## Input

Provide the following inputs:
1. Total number of processes
2. Maximum number of pages per process
3. Total number of frames in main memory (size of TLB)

## Output

For each process, the program will print the pages, frames, and the range allotted for each step. It will also print the description corresponding to each entry of the reference string.

Example:
- Total number of processes: 5
- Maximum number of pages per process: 8
- Total number of free frames: 3
- TLB size: 3 
