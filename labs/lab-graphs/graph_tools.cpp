/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
   Vertex start = graph.getStartingVertex();
   std::queue<Vertex> Q;
   graph.setVertexLabel(start, "VISITED");
   Q.push(start);
   vector<Vertex> startAdj = graph.getAdjacent(start);
   int minW = graph.getEdgeWeight(start, startAdj[0]);
   Vertex min_start = start;
   Vertex min_end = startAdj[0];

   vector<Edge> E = graph.getEdges();
   for (size_t j = 0; j < E.size(); j++)
	graph.setEdgeLabel(E[j].source, E[j].dest, "UNEXPLORED");

   vector<Vertex> V = graph.getVertices();
   for (size_t j = 0; j < V.size(); j++)
	graph.setVertexLabel(V[j], "UNEXPLORED");


   while (!Q.empty()){
	Vertex v = Q.front();
	Q.pop();
        vector<Vertex> adj_V = graph.getAdjacent(v);
	if (!adj_V.empty()){
	 for (size_t a = 0; a < adj_V.size(); a++){
	    if (graph.getVertexLabel(adj_V[a]) == "UNEXPLORED"){
		graph.setEdgeLabel(v, adj_V[a], "DISCOVERY");
		graph.setVertexLabel(adj_V[a], "VISITED");
		Q.push(adj_V[a]);
	    }
	    else if (graph.getEdgeLabel(v, adj_V[a]) == "UNEXPLORED")
		graph.setEdgeLabel(v, adj_V[a], "CROSS");
	    if (graph.getEdgeWeight(v, adj_V[a]) < minW){
		minW = graph.getEdgeWeight(v, adj_V[a]);
		min_start = v;
		min_end = adj_V[a];
	    }
	 }
	}
   }

   for (size_t j = 0; j < E.size(); j++)
	graph.setEdgeLabel(E[j].source, E[j].dest, "UNEXPLORED");

   for (size_t j = 0; j < V.size(); j++)
	graph.setVertexLabel(V[j], "UNEXPLORED");

   graph.setEdgeLabel(min_start, min_end, "MIN");

return minW;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE

   std::queue<Vertex> Q;
   graph.setVertexLabel(start, "VISITED");
   Q.push(start);
   std::unordered_map<Vertex, Vertex> myMap;

   vector<Edge> E = graph.getEdges();
   for (size_t j = 0; j < E.size(); j++)
	graph.setEdgeLabel(E[j].source, E[j].dest, "UNEXPLORED");

   vector<Vertex> V = graph.getVertices();
   for (size_t j = 0; j < V.size(); j++)
	graph.setVertexLabel(V[j], "UNEXPLORED");


   while (!Q.empty()){
	Vertex v = Q.front();
	Q.pop();
        vector<Vertex> adj_V = graph.getAdjacent(v);
	if (!adj_V.empty()){
	 for (size_t a = 0; a < adj_V.size(); a++){
	    if (graph.getVertexLabel(adj_V[a]) == "UNEXPLORED"){
		graph.setEdgeLabel(v, adj_V[a], "DISCOVERY");
		graph.setVertexLabel(adj_V[a], "VISITED");
		Q.push(adj_V[a]);
		myMap[adj_V[a]] = v;
	    }
	    else if (graph.getEdgeLabel(v, adj_V[a]) == "UNEXPLORED")
		graph.setEdgeLabel(v, adj_V[a], "CROSS");
	 }
	}
   }

   int c = 0;
   Vertex e = end;
   while (start != e){
	graph.setEdgeLabel(e, myMap[e], "MINPATH");
	e = myMap[e];
	c += 1;
   } 

 return c;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> V = graph.getVertices();
    vector<Edge> E = graph.getEdges();

    int n = V.size();
    int numE = E.size();

    //Create a disjoint set for each vertex in the graph
    DisjointSets vertexSet;
    vertexSet.addelements(n);

    //Sort the edges in increasing order
    std::sort(E.begin(), E.end());

    std::unordered_map<Vertex, int> myMap;
    for (size_t a = 0; a < V.size(); a++)
	myMap[V[a]] = a;

    int MST_edges = 0;
    //For each edge, starting from the least weight edge:
    for (int x = 0; x < numE && MST_edges < n-1; x++){
	Vertex A = E[x].source;
	Vertex B = E[x].dest;

	//If the edge connects two vertices in different sets: then ADD the
	//edge to the MST, and union the vertices' sets together.
	if (vertexSet.find(myMap[A]) != vertexSet.find(myMap[B])){
	    graph.setEdgeLabel(A, B, "MST");
	    vertexSet.setunion(myMap[A], myMap[B]);
	    MST_edges++;
	}
        //Otherwise, discard edge.
	//Repeat until all vertices are connected (are in one big set) or,
	//equivalently, we have n-1 edges in the MST, where n is the num vert
    }

}



