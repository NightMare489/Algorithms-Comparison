<a name="_page2_x29.00_y32.00"></a>**Abstract** 

This project investigates the differences between the theoretical runtime complexities (O notation) and the measured runtime of various sorting and searching algorithms. Specifically, we focus on Bubble Sort and Quick Sort for sorting, and Brute Force and Boyer-Moore for string searching. The benchmarking methodology is described, and results are presented using both 2D and 3D graphs, along with statistical analysis of the runtime data. 

<a name="_page2_x29.00_y145.00"></a>**Libraries Used** 

The following libraries were used in the benchmarking and visualization process: 

**Standard C++ Libraries**: Included for fundamental functionalities such as input/output, time measurement, random number generation, and threading. 

**Matplotlib for C++**: The **Matplotlib-CPP** library, a C++ wrapper for the popular Python plotting library Matplotlib, was used for generating the visualizations. Needs **Python 3.11.4** installed. 

<a name="_page2_x29.00_y272.00"></a>**Introduction** 

Algorithm analysis is a critical aspect of computer science, providing insights into the efficiency of algorithms. Theoretical runtime complexities, often expressed in Big O notation, describe the upper bound of an algorithm's performance. However, actual runtime can differ due to various factors such as implementation details, input data, and hardware. This project compares the theoretical and measured runtimes of selected algorithms to understand these differences better.

<a name="_page2_x29.00_y400.00"></a>**Algorithms and Theoretical Analysis** 

<a name="_page2_x29.00_y435.00"></a>**Sorting Algorithms:** 

<a name="_page2_x29.00_y462.00"></a>**Bubble Sort:** 

Bubble Sort is a simple comparison-based algorithm that repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order.

Bubble Sort’s time complexity is quadratic ***O*(n2)**, because it performs multiple comparisons and swaps in nested loops. Each outer loop iteration compares each element to all other elements, hence the ***O*(n²)** complexity. 

<a name="_page2_x29.00_y587.00"></a>**Quick Sort:** 

Quick Sort is a divide-and-conquer algorithm that selects a pivot element and partitions the array into two halves, sorting them recursively. 

Quick Sort’s efficiency comes from partitioning the array into two subarrays and recursively sorting them. On average, this leads to **log n** levels of recursion with n comparisons at each level, resulting in ***O*(n log n).** However, poorly chosen pivots can lead to ***O*(n²)** complexity. 



<a name="_page3_x29.00_y55.00"></a>**Brute<a name="_page3_x29.00_y32.00"></a> Force Search:** 

<a name="_page3_x29.00_y79.00"></a>The Brute Force search algorithm iterates over the text and for each character, it compares the entire pattern. This results in **m** comparisons for each of the **n** characters in the text, leading to ***O*(mn)** complexity.** 

**Boyer-Moore Search:** 

The Boyer-Moore algorithm improves the search efficiency by skipping sections of the text based on mismatched character information.<a name="_page3_x237.00_y174.00"></a> This allows for fewer comparisons in practice, often leading to sublinear time complexity ***O*(m/n)**. The worst-case scenario occurs when every character is compared ***O*(n2)**., but this is rare due to the algorithm’s heuristics. 

**Benchmarking Methodology** 

The benchmarking process involved running each algorithm on varying sizes of input data and measuring the execution time using the chrono library in C++. For sorting algorithms, random integer vectors of increasing size were used. For searching algorithms, random strings with embedded substrings were generated. Each test was repeated multiple times to average out inconsistencies and reduce noise.

<a name="_page3_x29.00_y335.00"></a>**Random Data Generation**: 

**Sorting**: Used custom made function generateRandomVector to create vectors of random integers. **Searching**: Used custom made function generateRandomStringWithSubstring to create random strings with embedded substrings.

<a name="_page3_x29.00_y412.00"></a>**Benchmarking:** 

**Time Measurement:** The benchmark function measured the execution time of the algorithms using chrono library 

**Repetitions:**  Each  algorithm  was  tested  multiple  times  to  ensure  reliable  average  runtime measurements. 

<a name="_page3_x29.00_y511.00"></a>**Threading:** 

Threading was used in the benchmarking process for several key reasons:

**Concurrent Execution:** Threading allows for multiple tasks to run concurrently, improving the overall efficiency of the benchmarking process. By running the sorting and searching benchmarks simultaneously  on  different  threads,  we  can  utilize  the  multi-core  capabilities  of  modern processors. This parallelism reduces the total time required to complete all benchmarks.

**Real-Time Plotting:** Using a separate thread for plotting ensures that the visualization of results does not block the execution of the benchmarks. The plotting thread continuously updates the graphs  with  new  data  points  without  waiting  for  the  benchmarks  to  complete.  This  real-time feedback helps in monitoring the progress and performance of the algorithms as the benchmarks run. 



<a name="_page4_x29.00_y32.00"></a>**Results** 

<a name="_page4_x29.00_y57.00"></a>**Sorting Algorithms** 

**Bubble Sort:** The measured runtime increased quadratically with input size, consistent with the theoretical ***O*(n2)** complexity. 

**Quick Sort:** The runtime generally followed an ***O*(n log n)** trend, though occasional spikes indicated worst-case behavior. 

|<p>**Array  Bubble Sort** </p>|<p>**Size  Avg Time (µs)** </p>|**Quick Sort Avg Time (µs)** 
| - | :- | :- |
|500  |184 |16 ||
|1000 | 615 | 47 |||
|1500|  1359 |79 ||
|2000 | 9717 | 90 |||
|2500 | 3860 |119 ||
|3000 | 6551 | 145 |||
|3500 | 8390 |177 ||
|4000 | 9866 | 178 |||
|4500 |12685 |248 |
|5000 | 18656 | 256 |||
|5500 |19353 |258 |
|6000  |22651 | 311 |||
|. |. |. |
|. | . | . |||
|. |. |. |
|12000 | 111671 | 612 |||
|12500 |124034 |751 |
|13000 | 135001  |645 |||
|13500 |148614 |863 |
|14000 | 160519 | 699 |||
|14500 |176540 |740 |
|15000  |192341 | 871 |||
|. |. |. |
|. | .  |. |||
|. |. |. |
|193000 | **-**  |12311 |||
|193500 | **-** |12178 ||
|194000 | **-** | 12479 |||
|194500 |**-** |12235 |
|195000 | **-** | 12116 |||
|195500 |**-** |12153 |
|196000 | **-** | 12532 |||
|196500 | **-** |12238 ||
|197000 | **-** | 12750 |||
|197500 |**-** |12404 |
|198000 | **-**  |12439 |||
|198500 | **-** |12667 ||
|199000 | **-** | 12562 |||
|199500 ||**-** |12710 |
|200000 | **-** | 12462 |||

![Aspose Words b287eb9e-737a-471b-bc47-d3af436b5d89 024](https://github.com/NightMare489/Algorithms-Comparison/assets/56297925/3e595b34-f1cd-4cb3-8723-411fc3bd149d)


<a name="_page4_x29.00_y57.00"></a>**Searching Algorithms** 

**Brute<a name="_page5_x29.00_y32.00"></a> Force Search:** The runtime increased linearly with text size and quadratically with substring size, matching the ***O*(m\*n)** complexity. 

**Boyer-Moore Search:** The runtime showed significant improvements over Brute Force, especially with larger texts and substrings, reflecting its better average-case complexity. 





|<p>**String  Pattern** </p>|<p>**Size  Size** </p>|**Brute Force Avg (µs)** |**Boyer-Moore Avg (µs)**
| - | :-: | :-: | :- |
|2 | 1 |0 |1 |
|1002 | 1 | 2 | 0 |||
|1002 | 1001 |531 |1 |
|2002  |1 | 4  |0 ||||
|2002|  1001 |1595 |1 ||
|2002 | 2001 | 2137 | 2 ||||
|3002 | 1 |6 |0 ||
|3002 | 1001 | 2892 | 2 ||||
|3002 | 2001 |4300 |3 ||
|3002 | 3001 | 4825 | 3 ||||
|4002| |1 |9 |0 |
|4002|  1001 | 3794|  2 ||||
|4002 |2001 |6454 |3 |
|4002|  3001|  8200|  5 ||||
|4002 |4001 |8541 |4 |
|. | . | . | . ||||
|. |. |. |. |
|. | . | . | . ||||
|29002 |19001 |398294 |23 |
|29002 | 20001|  405836 | 39 ||||
|29002 |21001 |415931 |26 |
|29002 | 22001 | 421256 | 42 ||||
|29002 |23001 |427920 |44 |
|29002 | 24001 | 433532 | 46 ||||
|29002 |25001 |443397 |49 |
|29002 | 26001|  448448 | 51 ||||
|29002 |27001 |448586 |52 |
|29002 | 28001|  447265 | 54 ||||
|29002 |29001 |448993 |35 |

![Aspose Words b287eb9e-737a-471b-bc47-d3af436b5d89 026](https://github.com/NightMare489/Algorithms-Comparison/assets/56297925/42da0123-aa4b-4ec4-a55b-1c12ae0c13c8)

 ![Aspose Words b287eb9e-737a-471b-bc47-d3af436b5d89 025](https://github.com/NightMare489/Algorithms-Comparison/assets/56297925/051e4fa2-4fea-43e7-b423-57cb748e709b)


<a name="_page6_x29.00_y32.00"></a>**Discussion** 

The measured runtimes generally align with the theoretical complexities. However, several factors contribute to the deviations observed:

**Implementation Details**: Optimizations in the code, such as efficient pivot selection in Quick Sort, can significantly affect performance. 

**Input Data Characteristics**: Random input data can sometimes result in best-case or worst-case scenarios, particularly for Quick Sort and Boyer-Moore. 

**System Overheads**: Real-world factors such as CPU cache, memory access patterns, and operating system scheduling can influence timing measurements.

<a name="_page6_x29.00_y225.00"></a>**Conclusion** 

The benchmarks confirmed the theoretical expectations of algorithm performance, demonstrating the importance  of  considering  both  average  and  worst-case  complexities.  While  theoretical  analysis provides a guideline, actual performance can vary due to multiple factors. These insights are crucial for selecting appropriate algorithms based on specific application needs.
