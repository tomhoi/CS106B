// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
#include "queue.h"
using namespace std;

bool DFS(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);
void retracePath(Vertex* curr, Vector<Vertex*>& path);

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
    Vector<Vertex*> temp;
    for (curr; curr != NULL; curr = curr->previous) { // retrace
        temp.add(curr);
    }   
    for (int i = temp.size() - 1; i >= 0; i--) { // flip the vector so start index is at 0
        path.add(temp[i]);
    }
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
