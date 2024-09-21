/*
node_iterator.hpp
Interface for loading nodes from an XEF file.

Copyright (c) 2024 Jonathan (Eltala) Moore
*/

#include <fstream>
#include <vector>
#include <iostream>
#include <cstdint>

namespace load {
    int load_nodes(std::ifstream &file, int nodes);
}

namespace write {
    int write_node(char* filename, std::ofstream &file, bool folder, long bytes);
}


/*
    md5 sum starts at 0x000
    parent node starts at 0x020
    directory node pointer starts at 0x024
    sibling id starts at 0x028
    file name starts at 0x02c
    size starts at 0x12c
    flags start at 0x134
    offset starts 0x136
*/
struct Node {
    char md5[32];
    uint32_t parent, directory, sibling_id;
    char name[256];
    uint64_t size;
    uint16_t flags;
    uint64_t offset;
    uint64_t end_offset;
};

template<typename T> 
T read_numeric_from_buffer(char *buffer, int offset) {
  return *reinterpret_cast<T*>(buffer + offset);
}

extern std::vector<Node> NODES;