# Sorting Algorithm Analysis

Execution times of 6 sorting algorithms were analyzed for an input of 100,000 integers in random, sorted and reverse sorted orders.
The goal was to analyze the performence of the algorithms against each other and the distribution of the data.
Sorting algorithms analyzed are *Insertion Sort*, *Selection Sort*, *Bubble Sort*, *Merge Sort*, *Quick Sort* and *Heap Sort*.

A detailed report can be found [here](https://github.com/bahadirozkan/sortingAlgorithms/blob/master/Analysis%20of%20Sorting%20Algorithms.pdf). \
I'll try to make time for the optimization of the code.

## Results:
• Insertion Sort gave the best results for the sorted data
due to the time complexity of Ω(n). \
• High-level algorithms which are Merge, Quick and
Heap Sort performed better over the rest. Quick Sort
among them needed less time to execute. (See figure
2) \
• Bubble Sort had the worst performance. (See figure 1) \
• Merge Sort’s, Selection Sort’s and Heap Sort’s
performance was not affected much by the order.
Whereas Insertion Sort was affected the most. \
• Choosing the middle item as pivot in Quick Sort
worked as expected and prevented the worst-case
scenario.

![Fig1](https://user-images.githubusercontent.com/20925510/68382828-8ef58080-0165-11ea-8e2b-85ef3211a860.JPG)
![Fig2](https://user-images.githubusercontent.com/20925510/68382851-99b01580-0165-11ea-8f63-bfab0969ecb2.JPG)
