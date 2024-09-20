#include "node_iterator.hpp"
#include <vector>
#include <fstream>

char node_buffer[512];
int nodes_free;

std::vector<Node> NODES;

int load::load_nodes(char* buffer_pointer, std::ifstream &file, int nodes) {
    for (int i = nodes; nodes > 0; --i) {
        file.read(node_buffer, 512);
        bool used_node = node_buffer[0x12b] & 1;

        if (used_node) {
            Node node = read_numeric_from_buffer<Node>(node_buffer, 0);

            NODES.push_back(node); 
        }
        else {
            ++nodes_free;
        }
    }  // some body
    return nodes_free;
}
 