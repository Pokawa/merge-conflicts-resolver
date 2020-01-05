//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
#define MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "conflicts.hpp"
#include "types.hpp"

class parsedCode
{
private:
    types::stringVector code;
    types::conflictsVector conflicts;

public:
    parsedCode(types::stringVector code, types::conflictsVector conflicts) : code(std::move(code)), conflicts(std::move(conflicts)) {}


    types::stringVector getLines()
    {
        auto copy{code};

        auto insertToCopy = [&copy](conflict* item){
            auto newLines = item->getNewLines();
            copy.insert(copy.begin() + item->index, newLines.begin(), newLines.end());
        };

        std::for_each(conflicts.begin(), conflicts.end(), insertToCopy);

        return copy;
    }
    //TODO Zrobić wersję kolorową

    int conflictsSize()
    {
        return conflicts.size();
    }

    void revertConflict(unsigned const int index)
    {
        conflicts[index] = std::make_unique<conflict>(*conflicts[index]);
    }

    void mergeToOld(unsigned const int index)
    {
        conflicts[index] = std::make_unique<conflictOld>(*conflicts[index]);
    }

    void mergeToNew(unsigned const int index)
    {
        conflicts[index] = std::make_unique<conflictNew>(*conflicts[index]);
    }

    void mergeToBoth(unsigned const int index)
    {
        conflicts[index] = std::make_unique<conflictBoth>(*conflicts[index]);
    }

    void mergeToBothR(unsigned const int index)
    {
        conflicts[index] = std::make_unique<conflictBothR>(*conflicts[index]);
    }
};


#endif //MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
