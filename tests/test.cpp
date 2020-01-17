//
// Created by hubert on 1/17/20.
//

#include "gtest/gtest.h"
#include <memory>
#include "conflicts.hpp"
#include "fileHandler.hpp"
#include "parser.hpp"

//int main(int argc, char**argv)
//{
//    testing::InitGoogleTest(&argc, argv);
//    RUN_ALL_TESTS();
//    return 0;
//}

TEST(Conflicts, Polymorthism) {
    stringVector lines = {"<<<<<<<", "123", "=======", "456",  ">>>>>>>"};
    stringVector oldlines = {"123"};
    stringVector newlines = {"456"};
    stringVector bothlines = {"123", "456"};
    stringVector bothrlines = {"456", "123"};

    auto foo = std::make_shared<conflict>(lines, 0);
    ASSERT_EQ(foo->getNewLines(), lines);

    foo = std::make_shared<conflictNew>(*foo);
    ASSERT_EQ(foo->getNewLines(), newlines);

    foo = std::make_shared<conflictOld>(*foo);
    ASSERT_EQ(foo->getNewLines(), oldlines);

    foo = std::make_shared<conflictBoth>(*foo);
    ASSERT_EQ(foo->getNewLines(), bothlines);

    foo = std::make_shared<conflictBothR>(*foo);
    ASSERT_EQ(foo->getNewLines(), bothrlines);

    foo = std::make_shared<conflict>(*foo);
    ASSERT_EQ(foo->getNewLines(), lines);
}

TEST(Conflicts, PolymorthismAndColors) {
    coloredString o = {"123", textColor::YellowText};
    coloredString n = {"456", textColor::BlueText};
    stringVector lines = {"<<<<<<<", "123", "=======", "456",  ">>>>>>>"};
    coloredStringVector coloredlines = {{"<<<<<<<", textColor::RedText}, o, {"=======", textColor::RedText},
                                        n,  {">>>>>>>", textColor::RedText}};
    coloredStringVector oldlines = {o};
    coloredStringVector newlines = {n};
    coloredStringVector bothlines = {o, n};
    coloredStringVector bothrlines = {n, o};

    auto foo = std::make_shared<conflict>(lines, 0);
    ASSERT_EQ(foo->getNewLinesColored(), coloredlines);

    foo = std::make_shared<conflictNew>(*foo);
    ASSERT_EQ(foo->getNewLinesColored(), newlines);

    foo = std::make_shared<conflictOld>(*foo);
    ASSERT_EQ(foo->getNewLinesColored(), oldlines);

    foo = std::make_shared<conflictBoth>(*foo);
    ASSERT_EQ(foo->getNewLinesColored(), bothlines);

    foo = std::make_shared<conflictBothR>(*foo);
    ASSERT_EQ(foo->getNewLinesColored(), bothrlines);

    foo = std::make_shared<conflict>(*foo);
    ASSERT_EQ(foo->getNewLinesColored(), coloredlines);
}

TEST(File, WriteRead){
    stringVector lines = {"<<<<<<<", "123", "=======", "456",  ">>>>>>>"};

    writeLinesToFile(lines, "tmp");
    auto newLines = readLinesFromFile("tmp");
    remove("tmp");

    ASSERT_EQ(lines, newLines);
}

TEST(File, Parse){
    stringVector lines = {"abc", "def", "<<<<<<<", "123", "=======", "456",  ">>>>>>>", "ghi"};

    writeLinesToFile(lines, "tmp");
    auto parsed = parseConflicts(readLinesFromFile("tmp"));
    remove("tmp");

    ASSERT_EQ(parsed.conflictsSize(), 1);
    ASSERT_EQ(parsed.getLines(), lines);


    lines = {"<<<<<<<", "123", "=======", "456",  ">>>>>>>", "abc", "def", "<<<<<<<", "789", "=======", "000",  ">>>>>>>", "ghi"};

    writeLinesToFile(lines, "tmp");
    parsed = parseConflicts(readLinesFromFile("tmp"));
    remove("tmp");

    ASSERT_EQ(parsed.conflictsSize(), 2);
    ASSERT_EQ(parsed.getLines(), lines);
}

