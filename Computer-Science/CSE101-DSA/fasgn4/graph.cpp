#include "graph.h"

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstring>

using namespace std;

void Graph::addMovie(string movieListLine)
{
    char *mLLcstring = strdup(movieListLine.c_str()); // Converst input into cstring
    char *tok;                                        // Char ptr to store tokens over iterations
    bool isMov = true;                                // bool helps separate movies from actors
    Movie *newMov;                                    // New movie object
    tok = strtok(mLLcstring, " ");
    while (tok != NULL) // Iterate until there are no more movies/actors to tokenize from input cstring
    {
        string movAct(tok); // Convert token (which can be movie or actor) into string
        if (isMov)          // If isMov is true, tok is the first token of the input line (tok is a movie)
        {
            newMov = new Movie(movAct);
            isMov = false;
        }
        else // All tokens after the first are actors
        {
            if (actorMap.count(movAct) == 0) // If the actor isn't in the graph yet
            {
                actorMap[movAct] = new Actor(movAct); // Make a new actor object stored in Graph's actorMap
            }
            newMov->actorList.push_back(movAct);           // Push movie to actor's movieListLine
            actorMap[movAct]->movieList.push_back(newMov); // Push movie to actor's movieList
        }
        tok = strtok(NULL, " ");
    }
}

bool Graph::solve(string actor1, string actor2) // returns true if actor1 reaches actor2, false o.w.
{
    if (actorMap.count(actor1) > 0 && actor1 == actor2) // Catches if actors are the same, might not need
    {
        return true;
    }
    queue<string> actorQ;
    pair<string, string> visitPair("", ""); // adds pair of <prevActor, movie> into visitMap
    actorQ.push(actor1);
    visitMap[actor1] = visitPair; // Mark first actor as visited
    while (!actorQ.empty())
    {
        string prevActor = actorQ.front(); // Dequeue the queue of actor names
        actorQ.pop();
        // Now we search through prevActor's neighborhood: conntected movies -> connected actors
        for (const auto &movie : actorMap[prevActor]->movieList) // loop over each movie connected to prevActor
        {
            for (const auto &nextActor : movie->actorList) // loop over each actor connected to movie, which is connected to prevActor
            {
                if (visitMap.count(nextActor) == 0) // if nextActor isn't a visited actor
                {
                    actorQ.push(nextActor);          // Push nextActor to Queue to explore its neighborhood later
                    visitPair.first = prevActor;     // update nextActor's previous actor
                    visitPair.second = movie->name;  // update nextActor's movie associated with prevActor
                    visitMap[nextActor] = visitPair; // Mark nextActor as visited
                    if (nextActor == actor2)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

string Graph::reconstructPath(string actor1, string actor2)
{
    if (actorMap.count(actor1) == 0 || actorMap.count(actor2) == 0 || solve(actor1, actor2) == false) // solve evaluated to false
    {
        return "Not present";
    }
    if (actor1 == actor2) // actor1 and actor2 are the same person
    {
        return actor1;
    }
    string outstring;
    pair<string, string> currActor = visitMap[actor2];
    outstring += actor2;
    while ((currActor.first).length() > 0) // while currActor still has a preceding actor in path
    {
        outstring = currActor.first + " -(" + currActor.second + ")- " + outstring;
        currActor = visitMap[currActor.first]; // Reassign currActor to its prev actor for next iteration (approaches actor1)
    }
    unordered_map<string, pair<string, string>> newVisitMap;
    visitMap = newVisitMap; // Refreshes visitmap for next path query
    return outstring;
}
