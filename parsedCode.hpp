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

class parsedCode
{
private:
    stringVector code;
    conflictsVector conflicts;

public:
    parsedCode(stringVector code, conflictsVector conflicts) : code(std::move(code)), conflicts(std::move(conflicts)) {}


    stringVector getLines()
    {
        auto copy{code};

        auto insertToCopy = [&copy](const std::shared_ptr<conflict>& item){
            auto newLines = item->getNewLines();
            copy.insert(copy.begin() + item->index, newLines.begin(), newLines.end());
        };

        std::for_each(conflicts.rbegin(), conflicts.rend(), insertToCopy);

        return copy;
    }
    //TODO Zrobić wersję kolorową

    int conflictsSize()
    {
        return conflicts.size();
    }

    void revertConflict(unsigned const int index)
    {
        conflicts[index] = std::make_shared<conflict>(*conflicts[index]);
    }

    void mergeToOld(unsigned const int index)
    {
        conflicts[index] = std::make_shared<conflictOld>(*conflicts[index]);
    }

    void mergeToNew(unsigned const int index)
    {
        conflicts[index] = std::make_shared<conflictNew>(*conflicts[index]);
    }

    void mergeToBoth(unsigned const int index)
    {
        conflicts[index] = std::make_shared<conflictBoth>(*conflicts[index]);
    }

    void mergeToBothR(unsigned const int index)
    {
        conflicts[index] = std::make_shared<conflictBothR>(*conflicts[index]);
    }
};


#endif //MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
