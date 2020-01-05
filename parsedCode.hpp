//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
#define MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP

#include <utility>
#include <vector>
#include <string>
#include "conflicts.hpp"

class parsedCode
{
private:
    std::vector<std::string> code;
    std::vector<conflict*> conflicts;

public:
    parsedCode(std::vector<std::string> code, std::vector<conflict*> conflicts) : code(std::move(code)), conflicts(std::move(conflicts)) {}

};


#endif //MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
