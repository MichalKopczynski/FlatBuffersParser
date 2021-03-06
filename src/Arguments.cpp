#include "Arguments.hpp"

#include <iostream>
#include "cxxopts.hpp"

#include "version.hpp"

void Arguments::parse(int argc, char ** argv){
    cxxopts::Options options("FlatBuffersParser", "FlatBuffers Parser is socket based tool for parsing binary FlatBuffers data to JSON format.");

    options.add_options()
        ("p,port", "Port to listen.", cxxopts::value<int>())
        ("f,file", "Schema files.", cxxopts::value<std::vector<std::string>>())
        ("v,version", "Print the version number and exit.")
        ("h,help", "Print help and exit.")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")){
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    if (result.count("version")){
      std::cout << "FlatBuffersParser version " << FLATBUFFERSPARSER_VERSION << std::endl;
      exit(0);
    }

    if (result.count("file")) {
        schemaFiles = result["file"].as<std::vector<std::string>>();
    }
    else {
        throw SchemaFileNotSpecifiedException();
    }

    if (result.count("port")) {
        port = result["port"].as<int>();
    }
    else {
        throw PortNotSpecifiedException();
    }
}
