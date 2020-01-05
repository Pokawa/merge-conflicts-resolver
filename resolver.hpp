//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
#define MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP

#include "parsedCode.hpp"
#include "parser.hpp"
#include "fileHandler.hpp"

class resolver
{
private:
    parsedCode instance = parsedCode(types::stringVector(), types::conflictsVector());
    int currentConflictIndex = 0;

public:
    explicit resolver()
    {
    }

    void load(const std::string& filename)
    {
        auto lines = readLinesFromFile(filename);
        instance = parseConflicts(lines);
    }

    void save(const std::string& filename)
    {
        auto newLines = instance.getLines();
        writeLinesToFile(newLines, filename);
    }

    void nextConflict()
    {
        currentConflictIndex++;

        if (currentConflictIndex >= instance.conflictsSize())
            currentConflictIndex = 0;
    }

    void previousConflict()
    {
        currentConflictIndex--;

        if (currentConflictIndex < 0)
            currentConflictIndex = instance.conflictsSize();
    }

    void revertCurrent()
    {
        instance.revertConflict(currentConflictIndex);
    }

    void mergeCurrentToOld()
    {
        instance.mergeToOld(currentConflictIndex);
    }

    void mergeCurrentToNew()
    {
        instance.mergeToNew(currentConflictIndex);
    }

    void mergeCurrentToBoth()
    {
        instance.mergeToBoth(currentConflictIndex);
    }

    void mergeCurrentToBothR()
    {
        instance.mergeToBothR(currentConflictIndex);
    }
};

#endif //MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
