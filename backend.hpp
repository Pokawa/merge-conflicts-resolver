//
// Created by hubert on 1/20/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_BACKEND_HPP
#define MERGE_CONFLICTS_RESOLVER_BACKEND_HPP

#include <string>
#include <functional>

class Backend
{
public:
    virtual void runBackend() = 0;
    virtual void bind(std::string, std::function<void()>, std::string) = 0;
    virtual void setRefreshRoutine(std::function<void()>) = 0;
};

#endif //MERGE_CONFLICTS_RESOLVER_BACKEND_HPP
