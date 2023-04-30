#include "gtest/gtest.h"

#include "../UniquePtr.hpp"

TEST(UniquePtrTest, Constructor) {
  UniquePtr<int> up(new int(42));
  EXPECT_EQ(*up, 42);
}

TEST(UniquePtrTest, MoveConstructor) {
  UniquePtr<int> up(new int(42));
  UniquePtr<int> up2(std::move(up));
  EXPECT_EQ(*up2, 42);
}

TEST(UniquePtrTest, MoveAssignment) {
  UniquePtr<int> up(new int(42));
  UniquePtr<int> up2;
  up2 = std::move(up);
  EXPECT_EQ(*up2, 42);
}

TEST(UniquePtrTest, Release) {
  UniquePtr<int> up(new int(42));
  int* raw_ptr = up.release();
  EXPECT_EQ(*raw_ptr, 42);
  delete raw_ptr;
}

TEST(UniquePtrTest, Reset) {
  UniquePtr<int> up(new int(42));
  up.reset(new int(43));
  EXPECT_EQ(*up, 43);
}

TEST(UniquePtrTest, Swap) {
  UniquePtr<int> up1(new int(42));
  UniquePtr<int> up2(new int(43));
  up1.swap(up2);
  EXPECT_EQ(*up1, 43);
  EXPECT_EQ(*up2, 42);
}
TEST(UniquePtrTest, NullPtrConstructor) {
  UniquePtr<int> up(nullptr);
  EXPECT_FALSE(up);
}

TEST(UniquePtrTest, ReleaseNullptr) {
  UniquePtr<int> up;
  int* raw_ptr = up.release();
  EXPECT_EQ(raw_ptr, nullptr);
}

TEST(UniquePtrTest, ResetNullptr) {
  UniquePtr<int> up(new int(42));
  up.reset(nullptr);
  EXPECT_FALSE(up);
}

TEST(UniquePtrTest, CopyConstructorIsDeleted) {
  EXPECT_FALSE(std::is_copy_constructible_v<UniquePtr<int>>);
}
TEST(UniquePtrTest, CopyAssignableIsDeleted) {
  EXPECT_FALSE(std::is_copy_assignable_v<UniquePtr<int>>);
}

// Test case for testing the Arrow Operator overload.
TEST(UniquePtrTest, ArrowOperator) {
    UniquePtr<int> up;
    UniquePtr<std::string> up2;

    up.reset(new int(42));
    EXPECT_EQ(*up.operator->(), 42);

    up2.reset(new std::string("Hello, world!"));
    EXPECT_EQ(*up2.operator->(), "Hello, world!");
}
#if 0
TEST(UniquePtrTest, ArrowOperator) {
  struct MyStruct {
    int value;
    void func() {}
  };
  UniquePtr<MyStruct> up(new MyStruct{42});
  EXPECT_EQ(up->value, 42);
  up->func();
}

TEST(UniquePtrTest, DereferenceOperator) {
  UniquePtr<int> up(new int(42));
  EXPECT_EQ(*up, 42);
  *up = 43;
  EXPECT_EQ(*up, 43);
}


#endif