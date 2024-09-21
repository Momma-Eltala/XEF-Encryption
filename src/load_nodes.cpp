/*
Copyright (c) 2024 Jonathan (Eltala) Moore

This loads used nodes to the heap
*/
#include "node_iterator.hpp"
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
            Node node = read_numeric_from_buffer<Node>(node_buffer, 0);

            NODES.push_back(node); 
            std::cerr << i << " nodes left" << std::endl;
        } else {
            ++nodes_free;
        }

        long TEST = node_buffer[0x12c];
        std::cout << TEST << std::endl;
    }  // some body
    return nodes_free;
}