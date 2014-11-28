// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "costs.h"
#include "trailblazer.h"
using namespace std;

bool DFS(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);

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

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
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
