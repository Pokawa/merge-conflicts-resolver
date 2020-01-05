//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_TYPES_HPP
#define MERGE_CONFLICTS_RESOLVER_TYPES_HPP


#include <vector>
#include <string>
#include "conflicts.hpp"

namespace types
{
    typedef std::vector<std::string> stringVector;
    typedef std::vector<std::unique_ptr<conflict>> conflictsVector;
}

#endif //MERGE_CONFLICTS_RESOLVER_TYPES_HPP
