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

        auto insert = [&copy](const std::shared_ptr<conflict>& item){
            auto newLines = item->getNewLines();
            copy.insert(copy.begin() + item->index, newLines.begin(), newLines.end());
        };

        std::for_each(conflicts.rbegin(), conflicts.rend(), insert);

        return copy;
    }

    coloredStringVector getLinesColored()
    {
        coloredStringVector out{};

        std::transform(code.begin(), code.end(), std::back_inserter(out), [](const std::string & line) -> coloredString { return {line, textColor::WhiteText};});

        auto insertColored = [&out](const std::shared_ptr<conflict>& item){
            auto newLines = item->getNewLinesColored();
            out.insert(out.begin() + item->index, newLines.begin(), newLines.end());
        };

        std::for_each(conflicts.rbegin(), conflicts.rend(), insertColored);

        return out;
    }

    int conflictsSize()
    {
        return conflicts.size();
    }

    void revertConflict(unsigned const int index)
    {
        convertConflict<conflict>(index);
    }

    void mergeToOld(unsigned const int index)
    {
        convertConflict<conflictOld>(index);
    }

    void mergeToNew(unsigned const int index)
    {
        convertConflict<conflictNew>(index);
    }

    void mergeToBoth(unsigned const int index)
    {
        convertConflict<conflictBoth>(index);
    }

    void mergeToBothR(unsigned const int index)
    {
        convertConflict<conflictBothR>(index);
    }

private:

    template <class targetType>
    void convertConflict(unsigned const int index)
    {
        conflicts[index] = std::make_shared<targetType>(*conflicts[index]);
    }
};


#endif //MERGE_CONFLICTS_RESOLVER_PARSEDCODE_HPP
