# -PEA-TSP-Algorithms-1
University project solving the traveling salesman problem with exact algorithms: Branch &amp; Bound, Dynamic Programming and Brute Force.
## Description
The program can solve Traveling Salesman problem with three exact algorithms:
- Branch &amp; Bound,
- Dynamic Programming
- Brute Force  

It returns the optimum path and it's length. The starting node/city is always 0.
## Usage
To test the program user can either generate a random graph or load one from .txt file.
### Txt file format
To load a graph from a file, the file has to be in a specific format. The first number is the size of a matrix and next numbers are weight/length of path from city x to city y. For example:  
4  
0 4 2 1  
3 0 1 2  
7 9 0 1  
2 5 3 0  
In this case length of path from city 0 to city 2 is 2 and the size of matrix is 4. Number of empty spaces and new lines does not matter.

