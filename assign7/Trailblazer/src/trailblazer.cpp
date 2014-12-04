// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
#include "pqueue.h"
using namespace std;

bool DFS(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);
void retracePath(Vertex* curr, Vector<Vertex*>& path);
Vector<Vertex*> genericDijkstra(BasicGraph& graph, Vertex* start, Vertex* end, double (newPriority)(Vertex*, Vertex*, double));
double newDijkstraPriority(Vertex* start, Vertex* end, double cost);
double newAStarPriority(Vertex* start, Vertex* end, double cost);

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
 * Retraces found path given the end index of the path.
 * @param curr - End index of the found path
 * @param path - Vector to fill with vertexes on found path 
 */
void retracePath(Vertex* curr, Vector<Vertex*>& path) {
    if (curr == NULL) return;
    retracePath(curr->previous, path);
    path.add(curr);
}

Vector<Vertex*> genericDijkstra(BasicGraph& graph, Vertex* start, Vertex* end, double (newPriority)(Vertex*, Vertex*, double)) {
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
    
    // search
    while (!pqueue.isEmpty()) {
        Vertex* curr = pqueue.dequeue(); // dequeue highest priority node
        curr->visited = true;
        curr->setColor(GREEN);
        
        if (curr == end) { // done searching
            retracePath(curr, path);
            return path;
        }
        
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

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return genericDijkstra(graph, start, end, newDijkstraPriority);
}

double newDijkstraPriority(Vertex* start, Vertex* end, double cost) {
    return cost;
}

double newAStarPriority(Vertex* start, Vertex* end, double cost) {
    return cost + heuristicFunction(start, end);
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return genericDijkstra(graph, start, end, newAStarPriority);
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
