//
// Created by hubert on 1/4/20.
//

#include "resolver.hpp"

int main()
{
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    auto a = std::make_shared<conflict>(lines, 0);
    std::shared_ptr<conflict> l = std::make_shared<conflictNew>(*a);
    auto b = l->getNewLines();
    return 0;
}

