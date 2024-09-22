/*
Copyright (c) 2024 Jonathan (Eltala) Moore

This loads used nodes to the heap
*/
#include "node_iterator.hpp"
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>

char node_buffer[512];
int nodes_free;

std::vector<Node> NODES;

int load::load_nodes(std::ifstream &file, int nodes) {
    file.seekg(2048);

    for (int i = nodes; i > 0; i--) {
        file.read(node_buffer, 512);
        bool used_node = node_buffer[0x135] & 1;

        if (used_node) {
            //Node node = read_numeric_from_buffer<Node>(node_buffer, 0);

            // long TEST = read_numeric_from_buffer<long>(node_buffer, 0x12c);
            // std::cout << TEST << std::endl;

            Node node;
            strncpy(node.md5, node_buffer, 32);
            node.parent = read_numeric_from_buffer<uint32_t>(node_buffer, 0x020);
            node.directory = read_numeric_from_buffer<uint32_t>(node_buffer, 0x024);
            node.sibling_id = read_numeric_from_buffer<uint32_t>(node_buffer, 0x028);
            strncpy(node.name, (node_buffer + 0x2c), 256);
            node.size = read_numeric_from_buffer<uint64_t>(node_buffer, 0x012c);
            node.flags = read_numeric_from_buffer<uint16_t>(node_buffer, 0x0134);
            node.offset = read_numeric_from_buffer<uint64_t>(node_buffer, 0x0136);
            node.end_offset = read_numeric_from_buffer<uint64_t>(node_buffer, 0x013e);


            NODES.push_back(node);
/* 
            std::cerr << i << " nodes left" << std::endl;
            // for (auto& node : NODES) {
                std::cout << "size:" << node.size << std::endl;
            // }
*/
        } else {
            ++nodes_free;
        }

    }  // some body
    return nodes_free;
}