// ================================ REPORTER ================================ //
// Project:         Reporter
// Name:            reporter.cpp
// Description:     Example code for reporter
// Creator:         Vincent Reverdy
// Contributor(s):  Vincent Reverdy [2018-2019]
// License:         BSD 3-Clause License
// ========================================================================== //
// Reports every lifecycle operation or function call in the following format:
// - Hash code for the template type
// - Hash code for the current thread
// - Id of the current reporter
// - Address of the data (nullptr for invalid state)
// - Value of the data (0 for invalid state)
// - Name of the operation
// ========================================================================== //



// ================================ PREAMBLE ================================ //
// C++ standard library
// Project sources
#include "../include/reporter.hpp"
// Third-party libraries
// Miscellaneous
// ========================================================================== //



// ================================== MAIN ================================== //
// Main function
int main(int argc, char* argv[])
{
    // Initialization
    reporter<> r1;
    reporter<> r2(r1);
    reporter<> r3(r2);
    reporter<> r4(std::move(r1));
    reporter<> r5;

    // Calls
    r1();
    r2();
    r3();
    r4();
    r5();
    
    // Finalization
    return 0;
}
// ========================================================================== //



