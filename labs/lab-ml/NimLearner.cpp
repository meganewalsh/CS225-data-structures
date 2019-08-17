/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>
#include <unordered_map>
using namespace std;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */

    for (int X = startingTokens; X >= 0 ; X--){

	for (int p = 1; p <= 2; p++){

	    int opp_p = 0;
	    if (p == 1)
		opp_p = 2;
	    else
		opp_p = 1;

	    Vertex curr = "p" + to_string(p) + "-" + to_string(X);
	    g_.insertVertexByLabel(curr);

	    if (X == 0)
		continue;

	    Vertex v_1 = "p" + to_string(opp_p) + "-" + to_string(X - 1);
	    g_.insertEdge(curr, v_1);
	    g_.setEdgeWeight(curr, v_1, 0);
	
	    if (X != 1){
	    	Vertex v_2 = "p" + to_string(opp_p) + "-" + to_string(X - 2);
		g_.insertEdge(curr, v_2);
	    	g_.setEdgeWeight(curr, v_2, 0);
	    }

	}
    }

}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */

    int startingTokens = (g_.getVertices().size() - 2) / 2;
    int p = 1;
    Vertex curr = g_.getVertexByLabel("p" + to_string(p) + "-" + to_string(startingTokens));

    int X = startingTokens;
    while (X > 0) {

        int opp_p = 0;
	if (p == 1)
	    opp_p = 2;
	else
	    opp_p = 1;

    	int choice;
	if (X == 1)
	    choice = 1;
	else
	    choice = ( rand() % 2 ) + 1;

    	Vertex V = g_.getVertexByLabel("p" + to_string(opp_p) + "-" + to_string(X - choice));
    	Edge e = g_.getEdge(curr, V);
    	path.push_back(e);

	X = X - choice;
	curr = V;
	p = opp_p;
    }

  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */

    Vertex full_loser = g_.getVertexByLabel((path[path.size() - 1]).dest);
    string loser = full_loser.substr(0,2); 

    for (size_t i = 0; i < path.size(); i++){

	Edge e = path[i];
	int curr_weight = e.getWeight();

	if ((g_.getVertexLabel(e.dest)).substr(0,2) == loser)
	    g_.setEdgeWeight(e.source, e.dest, curr_weight + 1);
	else
	    g_.setEdgeWeight(e.source, e.dest, curr_weight - 1);

   }

}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
