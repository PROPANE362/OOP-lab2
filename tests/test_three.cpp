#include <gtest/gtest.h>
#include "Three.h"
#include <stdexcept>

TEST(ThreeTest, DefaultCtor) {
    Three n;
    EXPECT_EQ(n.toString(), "0");
    EXPECT_EQ(n.size(), 1);
}

TEST(ThreeTest, SizeCtor) {
    Three n(3, 1);
    EXPECT_EQ(n.toString(), "111");
    EXPECT_EQ(n.size(), 3);
}

TEST(ThreeTest, SizeCtorZero) {
    Three n(0, 1);
    EXPECT_EQ(n.toString(), "0");
}

TEST(ThreeTest, SizeCtorInvalid) {
    EXPECT_THROW(Three(3, 5), std::invalid_argument);
}

TEST(ThreeTest, InitListCtor) {
    Three n{2, 1, 0};
    EXPECT_EQ(n.toString(), "12");
}

TEST(ThreeTest, InitListCtorInvalid) {
    EXPECT_THROW(Three({3, 1, 0}), std::invalid_argument);
}

TEST(ThreeTest, StringCtor) {
    Three n("210");
    EXPECT_EQ(n.toString(), "210");
}

TEST(ThreeTest, StringCtorEmpty) {
    Three n("");
    EXPECT_EQ(n.toString(), "0");
}

TEST(ThreeTest, StringCtorInvalid) {
    EXPECT_THROW(Three("345"), std::invalid_argument);
}

TEST(ThreeTest, CopyCtor) {
    Three a("120");
    Three b(a);
    EXPECT_EQ(b.toString(), "120");
    EXPECT_TRUE(a.isEqual(b));
}

TEST(ThreeTest, MoveCtor) {
    Three a("120");
    Three b(std::move(a));
    EXPECT_EQ(b.toString(), "120");
}

TEST(ThreeTest, AddSimple) {
    Three a("11");
    Three b("11");
    Three c = a.add(b);
    EXPECT_EQ(c.toString(), "22");
}

TEST(ThreeTest, AddWithCarry) {
    Three a("22");
    Three b("11");
    Three c = a.add(b);
    EXPECT_EQ(c.toString(), "110");
}

TEST(ThreeTest, AddDiffLen) {
    Three a("200");
    Three b("1");
    Three c = a.add(b);
    EXPECT_EQ(c.toString(), "201");
}

TEST(ThreeTest, SubtractSimple) {
    Three a("22");
    Three b("11");
    Three c = a.subtract(b);
    EXPECT_EQ(c.toString(), "11");
}

TEST(ThreeTest, SubtractWithBorrow) {
    Three a("110");
    Three b("22");
    Three c = a.subtract(b);
    EXPECT_EQ(c.toString(), "11");
}

TEST(ThreeTest, SubtractToZero) {
    Three a("120");
    Three b("120");
    Three c = a.subtract(b);
    EXPECT_EQ(c.toString(), "0");
}

TEST(ThreeTest, SubtractNegative) {
    Three a("11");
    Three b("22");
    EXPECT_THROW(a.subtract(b), std::underflow_error);
}

TEST(ThreeTest, Copy) {
    Three a("210");
    Three b = a.copy();
    EXPECT_EQ(b.toString(), "210");
    EXPECT_TRUE(a.isEqual(b));
}

TEST(ThreeTest, IsEqual) {
    Three a("120");
    Three b("120");
    Three c("121");
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_FALSE(a.isEqual(c));
}

TEST(ThreeTest, IsGreater) {
    Three a("200");
    Three b("12");
    Three c("200");
    EXPECT_TRUE(a.isGreater(b));
    EXPECT_FALSE(b.isGreater(a));
    EXPECT_FALSE(a.isGreater(c));
}

TEST(ThreeTest, IsLess) {
    Three a("12");
    Three b("200");
    Three c("12");
    EXPECT_TRUE(a.isLess(b));
    EXPECT_FALSE(b.isLess(a));
    EXPECT_FALSE(a.isLess(c));
}

TEST(ThreeTest, ZeroEquals) {
    Three a;
    Three b("0");
    Three c{0};
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_TRUE(a.isEqual(c));
}

TEST(ThreeTest, LargeNumbers) {
    Three a("222222222");
    Three b("111111111");
    Three sum = a.add(b);
    EXPECT_EQ(sum.toString(), "1111111110");
}

TEST(ThreeTest, Immutability) {
    Three a("120");
    Three b("11");
    std::string orig = a.toString();
    Three c = a.add(b);
    EXPECT_EQ(a.toString(), orig);
    Three d = a.subtract(b);
    EXPECT_EQ(a.toString(), orig);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
