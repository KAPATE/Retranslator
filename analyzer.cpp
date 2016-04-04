#include "analyzer.h"

std::vector <std::string> add(std::string line) {
    std::vector <std::string> code {};
    std::string command {};
    int i = 0;
    while (i<5) {
        if (i==4) {
            command = line.substr(0,line.length()-1);
            line.clear();
        }
        else {
            command = line.substr(0,line.find(','));
            line.erase(0,line.find(',')+1);
        }

        if (!command.empty()) {
                code.push_back(command);
        }
        else {
            code.push_back("NULL");
        }
        i++;
        }
    return code;
}
