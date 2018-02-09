/*! @file program.cpp
    @brief Implementation of Program class
    @defgroup params Parameters
*/
#include "program.hpp"
#include "population.hpp"
#include "individual.hpp"
#include "gene.hpp"

#include <wtl/exception.hpp>
#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/zfstream.hpp>
#include <wtl/filesystem.hpp>
#include <wtl/getopt.hpp>
#include <wtl/chrono.hpp>
#include <sfmt.hpp>
#include <boost/program_options.hpp>

#include <iostream>

namespace grn {

namespace fs = boost::filesystem;
namespace po = boost::program_options;

//! options description for general arguments
inline po::options_description general_desc() {HERE;
    po::options_description description("General");
    description.add_options()
        ("help,h", po::bool_switch(), "print this help")
        ("verbose,v", po::bool_switch(), "verbose output")
        ("test", po::value<int>()->default_value(0)->implicit_value(1));
    return description;
}

/*! @ingroup params

    Command line option | Symbol  | Variable
    ------------------- | ------- | -------------------------
    `-j,--parallel`     |         |
    `-o,--outdir`       |         |
*/
po::options_description Program::options_desc() {HERE;
    const std::string outdir = wtl::strftime("gerene_%Y%m%d_%H%M%S");
    po::options_description description("Program");
    description.add_options()
      ("parallel,j", po::value<unsigned int>()->default_value(1u))
      ("outdir,o", po::value<std::string>()->default_value("")->implicit_value(outdir))
    ;
    // description.add(Population::options_desc());
    description.add(Individual::options_desc());
    description.add(Gene::options_desc());
    return description;
}

[[noreturn]] void Program::help_and_exit() {HERE;
    auto description = general_desc();
    description.add(options_desc());
    // do not print positional arguments as options
    std::cout << "Usage: gerene [options]\n" << std::endl;
    description.print(std::cout);
    throw wtl::ExitSuccess();
}

//! Unit test for each class
inline void test(const int flg) {HERE;
    switch (flg) {
      case 0:
        break;
      case 1:
        Gene::test();
        Individual::test();
        Population::test();
        throw wtl::ExitSuccess();
      default:
        throw std::runtime_error("Unknown argument for --test");
    }
}

Program::Program(const std::vector<std::string>& arguments)
: vars_(std::make_unique<po::variables_map>()) {HERE;
    wtl::join(arguments, std::cout, " ") << std::endl;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.precision(15);
    std::cerr.precision(6);

    auto description = general_desc();
    description.add(options_desc());
    auto& vm = *vars_;
    po::store(po::command_line_parser({arguments.begin() + 1, arguments.end()}).
              options(description).run(), vm);
    if (vm["help"].as<bool>()) {help_and_exit();}
    po::notify(vm);

    config_string_ = wtl::flags_into_string(vm);
    if (vm["verbose"].as<bool>()) {
        std::cerr << wtl::iso8601datetime() << std::endl;
        std::cerr << config_string_ << std::endl;
    }
    test(vm["test"].as<int>());
}

Program::~Program() {HERE;}

void Program::run() {HERE;
    try {
        main();
    } catch (const wtl::KeyboardInterrupt& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Program::main() {HERE;
    auto& vm = *vars_;
    Population pop(6);
    std::cout << pop << std::endl;
    const auto outdir = vm["outdir"].as<std::string>();
    if (!outdir.empty()) {
        DCERR("mkdir && cd to " << outdir << std::endl);
        wtl::ChDir cd_outdir(outdir, true);
        wtl::make_ofs("program_options.conf") << config_string_;
        std::cerr << wtl::iso8601datetime() << std::endl;
    }
}

} // namespace grn
