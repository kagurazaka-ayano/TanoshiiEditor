#include <gtest/gtest.h>
#include "Buffer.h"

TEST(bufferTest, calculateWrappedLineTest) {
    auto splitted = Buffer::split("Labore sit deserunt non nisi", " ");
    EXPECT_EQ(splitted[0], "Labore");
    EXPECT_EQ(splitted[1], "sit");
    EXPECT_EQ(splitted[2], "deserunt");
    EXPECT_EQ(splitted[3], "non");
    EXPECT_EQ(splitted[4], "nisi");
}
