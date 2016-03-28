#include "analyzer.h"

std::string parser(std::string code) {
    std::cout<<"i_am_in analyzer"<<std::endl;
    int npos {};
    int last_pos {};
    npos = code.find("\n",npos);
    std::string line = code.substr(last_pos,npos);
    std::string command = analyzer(line);
    std::cout<<line;
    return code;
}

std::string analyzer(std::string line) {

}
