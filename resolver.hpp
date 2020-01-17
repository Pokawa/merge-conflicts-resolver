//
// Created by hubert on 1/5/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
#define MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP

#include "parsedCode.hpp"
#include "parser.hpp"
#include "fileHandler.hpp"
#include "printHandler.hpp"

class resolver
{
private:
    parsedCode instance;
    printHandler printer;
    coloredStringVector printingData;
    int currentConflictIndex;
    int currentPrintingPosition;

public:
    explicit resolver() : instance(stringVector(), conflictsVector()), currentConflictIndex(0)
    {
    }

    void load(const std::string& filename)
    {
        auto lines = readLinesFromFile(filename);
        instance = parseConflicts(lines);
        refreshPrintingData();
        getPrintingIndex();
    }

    void save(const std::string& filename)
    {
        auto newLines = instance.getLines();
        writeLinesToFile(newLines, filename);
    }

    void printToTerminal()
    {
        printer.printOnScreen(printingData, currentPrintingPosition);
    }

    void nextLine()
    {
        currentPrintingPosition++;
        //TODO blokada
    }

    void previousLine()
    {
        currentPrintingPosition--;
        if (currentPrintingPosition < 0)
            currentPrintingPosition = 0;
    }

    void nextConflict()
    {
        currentConflictIndex++;

        if (currentConflictIndex >= instance.conflictsSize())
            currentConflictIndex = 0;

        getPrintingIndex();
    }

    void previousConflict()
    {
        currentConflictIndex--;

        if (currentConflictIndex < 0)
            currentConflictIndex = instance.conflictsSize();

        getPrintingIndex();
    }

    void revertCurrent()
    {
        instance.revertConflict(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToOld()
    {
        instance.mergeToOld(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToNew()
    {
        instance.mergeToNew(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToBoth()
    {
        instance.mergeToBoth(currentConflictIndex);
        refreshPrintingData();
    }

    void mergeCurrentToBothR()
    {
        instance.mergeToBothR(currentConflictIndex);
        refreshPrintingData();
    }

private:
    void getPrintingIndex()
    {
        currentPrintingPosition = instance.getConflictPosition(currentConflictIndex);
    }

    void refreshPrintingData()
    {
        printingData = instance.getLinesColored();
    }
};

#endif //MERGE_CONFLICTS_RESOLVER_RESOLVER_HPP
