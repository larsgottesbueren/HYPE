#include <Hypergraph.hpp>
#include <Parsing.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>


namespace {

std::istringstream get_tokenized_line_skipping_comments(std::ifstream& f) {
    std::string line;
    do { ; } while (std::getline(f, line) && line[0] == '%');
    return std::istringstream(line);
}

void parseHMetis(part::Hypergraph& hg, std::ifstream& fs) {
    // parse header
    int64_t numNodes, numHyperedges;
    uint64_t hypergraphType = 0;
    auto header = get_tokenized_line_skipping_comments(fs);
    header >> numHyperedges >> numNodes;
    if (header >> hypergraphType) {
        if (hypergraphType != 0) {
            throw std::runtime_error("HYPE does not support weighted hypergraphs.");
        }
    }
    
    std::vector<int64_t> pin_list;
    for (int64_t e = 0; e < numHyperedges; ++e) {
        pin_list.clear();
        auto pin_list_string = get_tokenized_line_skipping_comments(fs);
        int64_t pin;
        while (pin_list_string >> pin) {
            pin_list.push_back(pin);
        }
        
        hg.addNodeList(e, pin_list);
    }
}

} // namespace

auto part::operator>>(std::istream& in, part::ParsingMode& mode)
    -> std::istream&
{
    std::string token;
    in >> token;
    if(token == "hmetis")
        mode = part::ParsingMode::Hmetis;
    else if(token == "hyperedgelist")
        mode = part::ParsingMode::EdgeList;
    else if(token == "bipartite")
        mode = part::ParsingMode::Bipartite;
    else
        in.setstate(std::ios_base::failbit);
    return in;
}

auto part::operator<<(std::ostream& os, const part::ParsingMode& mode)
    -> std::ostream&
{
    switch(mode) {
    case part::ParsingMode::Hmetis:
        os << "hmetis";
        break;
    case part::ParsingMode::EdgeList:
        os << "hyperedgelist";
        break;
    case part::ParsingMode::Bipartite:
        os << "bipartite";
    default:
        os.setstate(std::ios_base::failbit);
        break;
    }

    return os;
}

auto part::parseFileIntoHypergraph(const std::string& path,
                                   ParsingMode mode)
    -> part::Hypergraph
{
    part::Hypergraph ret_graph{};

    //file handling
    std::ifstream edge_file(path);
    if(!edge_file) {
        std::cout << "file: " << path << "not found\n";
        std::exit(-1);
    }

    //parse input file with the specified parser
    switch(mode) {
    case part::ParsingMode::Hmetis:
        parseHMetis(ret_graph, edge_file);
        break;
    case part::ParsingMode::EdgeList:
        throw std::runtime_error("EdgeList format currently not implemented");
    case part::ParsingMode::Bipartite:
        throw std::runtime_error("Bipartite HG format currently not implemented");
    }

    return ret_graph;
}
