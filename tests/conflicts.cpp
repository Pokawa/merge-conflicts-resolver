//
// Created by hubert on 1/17/20.
//

#include <memory>
#include "gtest/gtest.h"
#include "conflicts.hpp"

TEST(ConflictsPolymorhpism, Constructing) {
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};

    auto conf = std::make_shared<conflict>(lines, 0);

    ASSERT_EQ(conf->getNewLines(), newlines);
}

TEST(ConflictsPolymorhpism, New) {
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"456\n"};

    auto foo = std::make_shared<conflict>(lines, 0);
    auto conf = std::make_shared<conflictNew>(*foo);

    ASSERT_EQ(conf->getNewLines(), newlines);
}

TEST(ConflictsPolymorhpism, Old) {
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"123\n"};

    auto foo = std::make_shared<conflict>(lines, 0);
    auto conf = std::make_shared<conflictOld>(*foo);

    ASSERT_EQ(conf->getNewLines(), newlines);
}

TEST(ConflictsPolymorhpism, Both) {
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"123\n", "456\n"};

    auto foo = std::make_shared<conflict>(lines, 0);
    auto conf = std::make_shared<conflictBoth>(*foo);

    ASSERT_EQ(conf->getNewLines(), newlines);
}

TEST(ConflictsPolymorhpism, BothR) {
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"456\n", "123\n"};

    auto foo = std::make_shared<conflict>(lines, 0);
    auto conf = std::make_shared<conflictBothR>(*foo);

    ASSERT_EQ(conf->getNewLines(), newlines);
}

TEST(ConflictsPolymorhpism, Revert)
{
    stringVector lines = {"<<<<<<<\n", "123\n", "=======\n", "456\n",  ">>>>>>>\n"};
    stringVector newlines = {"456\n", "123\n"};

    auto foo = std::make_shared<conflict>(lines, 0);
    auto conf = std::make_shared<conflictBothR>(*foo);

    ASSERT_EQ(conf->getNewLines(), newlines);


    foo = std::make_shared<conflict>(*conf);

    ASSERT_EQ(foo->getNewLines(), lines);
}