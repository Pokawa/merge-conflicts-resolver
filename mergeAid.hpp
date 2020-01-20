//
// Created by hubert on 1/20/20.
//

#ifndef MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP
#define MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP

#include <string>
#include <map>
#include "frontend.hpp"
#include "backend.hpp"
#include "resolver.hpp"

class mergeAid : public Frontend
{
public:
    void setEntry(std::string key, std::string value) override {
        entries[key] = value;
    }

    std::string getEntry(std::string string) override {
        return entries[string];
    }

    void setBackend(Backend *obj) override {
        auto loadFile = [this](){ this->res.load(entries["filename"]); this->res.printToTerminal(); };
        auto writeFile = [this](){ this->res.save(entries["filename"]); };
        auto nextLine =[this](){ this->res.nextLine(); this->res.printToTerminal(); };
        auto previousLine =[this](){ this->res.previousLine(); this->res.printToTerminal(); };
        auto nextConflict =[this](){ this->res.nextConflict(); this->res.printToTerminal(); };
        auto previousConflict =[this](){ this->res.previousConflict(); this->res.printToTerminal(); };
        auto revert = [this](){ this->res.revertCurrent(); this->res.printToTerminal(); };
        auto toNew = [this](){ this->res.mergeCurrentToNew(); this->res.printToTerminal(); };
        auto toOld = [this](){ this->res.mergeCurrentToOld(); this->res.printToTerminal(); };
        auto toBoth = [this](){ this->res.mergeCurrentToBoth(); this->res.printToTerminal(); };
        auto toBothR = [this](){ this->res.mergeCurrentToBothR(); this->res.printToTerminal(); };

        obj -> bind("#vim#:o ${filename}<ENTER>", loadFile, "Open and load file");
        obj -> bind("#vim#:wa ${filename}<ENTER>", writeFile, "Write to file given name");
        obj -> bind("#vim#:w<ENTER>", writeFile, "Write to file");
        obj -> bind("#vim#j", nextLine, "Jump to next line");
        obj -> bind("#vim#k", previousLine, "Jump to previous line");
        obj -> bind("#vim#l", nextConflict, "Jump to next conflict and select");
        obj -> bind("#vim#h", previousConflict, "Jump to previous conflict and select");
        obj -> bind("#vim#1", revert, "Revert conflict to default state");
        obj -> bind("#vim#2", toNew, "Solve conflict choosing new version");
        obj -> bind("#vim#3", toOld, "Solve conflict choosing old version");
        obj -> bind("#vim#4", toBoth, "Solve conflict choosing two options, old first");
        obj -> bind("#vim#5", toBothR, "Solve conflict choosing two options, new first");
    }

private:
    resolver res;
    std::map<std::string, std::string> entries;
};

#endif //MERGE_CONFLICTS_RESOLVER_MERGEAID_HPP
