/*! @file main.cpp
    @brief Only defines tiny main()
*/
#include "program.hpp"
#include <iostream>

//! Just instantiate and run Program
int main(int argc, char* argv[]) {
    try {
        grn::Program program(argc, argv);
        program.run();
    } catch (const grn::exit_success& e) {
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
