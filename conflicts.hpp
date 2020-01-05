//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
#define MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <bits/unique_ptr.h>
#include "types.hpp"

class conflict
{
protected:
    types::stringVector data;

public:
    int index;

    conflict(types::stringVector lines, int index) : data(std::move(lines)), index(index)
    {}

    //TODO Zrobić wersję kolorową
    virtual types::stringVector getNewLines() noexcept
    {
        return data;
    }
};

class conflictSolved : public conflict
{
private:
    types::stringVector::iterator getCentre()
    {
        return std::find(data.begin(), data.end(), "=======");
    }

protected:
    types::stringVector getOld()
    {
        return {data.begin()+1, getCentre()};
    }

    types::stringVector getNew()
    {
        return {getCentre()+1, data.end()-1};
    }

public:
    explicit conflictSolved(const conflict & object) : conflict(object) {};
};

class conflictOld : public conflictSolved
{
public:
    using conflictSolved::conflictSolved;

    types::stringVector getNewLines() noexcept override
    {
        return getOld();
    }
};

class conflictNew : public conflictSolved
{
public:
    using conflictSolved::conflictSolved;

    types::stringVector getNewLines() noexcept override
    {
        return getNew();
    }
};

class conflictBoth : public conflictSolved
{
public:
    using conflictSolved::conflictSolved;

    types::stringVector getNewLines() noexcept override
    {
        auto front = getNew();
        auto back = getOld();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }
};

class conflictBothR : public conflictSolved
{
public:
    using conflictSolved::conflictSolved;

    types::stringVector getNewLines() noexcept override
    {
        auto front = getOld();
        auto back = getNew();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }
};

#endif //MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
