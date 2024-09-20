#include "parse_arguments.hpp"
#include <vector>
#include <iostream>

Config parse_arguments(int argc, char** argv) {
 if (argc == 1) {
    std::cerr << "USE F*CKING ARGUMENTS!!!" << std::endl;
    std::exit (1);
  }  

  std::vector<std::string> args;
  args.reserve(argc);
  
  Config config;

  for (int i = 0; i < argc; i++) {
    args.push_back(std::string(argv[i]));
  }

  for (int i = 1; i < argc; i++) {
    auto arg = args[i];

    if (arg == "--help") {
      std::cerr << "--help : prints this text aka help" << std::endl
                << "-c : create XEF file, then give it a path and name to make a file '/path/file.xef'" << std::endl
                << "-s : size, used with -c. this is the node count, this determines how many files and folders you can have." << std::endl;
      std::exit (0);
    }

    if (arg == "-c") {
      i++;
      config.output_path = args[i];
      config.make_xef = true;
      continue;
    }

    if (arg == "-s") {
      i++;
      config.nodes = std::stoi(args[i]);
      continue;
    }

    if (arg == "-x") {
      i++;
      config.output_path = args[i];
      config.add_xef = true;
      continue;
    }

    if (arg == "-i") {
      i++;
      config.inputfilex = args[i];
      config.addfile = true;
      continue;
    }

    std::cerr << args[i] << " i dont know what you want me to do with this you fucking idiot." << std::endl;
    std::exit (-1);
  }

  if (config.make_xef && config.add_xef) {
    std::cerr << "you cant. make a fucking xef file, and add to it. it might break things dimwit." << std::endl;
    std::exit (-1);
  }

  if (config.add_xef != config.addfile) {
    std::cerr << "okay, what file to add? im asking politly." << std::endl;
    std::exit (-2);
  }
  return config;
}