/*! @file program.hpp
    @brief Interface of Program class
*/
#pragma once
#ifndef GRN_PROGRAM_HPP_
#define GRN_PROGRAM_HPP_

#include <vector>
#include <string>
#include <memory>

namespace boost {namespace program_options {
  class options_description;
  class variables_map;
}}

namespace grn {

/*! @brief Program class
*/
class Program {
  public:
    //! parse command arguments
    Program(const std::vector<std::string>& args);
    //! parse command arguments
    Program(int argc, char* argv[])
    : Program(std::vector<std::string>(argv, argv + argc)) {}
    //! non-default destructor for forward declaration
    ~Program();

    //! top level function that should be called once from global main
    void run();

  private:
    //! called from run()
    void main();
    //! print help message and exit
    [[noreturn]] void help_and_exit();
    //! options description for Program class
    boost::program_options::options_description options_desc();
    //! optional variables
    std::unique_ptr<boost::program_options::variables_map> vars_;
    //! writen to "program_options.conf"
    std::string config_string_;
};

} // namespace grn

#endif /* GRN_PROGRAM_HPP_ */
