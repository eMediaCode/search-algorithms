# search-algorithms

## Algorithms
```
1. Depth-First Search (DFS)
2. Breadth-First Search (BFS)
3. Uniform Cost Search (UCS)
4. A* Tree Search
5. A* Graph Search
```

## Graphs
#### Graph 1
<img src="http://i.imgur.com/PPDPSSL.png" width="150"/>

#### Graph 2
<img src="http://i.imgur.com/nax1gCt.png" width="150"/>

#### Graph 3
<img src="http://i.imgur.com/ReX3Eow.png" width="150"/>

#### Graph 4
<img src="http://i.imgur.com/48qP96j.png" width="400"/>

#### Graph 5
<img src="http://i.imgur.com/9o38T1a.png" width="400"/>

## Running the Program
#### Terminal (Mac)
```
1. Type "make Graph"
2. Type "./Graph"
```
## Output
```
-------------- GRAPH 1 --------------

S node : 0
A node : 1
B node : 2
C node : 3
G node : 4

Depth-First Search: 0 1 2 3 4
Breadth-First Search: 0 1 2 4 


-------------- GRAPH 2 --------------

S node : 0
A node : 1
B node : 2
C node : 3
G node : 4

Depth-First Search: 0 2 1 4
Breadth-First Search: 0 2 3 1 4 


-------------- GRAPH 3 --------------

S node : 0
A node : 3
B node : 1
C node : 2
G node : 4

Depth-First Search: 0 1 3 4
Breadth-First Search: 0 1 2 3 4 


-------------- GRAPH 4 --------------

S node : 0
A node : 1
B node : 2
C node : 3
D node : 4
E node : 5
F node : 6
G1 node : 7
G2 node : 8

Depth-First Search: 0 1 4 3 7 8
Breadth-First Search: 0 1 2 4 5 3 7 
Uniform Cost Search: 0 1 4 8
A* Tree Search: 0 1 4 8
A* Graph Search: 0 1 4 8


-------------- GRAPH 5 --------------

Start node : 0
A node : 1
B node : 2
C node : 3
D node : 4
Goal node : 5

Depth-First Search: 0 1 2 4 5
Breadth-First Search: 0 1 2 3 4 5 
Uniform Cost Search: 0 1 4 5
A* Tree Search: 0 1 4 5
A* Graph Search: 0 1 4 5


---------------- END ----------------
```
