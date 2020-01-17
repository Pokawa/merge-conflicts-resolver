//
// Created by hubert on 1/17/20.
//

#include "gtest/gtest.h"

//int main(int argc, char**argv)
//{
//    testing::InitGoogleTest(&argc, argv);
//    RUN_ALL_TESTS();
//    return 0;
//}

TEST(SomeKindOfTest, good){
    ASSERT_EQ(1,1);
}

TEST(SomeKindOfTest, bad){
    ASSERT_EQ(1,2);
}