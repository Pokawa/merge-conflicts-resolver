//
// Created by hubert on 1/4/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
#define MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP

#include <string>
#include <vector>
#include <algorithm>

class conflict
{
protected:
    std::vector<std::string> data;

public:
    int index;

    conflict(std::vector<std::string> lines, int index) : data(std::move(lines)), index(index)
    {}

    virtual std::vector<std::string> getNewLines() noexcept
    {
        return data;
    }

};

class conflictSolved : public conflict
{
private:
    std::vector<std::string>::iterator getCentre()
    {
        return std::find(data.begin(), data.end(), "=======");
    }

protected:
    std::vector<std::string> getOld()
    {
        return {data.begin()+1, getCentre()};
    }

    std::vector<std::string> getNew()
    {
        return {getCentre()+1, data.end()-1};
    }
};

class conflictOld : public conflictSolved
{
public:
    std::vector<std::string> getNewLines() noexcept override
    {
        return getOld();
    }
};

class conflictNew : public conflictSolved
{
public:
    std::vector<std::string> getNewLines() noexcept override
    {
        return getNew();
    }
};

class conflictBoth : public conflictSolved
{
public:
    std::vector<std::string> getNewLines() noexcept override
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
    std::vector<std::string> getNewLines() noexcept override
    {
        auto front = getOld();
        auto back = getNew();
        front.insert(front.end(), back.begin(), back.end());
        return front;
    }
};

#endif //MERGE_CONFLICTS_RESOLVER_CONFLICTS_HPP
