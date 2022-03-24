# Project on Currency 
### Team 4
- Prerak Srivastava 
- Shubh Karman Singh Bhullar
- Knv Karthikeya
- Rohan Madinei
## TA assigned : Dhruv Sharma

## Compiling and Running
- Clone this repository on your machine
- Compile the program: `gcc main2.c`
- For a terminal experience: `./a.out`
- For an automated experience using the input program: `./a.out < Input.txt`

### Manual Input 
**Although this steps aren't required but the make your terminal look clean.**
1. Uncomment the lines 294,295,296,353,354,355,438,439,440,467,468,469,500,501,502,506,507,508,547,548,549 in `currency2.c`.
2. Uncomment the lines 22,23,24,27,28,29 and 164,165,166 in `main2.c`.
3. Comment the line 366 in `currency2.c`.
4. You can run our program by running `gcc main2.c` followed by `./a.out` in your terminal.


### Input through a program
**Although this steps aren't required but the make your terminal look clean.**
1. Comment the lines 294,295,296,353,354,355,438,439,440,467,468,469,500,501,502,506,507,508,547,548,549 in `currency2.c`.
2. Comment the lines 22,23,24,27,28,29 and 164,165,166  in `main2.c`.
3. Uncomment the line 366 in `currency2.c`.
4. To run the input program
    ```
    gcc inputprogram.c
    ./a.out > Input2.c
    ```
5. The method to enter the input in `inputprogram.c` is as follows:    
    1. Enter the total number of banks (bankno).
    2. For the next bankno lines the ith line contains 2 integers 1st one represents the number of curriences in the ith bank and 2nd one represents the density index of the graph  

```
Density of graph 1 > density of graph 2 if density index 1 < density index 2 
```
6. The input should look something like this
```cpp
6 
4 1
5 2 
6 8 
9 10
12 15
20 30
```
7. Then you cna run our program by running `gcc main2.c` followed by `./a.out < Input2.txt > output.txt`.
8. The output of the program will be present in `output.txt`

## Objective
To develop and design a currency exchange monitor with the following features:
1. Add or delete a trade bank.
2. Add or delete a currency.
3. Add or delete a currency conversion between two currencies.
4. Figure out the best possible path to convert the given two currencies.

## Approach

We have heavily relied on data structures like graphs as it was easier to store the required data and develop the necessary algorithms to work on this data. 

1. Create an array of all the trade-banks given by the user.
2. Each Trade-bank will have it's individual graph.
3. Each node in the graph here behaves like a node containing the currency name and it's respective weight.
4. The following graph can be represented in the form of a adjacency matrix or a list.
5. Each currency is linked to the other on the basis of the input given by the user.
6. Application of various algorithms like DFS,BFS,Dijkstra etc depending on which gives us the best case scenario in finding out the best path to convert a given currency A to a given currency B.
7. Example : If all the weights of the graph are equal it is better to use BFS rather than Dijkstra as it gives us a faster result as 
``` 
Time complexity of BFS is O(V + E) as Dijkstras is O(V + E(log(V))) 
```


