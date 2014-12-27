#include <iostream>
#include "dataset.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl << endl;
    
    DataSet test("testing.txt");
    DataEntry entry("");
    
    while(test.nextDataEntry(entry)) {
        entry.print();
    }
    
    return 0;
}

