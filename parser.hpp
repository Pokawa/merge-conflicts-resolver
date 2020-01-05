//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PARSER_HPP
#define MERGE_CONFLICTS_RESOLVER_PARSER_HPP

#include <vector>
#include <memory>
#include "conflicts.hpp"
#include "parsedCode.hpp"
#include "types.hpp"

parsedCode parseConflicts(const types::stringVector &lines)
{
    types::stringVector code;
    types::conflictsVector conflicts;

    auto isStartOfConflict = [](const std::string& line){ return line.find("<<<<<<<") != std::string::npos; };
    auto isEndOfConflict = [](const std::string& line){ return line.find(">>>>>>>") != std::string::npos; };

    auto iter = lines.begin();
    while (iter != lines.end())
    {
        auto start = std::find_if(iter, lines.end(), isStartOfConflict);
        auto end = std::find_if(start, lines.end(), isEndOfConflict) + 1;

        code.insert(code.end(), iter, start);

        types::stringVector tmp{start, end};
        conflicts.push_back(std::make_unique<conflict>(tmp, code.size()));

        iter = end;
    }

    return parsedCode{std::move(code), std::move(conflicts)};
}
#endif //MERGE_CONFLICTS_RESOLVER_PARSER_HPP
