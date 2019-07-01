#include <iostream>
using namespace std;


#include "gc_details.h"
// #include "gc_pointer.h"
// #include "LeakTester.h"

int main()
{
    //Test Pointer details
    testPtrDetails();

    //Commented for now
    // Pointer<int> p = new int(19);
    // p = new int(21);
    // p = new int(28);

    cout << "Done!" << endl;   
    return 0;
}