//
// Created by hubert on 1/20/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_FRONTEND_HPP
#define MERGE_CONFLICTS_RESOLVER_FRONTEND_HPP

#include <string>

class Backend;

class Frontend {
public:
    virtual void setEntry(std::string,std::string) = 0;
    virtual std::string getEntry(std::string) = 0;
    virtual void setBackend( Backend * obj) = 0;
};

#endif //MERGE_CONFLICTS_RESOLVER_FRONTEND_HPP
