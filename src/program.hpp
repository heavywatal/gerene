/*! @file program.hpp
    @brief Interface of Program class
*/
#pragma once
#ifndef GRN_PROGRAM_HPP_
#define GRN_PROGRAM_HPP_

#include <vector>
#include <string>

#include <boost/program_options.hpp>

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

    //! top level function that should be called once from global main
    void run();

  private:
    //! called from run()
    void main();
    //! options description for Program class
    boost::program_options::options_description options_desc();
    //! print help message and exit
    void help_and_exit();

    //! number of threads
    unsigned int concurrency_ = 1;
    //! `-w`
    bool is_writing_ = false;
    //! name of output directory
    std::string out_dir_ = "";
    //! writen to "program_options.conf"
    std::string config_string_;
};

} // namespace grn

#endif /* GRN_PROGRAM_HPP_ */
