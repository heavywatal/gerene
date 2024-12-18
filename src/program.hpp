/*! @file program.hpp
    @brief Interface of Program class
*/
#pragma once
#ifndef GRN_PROGRAM_HPP_
#define GRN_PROGRAM_HPP_

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace grn {

//! @cond
class exit_success: public std::logic_error {
  public:
    exit_success() noexcept: std::logic_error("") {}
};
//! @endcond

/*! @brief Program class
*/
class Program {
  public:
    //! parse command arguments
    Program(const std::vector<std::string>& args);
    //! parse command arguments
    Program(int argc, char* argv[])
    : Program(std::vector<std::string>(argv + 1, argv + argc)) {}
    //! non-default destructor for forward declaration
    ~Program();

    //! top level function that should be called once from global main
    void run();

  private:
    //! called from run()
    void main();
    //! writen to "program_options.conf"
    std::string config_;
};

} // namespace grn

#endif /* GRN_PROGRAM_HPP_ */
