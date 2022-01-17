bool cycle_DFS(src)
{
    Node u                                                // u will be Node variables
        visited[number of v] = {false, false, ..., false} // Array for tracking visited nodes
                               stack<Node>
                                   nodeStack // Stack for holding nodes to explore in DFS
                                       nodeStack.push(src)
                                           visited[src] = true src.parent = NULL while (!nodeStack.empty())
    {
        u = nodeStack.pop() for (edge(u, v) in Neighborhood(u))
        {
            if (visited[v] == false) // If we run into an unvisited node
            {
                visited[v] = true         // mark node as visited
                             v.parent = u // assign new parent to v
                                            nodeStack.push(v)
            }
            else if (visited[v] == true && u != v.parent) // If we find a visited node that's not our parent
            {
                return true // we found the cycle
            }
        }
    }
    return false // Finished travelling graph without a cycle
}