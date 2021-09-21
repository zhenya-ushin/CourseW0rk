#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "Graphs.h"
using namespace std;

int main()
{

    try
    {
        Graphs graph("test.txt");
        cout << "Maximum flow in network is: " << graph.get_max_flow_size() << endl;
    }
    catch (exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
