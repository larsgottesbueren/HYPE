# HYPE
Hypergraph partitioner based on the idea of neighborhood expansion that processes very large hypergraphs (with up to billions of vertices) using only a single thread. The source code is written in C++.

## How to build 
To use, simply install via the corresponding script "build.sh". Makefile is contained. Runs with cmake.

We use the boost library. Should be installed automatically with the build file. If not, please install boost manually: https://www.boost.org/

## How to Use
To start the partitioner, follow the commands provided in the main file. The following arguments can be set:

"help,h" -- display help message

"thesis,t" -- if set, output is formatted in csv to make it easier to plot directly. If not set, the output is more verbose.

"input,i" -- input hypergraph file

"format,f" -- specify the input format of the hypergraph file

"partitions,p" -- number of partitions

"sset-size,s" -- maximum size of the secondary set (called 'fringe' in the paper); in paper, this is set to 10

"percent-of-edges-ignored,e" -- how many percent of the biggest hyperedges will be removed; experimental, set to 0 to reproduce results from paper

"neigs-calc-method,n" -- Switch to choose between exact and cached calculation of number of neigbours of a vertex in the hypergraph
