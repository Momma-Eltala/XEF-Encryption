#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>

#include "node_iterator.hpp"
#include "parse_arguments.hpp"

 
 
const std::string help_arg = "--help";
const std::string xefheader = "\x01XEF";
char buffer[2048];


template<typename T>
void write_numeric_to_file(std::ofstream &file, T num) {
  file.write(reinterpret_cast<char*>(&num), sizeof(num));
}

void write_to_file(char* buffer, std::ofstream &file, uint32_t bytes) { //takes
  file.write(buffer, bytes);
}

template<typename T>
T read_numeric_from_file(std::ifstream &file, int offset) {
  char buf[sizeof(T)];

  file.read(buf, sizeof(T));

  return *reinterpret_cast<T*>(buf);
}

// read_numeric_from_file<Node>(the_file, the_nodes_offset)


bool _char_compare(const char* segment1, char* segment2, int c) {
  for (int i = 0; segment1[i] == segment2[i]; ++i) {
    --c;

    if (c == 0) {
      return false;
    }
  }

  return true;
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