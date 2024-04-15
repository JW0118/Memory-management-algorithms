# Memory-management-algorithms
c++ Program that simulates different memory management algorithms
This program simulates various memory manegement algoritms. The algorithms in the program are lru, optimal, and fifo. Each algorithm is split into their own respective functions that each simulate the performance of the algorithm. Apon running the program the user will be shown each step/iteration of the algorithm until the end of the page reference string is over. 
The LRU algorithm replaces the page that has not been used for the longest time. The program does this by keeping a list of currently loaded pages and when a page needs to be replaced. It is removed and then a new page is added at the end of the list indicating it is the most recently used page.
The optimal algorithm replaces the page that will not be used for the longest time. The program iterates over the reference string to simulate future access and findes the page that is not used for the longest time.
The FIFO algorith replaces pages based on when they are recieved. When a page is needing to be replaced the algorithm will remove the page that was loaded first.
