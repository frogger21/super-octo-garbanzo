# super-octo-garbanzo
Karger random contraction algorithm in C++ with lists and structs

Takes a textfile and parses it into the adjacency lists.
Numbers are seperated by non-number ascii 
e.g. "1xxx24   25...27>>> 30" will correctly be read as 1, 24, 25, 30 etc.
First column is the node and the rest of the columns on the same row represent other nodes.
So 1, 24, 25, 30 ... would mean [1, 24], [1, 25], [1, 30] and so on (the edges).

It will run as many trials of the Karger random contraction algorithm you specify 
and tell you the smallest minimum cut it got from the Karger algorithm.

You must specify the filepath and filename of the text file that has the matrix in the source code.
You must also specify within the source code the number of trials you wish to do.

img source: wikipedia
![alt text](https://github.com/frogger21/super-octo-garbanzo/blob/master/karger.PNG)

Karger algorithm will find the minimum cut via a randomimized process.
