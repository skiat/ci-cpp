#include "header.h"
#include <gmock/gmock.h>


using namespace ::testing;

TEST(Basic, Initial) {
    int a {0};
    ASSERT_THAT(a, 0);
}

TEST(Basic, Sum) {
    ASSERT_EQ(5, sum(3, 2));
}
