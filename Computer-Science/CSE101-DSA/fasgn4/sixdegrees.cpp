#include "graph.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        throw std::invalid_argument("Usage: ./sixdegrees <INPUT FILE> <OUTPUT FILE>"); // throws error, inspired by prof Sesh's ex codes
    }

    ifstream movieList;
    ifstream input;
    ofstream output;

    movieList.open("movielists/cleaned_movielist.txt"); // Reads in movielist to for populating graph
    input.open(argv[1]);
    output.open(argv[2]);

    Graph myGraph;
    string movieListLine;                     // line read from input, which populates graph
    while (getline(movieList, movieListLine)) // Populates graph 1 movie at a time
    {
        // movieListLine.pop_back();
        myGraph.addMovie(movieListLine);
    }

    string query;
    while (getline(input, query)) // While loop iterates queries
    {
        query.pop_back(); // Required for windows, weird invisible string, not a problem in codio or linuxbox
        vector<string> actorVec; // Vector will hold query actors
        string tmpActor, actor1, actor2;
        stringstream ssQuery(query);

        while (getline(ssQuery, tmpActor, ' '))
        {
            actorVec.push_back(tmpActor);
        }
        actor1 = actorVec[0];
        actor2 = actorVec[1];
        output << myGraph.reconstructPath(actor1, actor2) << endl;
    }
    movieList.close();
    input.close();
    output.close();
}