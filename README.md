# Trade Bank Management System (TBMS)

### Team Members

- Prerak Srivastava
- Shubh Karman Singh Bhullar
- Knv Karthikeya

## Compiling and Running

```
$ gcc main.c src/bank.c src/currency.c src/graph.c -o main
$ ./main
```

### Automated Input

To run the input program

```
$ gcc inputprogram.c -o input
$ ./input > input.txt
```

The method to enter the input in `inputprogram.c` is as follows:

1. Enter the total number of banks (bankno).
2. For the next bankno lines the ith line contains 2 integers 1st one represents the number of curriences in the ith bank and 2nd one represents the density index of the graph

```
Density of graph 1 > density of graph 2 if density index 1 < density index 2 
```

The input should look something like this

```cpp
6 
4 1
5 2 
6 8 
9 10
12 15
20 30
```

Then you can run our program by compiling the program using the command given in the previous section followed by `./main < input.txt > output.txt`.

The output of the program will be present in `output.txt`

## Objective

To develop and design a currency exchange monitor with the following features:

1. Add or delete a trade bank.
2. Add or delete a currency in a specified trade bank.
3. Add or delete a currency conversion between two currencies.
4. Figure out the best possible path to convert the given two currencies.

## Approach

We have used data structures like graphs as it was easier to store the required data and develop the necessary algorithms to work on this data.

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
# java-tbms
