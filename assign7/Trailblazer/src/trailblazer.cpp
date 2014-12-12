// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
#include "set.h"
#include "map.h"
using namespace std;

bool DFS(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);
void retracePath(Vertex* curr, Vector<Vertex*>& path);
Vector<Vertex*> genericDijkstra(BasicGraph& graph, Vertex* start, Vertex* end, double (newPriority)(Vertex*, Vertex*, double));
double newDijkstraPriority(Vertex* start, Vertex* end, double cost);
double newAStarPriority(Vertex* start, Vertex* end, double cost);
bool inSameSet(Vertex* start, Vertex* end, Vector<Set<Vertex*> >& vertexSets);
void mergeSets(Vertex* start, Vertex* end, Vector<Set<Vertex*> >& vertexSets);
Vertex* parent(Vertex* curr);

/**
 * @brief depthFirstSearch
 * Wrapper function for recursive DFS on given graph. Returns the found (or not) path
 * as a Vector of vertex pointers.
 * @param graph - Provided graph on which to search
 * @param start - Start vertex of path
 * @param end - End vertex of path
 * @return - The found path as a Vector of vertex pointers
 */
Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData(); // reset before each search
    Vector<Vertex*> path;
    DFS(graph, start, end, path); // search
    return path;
}

/**
 * @brief DFS
 * Recursive depth first search on given graph. For each vertex it visits, DFS marks 
 * it, searches its neighbors, and removes marking if vertex proved unfruitful. DFS
 * goes deep; it goes down one particular path as far as possible before backtracking.
 * @param graph - Provided graph on which to search
 * @param curr - Current vertex
 * @param end - Desired end vertex of the path
 * @param path - The found path as a Vector of vertex pointers
 * @return 
 */
bool DFS(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path) {    
    // add curr vertex
    curr->visited = true;
    curr->setColor(GREEN);
    path.add(curr);
    
    // base case
    if (curr == end) return true;
    
    // for each univisited neighbor
    for (Edge* edge : curr->edges) {
        Vertex* neighbor = edge->finish; // extract neighbor
        if (neighbor->visited) continue; // skip if already visited
        if (DFS(graph, neighbor, end, path)) return true; // make choice
        // otherwise unmake choice (nothing to do)
    }
    
    // (partially) undo curr vertex choice
    curr->setColor(GRAY);
    path.remove(path.size() - 1);
    return false;
}

/**
 * @brief breadthFirstSearch
 * Breadth first search for a given graph. Goes through graph's current generation
 * of neighbors (all the same distance away) and enqueues the next generation for
 * future processing. Guaranteed to find the shortest path (assuming all paths are equal
 * in cost). Goes wide across all possible neighbors.
 * @param graph - Provided graph on which to search
 * @param start - Start vertex of path
 * @param end - Desired end vertex of path
 * @return - The found path as a Vector of vertex pointers
 */
Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData(); // reset before each search
    Vector<Vertex*> path;
    Queue<Vertex*> frontier;
    
    // first vertex
    start->visited = true;
    start->setColor(YELLOW);
    frontier.enqueue(start);
    
    // search
    while(!frontier.isEmpty()) {
        Vertex* curr = frontier.dequeue(); // dequeue current generation
        curr->setColor(GREEN);
        
        for (Edge* edge : curr->edges) { // next generation neighbors
            Vertex* neighbor = edge->finish; // extract neighbor
            if (neighbor->visited) continue; // skip if already visited
            
            frontier.enqueue(neighbor); // enqueue
            neighbor->previous = curr;
            neighbor->visited = true;
            neighbor->setColor(YELLOW);
            
            if (neighbor == end) { // path found
                neighbor->setColor(GREEN);
                retracePath(neighbor, path);
                return path;
            }
        }
    }
    
    return path;
}

/**
 * @brief retracePath
 * Recursively retraces found path given the end index of the path.
 * @param curr - End index of the found path
 * @param path - Vector to fill with vertexes on found path 
 */
void retracePath(Vertex* curr, Vector<Vertex*>& path) {
    if (curr == NULL) return;
    retracePath(curr->previous, path);
    path.add(curr);
}

Vector<Vertex*> genericDijkstra(BasicGraph& graph, Vertex* start, Vertex* end, double (newPriority)(Vertex*, Vertex*, double)) {
    // ================== SETUP ===================
    Vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    
    graph.resetData(); // reset before each search
    
    // set cost of all vertices to be infinity
    Set<Vertex*> allVertices = graph.getVertexSet();
    for (Vertex* vertex : allVertices) {
        vertex->cost = POSITIVE_INFINITY;
    }
    
    // set start node to have cost 0 and enqueue
    start->cost = 0;
    pqueue.enqueue(start, newPriority(start, end, 0));
    
    // ================== SEARCH ==================
    while (!pqueue.isEmpty()) {
        Vertex* curr = pqueue.dequeue(); // dequeue highest priority node
        curr->visited = true;
        curr->setColor(GREEN);
        
        if (curr == end) { // done searching
            retracePath(curr, path);
            return path;
        }
        
    // ================== RELAX ===================
        for (Edge* edge : curr->edges) { // neighbors
            Vertex* neighbor = edge->finish; // extract neighbor
            if (neighbor->visited) continue;
            double cost = curr->cost + edge->cost; // calculate cost
            if (cost < neighbor->cost) { // update if new cost/path is better
                neighbor->cost = cost;
                neighbor->previous = curr;
                if (neighbor->getColor() == YELLOW) { // already in pqueue but not yet processed
                    pqueue.changePriority(neighbor, newPriority(neighbor, end, cost));
                } else {
                    pqueue.enqueue(neighbor, newPriority(neighbor, end, cost));
                }
                neighbor->setColor(YELLOW);
            }
        }
    }
    
    return path;
}

/**
 * @brief dijkstrasAlgorithm
 * Uses Dijkstra's algorithm to search a given graph. [FINISH MEEEEEEEEEEEEEE---------]
 * @param graph - Provided graph on which to search
 * @param start - Start vertex of path
 * @param end - Desired end vertex of path
 * @return - The found path as a Vector of vertex pointers
 */
Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return genericDijkstra(graph, start, end, newDijkstraPriority);
}

double newDijkstraPriority(Vertex* start, Vertex* end, double cost) {
    return cost;
}

/**
 * @brief aStar
 * Uses A* algorithm to search a given graph. Similar to Dijkstra's, but uses a heuristic
 * function when calculating the new priority of a node so that it can direct its search
 * more towards the end (vs. searching in all directions in concentric-ish circle as with
 * Dijkstra's). Calls generic Dijkstra function with different priority calculating callback
 * function.
 * @param graph - Provided graph on which to search
 * @param start - Start vertex of path
 * @param end - Desired end vertex of path
 * @return - The found path as a Vector of vertex pointers
 */
Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return genericDijkstra(graph, start, end, newAStarPriority);
}

/**
 * @brief newAStarPriority
 * Callback function for calculating new node priorities during A* search. Combines actual cost
 * (of previous node's cost + cost of new edge) and a heuristic function that calculates the 
 * straight distance from the current (start) node to the end of the desired path. Added heuristic
 * makes sure that the algorithm fist explores paths closer towards the end point.
 * @param start - Current vertex being assigned a priority
 * @param end - Desired end vertex of path
 * @param cost - Previous vertex's cost + cost of new edge to current vertex
 * @return 
 */
double newAStarPriority(Vertex* start, Vertex* end, double cost) {
    return cost + heuristicFunction(start, end);
}

/**
 * @brief kruskal
 * Uses Kruskal's algorithm to generate minimum spanning tree for a given weighted graph.
 * Examines each edge starting from the least weighted one. If the edge joins vertices that
 * haven't already been connected by the MST, then adds edge to the MST and joins the vertices'
 * clusters (other vertices it is connected to by the existing MST). If the edge joins vertices
 * that are already connected, the algorithm ignores those edges. Continues until no more edges
 * left to examine.
 * @param graph - Provided graph from which to create a MST
 * @return - Set of edges to be included in the MST
 */
Set<Edge*> kruskal(BasicGraph& graph) {
    // ================== SETUP ===================
    Set<Edge*> mst;
    Set<Edge*> allEdges = graph.getEdgeSet();
    Set<Vertex*> allVertices = graph.getVertexSet();
    
    PriorityQueue<Edge*> pq; // put edges and weights in a priority queue
    for (Edge* edge : allEdges) { 
        pq.enqueue(edge, edge->cost);
    }
    
   Vector<Set<Vertex*> > vertexSets; // put all vertices into their own cluster
    for (Vertex* vertex : allVertices) {
        Set<Vertex*> newEmptySet;
        newEmptySet.add(vertex);
        vertexSets.add(newEmptySet);
    }
    
    // ================ MAKE TREE =================
    while (!pq.isEmpty()) {
        Edge* edge = pq.dequeue();
        // if vertices aren't in the same cluster, add to MST and merge their clusters
        if (!inSameSet(edge->start, edge->finish, vertexSets)) {
            mst.add(edge);
            mergeSets(edge->start, edge->finish, vertexSets);
        }
    }
    
    return mst;
}

/**
 * @brief inSameSet
 * Checks if start and end vertices of an edge are the same cluster of connected
 * vertices.
 * @param start - Start vertex of edge being examined
 * @param end - End vertex of edge being examined
 * @param vertexSets - Vector of vertex clusters
 * @return - Returns true if vertices are in the same cluster
 */
bool inSameSet(Vertex* start, Vertex* end, Vector<Set<Vertex*> >& vertexSets) {
    for (Set<Vertex*> set : vertexSets) {
        if (set.contains(start) && set.contains(end)) return true;
    }
    return false;
}

/**
 * @brief mergeSets
 * Merges the clusters of two vertices (that aren't already in the same set).
 * @param start - Vertex in one cluster
 * @param end - Vertex in another cluster
 * @param vertexSets - Vector of vertex clusters
 */
void mergeSets(Vertex* start, Vertex* end, Vector<Set<Vertex*> >& vertexSets) {
    int startSet, endSet;
    
    // find sets
    Set<Vertex*> curr;
    for (int i = 0; i < vertexSets.size(); i++) {
        curr = vertexSets[i];
        if (curr.contains(start)) {
            startSet = i;
        } else if (curr.contains(end)) {
            endSet = i;
        }
    }
   
    // merge
    vertexSets[startSet] += vertexSets[endSet];
    vertexSets.remove(endSet);
}

/*
 * 
// * Same basic idea as Kruskal's algorithm implementation above, except uses
// * a disjoint set forest instead of a Vector of vertex sets. Clusters are trees
// * with the previous pointers of each vertex pointing either to itself (if it is the
// * head of the tree) or the parent node on the tree. Merging trees requires rewiring
// * of one tree's head to point to the other tree's head. Checking if vertices are in
// * the same tree requires comparing the vertices' heads and seeing if they are the same.
Set<Edge*> kruskal(BasicGraph& graph) {
    // ================== SETUP ===================
    Set<Edge*> mst;
    Set<Edge*> allEdges = graph.getEdgeSet();
    Set<Vertex*> allVertices = graph.getVertexSet();
    
    // put edges and weights in a priority queue
    PriorityQueue<Edge*> pq;
    for (Edge* edge : allEdges) { 
        pq.enqueue(edge, edge->cost);
    }
    
    // each vertex is its own disjoint set; its parent is itself
    for (Vertex* vertex : allVertices) vertex->previous = vertex;
    
    // ================ MAKE TREE =================
    while (!pq.isEmpty()) {
        Edge* edge = pq.dequeue();
        
        // if vertices aren't in the same disjoint set, add the edge to the MST and merge the sets
        Vertex* startParent = parent(edge->start);
        Vertex* finishParent = parent(edge->finish);
        if (startParent != finishParent) { 
            mst.add(edge);
            startParent->previous = finishParent; // merge disjoint sets
        }
    }
    
    return mst;
}

// * Recursively finds the head vertex of the tree of a given vertex.
// * @param curr - Given vertex that wants to find the head of its tree
// * @return - Head vertex
Vertex* parent(Vertex* curr) {
    if (curr->previous == curr) { // at the head of the disjoint set
        return curr;
    } else {
        return parent(curr->previous); // keep going up the set
    }
}
*/
