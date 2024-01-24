#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "unique_ptr.h"
#include "unique_ptr.h" // check include guards

SCENARIO("UniquePtr Constructors", "[UniquePtr]") {
  SECTION("Default Constructor") {
    UniquePtr<int> ptr;
    CHECK(ptr.Get() == nullptr);
  }

  SECTION("Constructor from C pointer") {
    int *p = new int(5);
    UniquePtr<int> ptr(p);

    CHECK(ptr.Get() == p);
  }

  SECTION("Move Constructor") {
    UniquePtr<int> ptr1(new int(5));
    UniquePtr<int> ptr2(std::move(ptr1));

    CHECK(ptr1.Get() == nullptr);
    CHECK(ptr2.Get() != nullptr);
    CHECK(std::is_nothrow_move_constructible_v<UniquePtr<int>>);
  }

  SECTION("Destructor") {
    int *p = new int(5);

    {
      UniquePtr<int> ptr(p);
    }

    CHECK(*p != 5);
  }

  SECTION("Copy constructor delete") {
    STATIC_REQUIRE(std::is_copy_constructible<UniquePtr<int>>::value == false);
  }
}

SCENARIO("Assignment", "[UniquePtr]") {
  SECTION("Copy assignment delete") {
    STATIC_REQUIRE(std::is_copy_assignable<UniquePtr<int>>::value == false);
  }

  SECTION("Move assignment transfer the ownership") {
    int *c_ptr = new int(7);

    UniquePtr<int> ptr1(new int(5));
    UniquePtr<int> ptr2(c_ptr);

    ptr2 = std::move(ptr1);

    CHECK(ptr1.Get() == nullptr);
    CHECK(ptr2.Get() != nullptr);
    CHECK(*c_ptr != 7);

    CHECK(std::is_move_assignable<UniquePtr<int>>::value);
    CHECK(std::is_nothrow_move_assignable_v<UniquePtr<int>>);
  }
}

SCENARIO("Methods", "[UniquePtr]") {
  SECTION("Release") {
    UniquePtr<int> ptr(new int(5));
    int *p = ptr.Release();

    CHECK(ptr.Get() == nullptr);
    CHECK(*p == 5);
  }

  SECTION("Reset") {
    UniquePtr<int> ptr(new int(5));
    ptr.Reset(new int(10));

    CHECK(*ptr == 10);
  }

  SECTION("Reset") {
    UniquePtr<int> ptr1(new int(5));
    UniquePtr<int> ptr2(new int(10));

    ptr1.Swap(ptr2);

    CHECK(*ptr1 == 10);
    CHECK(*ptr2 == 5);
  }
}

SCENARIO("Operators", "[UniquePtr]") {
  SECTION("Dereference") {
    UniquePtr<int> ptr(new int(5));
    CHECK(*ptr == 5);
  }

  SECTION("Arrow") {
    struct TestStruct {
      int value;
      void SetValue(int val) {
        value = val;
      }
    };

    UniquePtr<TestStruct> ptr(new TestStruct{5});
    ptr->SetValue(10);

    CHECK(ptr->value == 10);
  }

  SECTION("Bool operator") {
    UniquePtr<int> ptr;
    CHECK(!ptr);

    ptr.Reset(new int(5));
    CHECK(ptr);
  }
}
