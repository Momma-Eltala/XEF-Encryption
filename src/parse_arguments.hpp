#include <string>

struct Config {
  std::string output_path;
  int nodes = 0;
  long used_nodes = 0;
  bool add_xef = false;
  bool make_xef = false;
  bool addfile = false;
  long file_input_size;
  std::string inputfilex;
};

Config parse_arguments(int argc, char** argv); 


// parse_arguments::parse_arguments()

// using namespace parse_arguments;
// parse_arguments();