//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
#define MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <bits/unique_ptr.h>
#include "coloredString.hpp"

typedef std::vector<std::string> stringVector;

class conflict
{
private:
    stringVector::iterator getCentrePosition()
    {
        return std::find(data.begin(), data.end(), "=======");
    }

protected:
    stringVector data;

    stringVector getOld()
    {
        return {data.begin()+1, getCentrePosition()};
    }

    stringVector getNew()
    {
        return {getCentrePosition() + 1, data.end() - 1};
    }

    coloredStringVector getOldColored()
    {
        auto lines = getOld();
        coloredStringVector out{};

        std::transform(lines.begin(), lines.end(), std::back_inserter(out), [](const std::string & line)-> coloredString { return {line, textColor::YellowText};});
        return out;
    }

    coloredStringVector getNewColored()
    {
        auto lines = getNew();
        coloredStringVector out{};

        std::transform(lines.begin(), lines.end(), std::back_inserter(out), [](const std::string & line)-> coloredString { return {line, textColor::BlueText};});
        return out;
    }

public:
    int index;

    conflict(stringVector lines, int index) : data(std::move(lines)), index(index)
    {}

    virtual stringVector getNewLines() noexcept
    {
        return data;
    }

    virtual coloredStringVector getNewLinesColored() noexcept
    {
        coloredStringVector out{{data.front(), textColor::RedText}, {"=======", textColor::RedText}, {data.back(), textColor::RedText}};

        auto newLines = getNewColored();
        auto oldLines = getOldColored();

        out.insert(out.begin()+1, oldLines.begin(), oldLines.end());
        out.insert(out.end()-1, newLines.begin(), newLines.end());

        return out;
    }
};

class conflictOld : public conflict
{
public:
    explicit conflictOld(const conflict & object) : conflict(object) {};

    stringVector getNewLines() noexcept override
    {
        return getOld();
    }

    coloredStringVector getNewLinesColored() noexcept override
    {
        return getOldColored();
    }
};

class conflictNew : public conflict
{
public:
    explicit conflictNew(const conflict & object) : conflict(object) {};

    stringVector getNewLines() noexcept override
    {
        return getNew();
    }

    coloredStringVector getNewLinesColored() noexcept override
    {
        return getNewColored();
    }
};

class conflictBoth : public conflict
{
public:
    explicit conflictBoth(const conflict & object) : conflict(object) {};

    stringVector getNewLines() noexcept override
    {
        auto front = getOld();
        auto back = getNew();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }

    coloredStringVector getNewLinesColored() noexcept override
    {
        auto front = getOldColored();
        auto back = getNewColored();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }
};

class conflictBothR : public conflict
{
public:
    explicit conflictBothR(const conflict & object) : conflict(object) {}

    stringVector getNewLines() noexcept override
    {
        auto front = getNew();
        auto back = getOld();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }

    coloredStringVector getNewLinesColored() noexcept override
    {
        auto front = getNewColored();
        auto back = getOldColored();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }
};

typedef std::vector<std::shared_ptr<conflict>> conflictsVector;

#endif //MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
