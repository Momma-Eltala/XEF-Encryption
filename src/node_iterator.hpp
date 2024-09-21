/*
node_iterator.hpp
Interface for loading nodes from an XEF file.

Copyright (c) 2024 Jonathan (Eltala) Moore
*/

#include <fstream>


namespace load {
    int load_nodes(char* buffer_pointer,  std::ifstream &file, int nodes);
}

namespace write {
    int write_node(char* filename, std::ofstream &file, bool folder);
}


/*
    md5 sum starts at 0x000
    parent node starts at 0x020
    directory node pointer starts at 0x024
    sibling id starts at 0x028
    file name starts at 0x02c
    size starts at 0x128
    flags start at 0x12a
    offset starts 0x12c
*/
struct Node {
    char md5[32];
    int32_t parent, directory, sibling_id;
    char name[256];
    int64_t size;
    int16_t flags;
    int64_t offset;
};

template<typename T> 
T read_numeric_from_buffer(char *buffer, int offset) {
  return *reinterpret_cast<T*>(buffer + offset);
}