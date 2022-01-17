#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstring>

using namespace std;

class Movie // Movie class acts as a connection between Actor class objects
{
public:
    string name;              // Name of movie
    vector<string> actorList; // used to search through actorMap in Graph
    Movie(string mName)
    {
        name = mName;
    }
};

class Actor // Actor class creates objects that are like nodes in a graph
{
public:
    string actor;              // actor name/key
    vector<Movie *> movieList; // Each actor holds a list of Movies which behave like edges

    Actor(string aName) // used when actor isn't in graph yet
    {
        actor = aName;
    }
};

class Graph // Graph class creates a network of actors connected by movies
{
public:
    unordered_map<string, pair<string, string>> visitMap; // Use this to track prevs and visited status
    unordered_map<string, Actor *> actorMap;              // Map which holds all Actors in the graph
    void addMovie(string movie);                          // Method for adding movie and associated actors into graph network
    bool solve(string actor1, string actor2);             // Finds path between actor1 and actor2 in the graph, leaves trail in visitMap
    string reconstructPath(string actor1, string actor2); // relies on solve, backtracks to actor2 if its present through visitMap
};

#endif