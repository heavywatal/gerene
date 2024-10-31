/*! @file program.cpp
    @brief Implementation of Program class
    @defgroup params Parameters
*/
#include "program.hpp"
#include "population.hpp"
#include "individual.hpp"
#include "gene.hpp"
#include "config.hpp"

#include <wtl/exception.hpp>
#include <wtl/debug.hpp>
#include <wtl/iostr.hpp>
#include <wtl/chrono.hpp>
#include <wtl/zlib.hpp>
#include <clippson/clippson.hpp>

#include <iostream>
#include <fstream>

namespace grn {

namespace fs = std::filesystem;

nlohmann::json VM;

//! Options description for general purpose
inline clipp::group general_options(nlohmann::json* vm) {HERE;
    return (
      clippson::option(vm, {"h", "help"}, false, "print this help"),
      clippson::option(vm, {"version"}, false, "print version"),
      clippson::option(vm, {"v", "verbose"}, false, "verbose output")
    ).doc("General:");
}

/*! @ingroup params

    Command line option | Symbol  | Variable
    ------------------- | ------- | -------------------------
    `-j,--parallel`     |         |
    `-o,--outdir`       |         |
*/

//! Options description for general purpose
inline clipp::group program_options(nlohmann::json* vm) {HERE;
    return (
      clippson::option(vm, {"j", "parallel"}, 1u),
      clippson::option(vm, {"o", "outdir"}, "")
    ).doc("General:");
}

//! Program options
/*! @ingroup params

    Command line option | Symbol         | Variable
    ------------------- | -------------- | -------------------------------
    `-V,--genes`        | \f$V\f$        | NUM_GENES_
*/
inline clipp::group individual_options(nlohmann::json* vm, IndividualParams* p) {HERE;
    return (
      clippson::option(vm, {"V", "genes"}, &p->NUM_GENES)
    ).doc("Individual");
}

//! Program options
/*! @ingroup params

    Command line option | Symbol         | Variable
    ------------------- | -------------- | -------------------------------
    `-L,--cres`         | \f$L\f$        | NUM_CRES_
*/
inline clipp::group gene_options(nlohmann::json* vm, GeneParams* p) {HERE;
    return (
      clippson::option(vm, {"L", "cres"}, &p->NUM_CRES)
    ).doc("Gene");
}

Program::Program(const std::vector<std::string>& arguments) {HERE;
    wtl::join(arguments, std::cout, " ") << std::endl;
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.precision(15);
    std::cerr.precision(6);

    nlohmann::json vm_local;
    IndividualParams individual_params;
    GeneParams gene_params;
    auto cli = (
      general_options(&vm_local),
      program_options(&VM),
      individual_options(&VM, &individual_params),
      gene_options(&VM, &gene_params)
    );
    clippson::parse(cli, arguments);
    auto fmt = clippson::doc_format();
    if (vm_local.at("help")) {
        std::cout << "Usage: " << PROJECT_NAME << " [options]\n\n";
        std::cout << clipp::documentation(cli, fmt) << "\n";
        throw wtl::ExitSuccess();
    }
    if (vm_local.at("version")) {
        std::cout << PROJECT_VERSION << "\n";
        throw wtl::ExitSuccess();
    }

    config_ = VM.dump(2) + "\n";
    if (vm_local.at("verbose")) {
        std::cerr << wtl::iso8601datetime() << std::endl;
        std::cerr << config_ << std::endl;
    }
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
    Population pop(6);
    std::cout << pop << std::endl;
    const auto outdir = VM.at("outdir").get<fs::path>();
    if (!outdir.empty()) {
        const auto config_file = outdir / "config.json";
        DCERR(config_file << std::endl);
        std::ofstream(config_file) << config_;
        std::cerr << wtl::iso8601datetime() << std::endl;
    }
}

} // namespace grn
