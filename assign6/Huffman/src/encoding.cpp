// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "pqueue.h"
#include "vector.h"

// helper functions
void makePriorityQueue(PriorityQueue<HuffmanNode*>& pqueue, const Map<int, int>& freqTable); 
void makeTree(PriorityQueue<HuffmanNode*>& pqueue);
void traverseTree(HuffmanNode* currNode, Map<int, string>& encodingMap, string currCode);
void writeBit(obitstream& output, string value);

/**
 * @brief buildFrequencyTable
 * Counts frequency of characters in an input (string or file), puts them
 * in a map, and returns the map when it reaches the end of the file. Assumes 
 * input file exists and can be read. 
 * @param input - valid input (string or file) from user
 * @return - map of frequency of each character
 */
Map<int, int> buildFrequencyTable(istream& input) {
    // init variables
    Map<int, int> freqTable;
    bool endOfFile = false;
    char currCharacter;
    
    // count character frequencies
    while (!endOfFile) {
        currCharacter = input.get();
        if (currCharacter == -1) { // end of file
            endOfFile = true;
            freqTable.put(PSEUDO_EOF, 1);
        } else { // otherwise, valid character
            freqTable[currCharacter]++;
        }
    }
    
    return freqTable;
}

/**
 * @brief buildEncodingTree
 * Builds encoding tree that arranges characters and their frequencies
 * from most to least frequent. 
 * @param freqTable - Map of characters and their corresponding frequencies;
 *                    passed by reference. 
 * @return - Returns pointer to parent node of encoding tree
 */
HuffmanNode* buildEncodingTree(const Map<int, int>& freqTable) {
    PriorityQueue<HuffmanNode*> pqueue;
    makePriorityQueue(pqueue, freqTable);
    makeTree(pqueue);
    
    return pqueue.peek();   // this is just a placeholder so it will compile
}

/**
 * @brief makeTree
 * Makes encoding tree out of priority queue of HuffmanNodes. Tree has
 * most frequent character near the top and least frequent characters
 * as leaves on the bottom.
 * @param pqueue - priority queue of HuffmanNodes used to make encoding 
 *                 tree; passed by reference
 */
void makeTree(PriorityQueue<HuffmanNode*>& pqueue) {
    while (pqueue.size() > 1) {
        // dequeue first two nodes, store in left and right
        HuffmanNode* left = pqueue.dequeue();
        HuffmanNode* right = pqueue.dequeue();
        
        // make new parent node with children attached
        int countSum = left->count + right->count;
        HuffmanNode* parent = new HuffmanNode(NOT_A_CHAR, countSum, left, right);
        
        // enqueue parent
        pqueue.enqueue(parent, countSum);
    }
}

/**
 * @brief makePriorityQueue
 * Packages each character and its frequency into a HuffmanNode and enqueues
 * the nodes into a priority queue. 
 * @param pqueue - Priority queue to fill; passed by reference.
 * @param freqTable - Map of each character and its frequency; passed by reference. 
 */
void makePriorityQueue(PriorityQueue<HuffmanNode*>& pqueue, const Map<int, int>& freqTable) {
    Vector<int> keys = freqTable.keys();
    
    for (int key : keys) {
        HuffmanNode* node = new HuffmanNode(key, freqTable[key]);
        pqueue.enqueue(node, freqTable[key]);
    }
}

/**
 * @brief buildEncodingMap
 * Builds encoding map of characters and their codes by calling recursive 
 * traverseTree function. 
 * @param encodingTree - pointer to first node in encoding tree from previous step
 * @return - encoding map. Empty map if pointer to first node in tree is null.
 */
Map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    Map<int, string> encodingMap;
    if(encodingTree != NULL) traverseTree(encodingTree, encodingMap, "");    
    return encodingMap;
}

/**
 * @brief traverseTree
 * Recursively goes through tree, assigning codes to each leaf node (character).
 * @param currNode - pointer to current node in the tree
 * @param encodingMap - map passed by reference that stores characters and their codes
 * @param currCode - string with current code, built up by 0's and 1's based on left 
 *                   and right branches
 */
void traverseTree(HuffmanNode* currNode, Map<int, string>& encodingMap, string currCode) {
    if (currNode->isLeaf()) {
        encodingMap.put(currNode->character, currCode); // add character and code to map
        return;
    }
    
    traverseTree(currNode->zero, encodingMap, currCode + "0"); // left
    traverseTree(currNode->one, encodingMap, currCode + "1"); // right
}

/**
 * @brief encodeData
 * Goes through input file and creates Huffman encoding for file contents based
 * on previously made encoding map for each character. Writes Huffman encoding to 
 * output. 
 * @param input - input file or string
 * @param encodingMap - map of characters and their codes; previously created.
 * @param output - output stream where Huffman encoding is written
 */
void encodeData(istream& input, const Map<int, string>& encodingMap, obitstream& output) {
    char currCharacter;
    bool endOfFile = false;
    
    while (!endOfFile) {
        currCharacter = input.get();
        if (currCharacter == -1) { // end of file
            writeBit(output, encodingMap.get(PSEUDO_EOF));
            endOfFile = true;
        } else {
            writeBit(output, encodingMap.get(currCharacter));
        }
    }
}

/**
 * @brief writeBit
 * Given a string code of 0's and 1's, writes the appropriate bits to output stream.
 * @param output - output stream to write bits
 * @param value - string code to convert into bits
 */
void writeBit(obitstream& output, string value) {
    for (int i = 0; i < value.length(); i++) {
        if (value[i] == '0') {
            output.writeBit(0);
        } else if (value[i] == '1') {
            output.writeBit(1);
        }
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
