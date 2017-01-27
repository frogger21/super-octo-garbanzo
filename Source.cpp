#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct Edge
{
	int src, dest; //src -> dest for graph theory
};

struct Graph
{
	int Nvertices, Medges; //# of vertices and edges
	list<Edge> Edges; //undirected so A->B is same as B->A
};

bool aNumber(char *a)
{
	int temp = static_cast<int>(*a);
	if (temp <= 57 && temp >= 48)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool check(Graph &X, Edge &Y)
{
	//checks if a -> b already exists as b -> a
	list<Edge>::iterator i;
	for (i = X.Edges.begin(); i != X.Edges.end(); ++i)
	{
		if (Y.src == i->dest && Y.dest == i->src)
		{
			return true; //we have a match
		}
	}
	return false;
}

void split(string line, Graph &X)
{
	string::size_type sz;
	Edge TempEdge;
	int NumCount = 0;
	int startPos, numLen, tracker, StringSize;
	int theNumber;
	int firstVirtex;
	StringSize = line.size();
	bool Num = false;
	bool temp = false;
	for (int i = 0; i < StringSize; i++)
	{
		//is it a number?
		temp = aNumber(&line[i]);
		//if it's not a number then 
		if (temp == false)
		{
			Num = false;
		}
		//previous char was not a number but current is: we got a new number
		if (Num == false && temp == true)
		{
			Num = true;
			startPos = i;
			numLen = 1; //we don't know yet fully
			tracker = i + 1;
			while (tracker < StringSize)
			{
				if (aNumber(&line[tracker]) == true)
				{
					numLen += 1;
					tracker++;
				}
				else
				{
					break;
				}
			}
			string test2 = line.substr(startPos, numLen);
			theNumber = stoi(test2, &sz); //convert string to integer
			NumCount += 1;

			if (NumCount == 1)
			{
				firstVirtex = theNumber;
				X.Nvertices += 1;
			}
			else
			{
				TempEdge.src = firstVirtex;
				TempEdge.dest = theNumber;
				if (check(X, TempEdge) == false)
				{
					//we've never seen this before so add it.
					X.Edges.push_back(TempEdge);
					X.Medges += 1;
				}
			}
			//std::cout << theNumber << endl;
		}
	}
}

void printGraph(Graph &X)
{
	list<Edge>::iterator i;
	for (i = X.Edges.begin(); i != X.Edges.end(); ++i)
	{
		std::cout << "[" << i->src << "," << i->dest << "]" << endl;
	}
}

int kargerContract(Graph &X)
{
	list<Edge>::iterator i1;
	int edgeMax, luckyNumber;
	int a, b;
	int a2, b2;
	int mincut;
	bool A, B;
	A = false; //initialize
	B = false; //initialize

	while (X.Nvertices > 2)
	{
		//pick random edge
		edgeMax = X.Medges; 
		
		luckyNumber = rand() % edgeMax + 1; // between 1 and edgeMax
		i1 = X.Edges.begin();
		advance(i1, luckyNumber - 1); //remember in c++ things start with 0
		a = i1->src; //our A for A->B (it's an integer)
		b = i1->dest; //our B for A-B  (ditto above)
		i1 = X.Edges.erase(i1); //delete this 
		X.Medges -= 1; //we lost one edge
		X.Nvertices -= 1; //we merged 2 into 1
		//now we merge A and B to just A and delete self loops [A,A]
			//cout << "A: " << a << ", B: " << b << endl;
		for (i1 = X.Edges.begin(); i1 != X.Edges.end(); )
		{
			//A i1->src; 
			//B i1->dest;
			a2 = i1->src;
			b2 = i1->dest;
			
			if (a2 == b)
			{
				//if source is either A or B, replace it with A
				i1->src = a;
			}
			if ( b2 == b)
			{
				//if destination is either A or B replace it with A
				i1->dest = a;
			}
			//if both are A, then delete it because it's a self loop
			a2 = i1->src;
			b2 = i1->dest;
			if (a2 == a && b2 == a)
			{
				i1 = X.Edges.erase(i1);
				X.Medges -= 1; //we lost an edge
			}
			else
			{
				++i1;
			}
		}
			//printGraph(X);
	}
	mincut = X.Medges;
	return(mincut);
}

void copyGraph(Graph &Original,Graph &Copyee)
{
	list<Edge>::iterator i1; //original
	Edge temp;
	//list<Edge>::iterator i2; //copyee
	//i2 = Copyee.Edges.begin();
	for (i1 = Original.Edges.begin(); i1 != Original.Edges.end(); ++i1)
	{
		temp.dest = i1->dest;
		temp.src = i1->src;
		Copyee.Edges.push_back(temp);
	}
	Copyee.Edges = Original.Edges;
	Copyee.Medges = Original.Medges;
	Copyee.Nvertices = Original.Nvertices;
}

int main()
{
	srand(time(NULL)); //random seed by time
	bool First = true;
	Graph Y;
	std::cout << "Running...\n";
	int min = 100000; //arbitrary high
	int maxN = 13; //number of trials
	for (int z = 0; z < maxN; z++)
	{
		int tempMin;
		int nVertices = 0; //not sure yet...
		int mEdges = 0; //not sure yet...
		Graph X;
		X.Nvertices = nVertices;
		X.Medges = mEdges;
		//Open File
		if (First == true)
		{
			string line, fileNom;
			fileNom = "D:/kargerMinCut.txt"; //filepath and filename to parse.
			ifstream myfile(fileNom);
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					split(line, X);
				}
				myfile.close();
			}
			First = false;
			copyGraph(X, Y); //Y holds original
			//cout << "Was here!\n";
		}
		else
		{
			copyGraph(Y, X); //X will copy from Y
			//cout << "Not here!\n";
			
		}
		//printGraph(X);
		tempMin = kargerContract(X);
		std::cout << (z + 1) << " -> The number of mincut: " << tempMin;
		if (tempMin < min)
		{
			min = tempMin;
		}
		std::cout << " (Global min thus: " << min << ")" << endl;
	}
	std::cout << "After many tries (" << maxN << " tries) the mincut I found was: " << min << endl;
	std::cout << "Thanks!\n";

	//pause 
	int userInput;
	std::cout << "\nExiting...\n";
	std::cin >> userInput;
	return 0;
}
