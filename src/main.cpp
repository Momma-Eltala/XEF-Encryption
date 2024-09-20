#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

 
 
const std::string help_arg = "--help";
const std::string xefheader = "\x01XEF";

    char buffer[2048];
//
// if argc == 1:
//   std::cerr << "fuck you" << std::endl
// 
//    // return -1
// bool all_eq = false
// std::string first_arg = argv[1]
// while argp < argc:
//   all_eq &&= std::string(argv[argp]) == first_arg
// 

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
 

template<typename T>
void write_numeric_to_file(std::ofstream &file, T num) {
  file.write(reinterpret_cast<char*>(&num), sizeof(num));
}

void write_to_file(char* buffer, std::ofstream &file, uint32_t bytes) { //takes

  file.write(buffer, bytes);
}
// template<typename T>
// T read_numeric_from_file(std::ifstream &file, int offset) {
//   char buf[sizeof(T)];

//   file.read(buf, sizeof(T));

//   return *reinterpret_cast<T*>(buf);
// }

template<typename T> 
T read_numeric_from_buffer(char *buffer, int offset) {
  return *reinterpret_cast<T*>(buffer + offset);
}

bool _char_compare(const char* segment1, char* segment2, int c) {
  // for (setup; loop while this is true; prepare for next iteration)

  for (int i = 0; segment1[i] == segment2[i]; ++i) {
    --c;

    if (c == 0) {
      return false;
    }
  }

  return true;
}
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

int main(int argc, char** argv) {
  Config config = parse_arguments(argc, argv);

  if (config.make_xef) {
    std::ofstream xef_file(config.output_path);
    xef_file << "\x01XEF";
    write_numeric_to_file(xef_file, config.nodes);
    xef_file << std::string (8, '\0');
    xef_file << std::string(2028, '\0');
    xef_file << std::string(512 * config.nodes, '\0');
 
     if (!xef_file) {
     std::cerr << "\e[1;31m" "Wherever you tried to put the file... it fucking failed. Try again, bitch." "\e[0m" << std::endl;
     return 101;
    }
    config.file_input_size = (2048+512*config.nodes);
  }
  if (config.make_xef && !config.nodes) {
    std::cerr << "Okay, you tried to make a file, but you didn't give it a size." << std::endl;
    return 1;
  }


  if (config.add_xef) {

    std::ifstream inputfile (config.inputfilex, std::ifstream::binary);
    std::ifstream xef_file_use (config.output_path, std::ifstream::binary);
    if (!xef_file_use || !inputfile) {
      std::cerr << "sorry, can you please tell me about somethat that fucking EXIST?! because "; 
      if (!xef_file_use) {
        std::cerr << config.output_path;
      }
      else {
        std::cerr << config.inputfilex;
      }
      std::cerr << " does not exist." 
      << std::endl;
      return 1;
    }
    xef_file_use.read (buffer, 2048);
    bool not_xef = _char_compare(xefheader.c_str(), buffer, 4);
    if(not_xef) {
      std::cerr << "*long sigh* "
      << config.output_path
      << " is not a xef file."
      << std::endl;
      return 4;
    }

    config.nodes = read_numeric_from_buffer<int>(buffer, 4);
    
  }
  /*
  if (config.nodes >= 1024*10) {
    std::cerr << "i dont think a your mom is fat joke works here... are you a byte slut?" 
    << std::endl
    << "Oh. for the record. The file size is "
    << config.file_input_size
    << " bytes, non human readable because fuck you"
    << std::endl;
    return 0;
  }

  if (config.nodes >= 1024) {
    std::cerr << "Wow.... " 
    << config.nodes
    << " nodes. you needed a place to put the images of your mom about how fat she is, that the jpeg image is bigger then png?"
    << std::endl
    << "Oh. for the record. The file size is "
    << config.file_input_size
    << " bytes, non human readable because fuck you"
    << std::endl;
    return 0;
    
  }
  */
  std::cerr << "Wow, you did it!!!!!! " << config.output_path << " with length of " << std::to_string(config.nodes) << " nodes" << std::endl;

  return 0;
}








// void some_fn() {
// some_label:
//   std::cout << "yes" << std::endl;
//   goto also_a_label;

// another_label:
//   std::cout << "idk do something here"<< std:endl;

// also_a_label:
//   return;
// }