#include <cassert>
#include <iostream>
#include "unique_ptr.h"

void TestDefaultConstructor() {
  UniquePtr<int> ptr;
  assert(ptr.Get() == nullptr);
}

void TestConstructorWithPointer() {
  int *p = new int(5);
  UniquePtr<int> ptr(p);
  assert(ptr.Get() == p);
}

void TestMoveConstructor() {
  UniquePtr<int> ptr1(new int(5));
  UniquePtr<int> ptr2(std::move(ptr1));
  assert(ptr1.Get() == nullptr);
  assert(ptr2.Get() != nullptr);
  assert(std::is_nothrow_move_constructible_v<UniquePtr<int>>);
}

void TestDestructor() {
  int *p = new int(5);
  {
    UniquePtr<int> ptr(p);
  }
  assert(*p != 5);
}

void TestMoveAssignmentOperator() {
  UniquePtr<int> ptr1(new int(5));
  UniquePtr<int> ptr2;
  ptr2 = std::move(ptr1);
  assert(ptr1.Get() == nullptr);
  assert(ptr2.Get() != nullptr);
}

void TestDereferenceOperator() {
  UniquePtr<int> ptr(new int(5));
  assert(*ptr == 5);
}

void TestArrowOperator() {
  struct TestStruct {
    int value;
    void SetValue(int val) {
      value = val;
    }
  };
  UniquePtr<TestStruct> ptr(new TestStruct{5});
  ptr->SetValue(10);
  assert(ptr->value == 10);
}

void TestBoolOperator() {
  UniquePtr<int> ptr;
  assert(!ptr);
  ptr.Reset(new int(5));
  assert(ptr);
}

void TestReleaseMethod() {
  UniquePtr<int> ptr(new int(5));
  int *p = ptr.Release();
  assert(ptr.Get() == nullptr);
  assert(*p == 5);
}

void TestResetMethod() {
  UniquePtr<int> ptr(new int(5));
  ptr.Reset(new int(10));
  assert(*ptr == 10);
}

void TestSwapMethod() {
  UniquePtr<int> ptr1(new int(5));
  UniquePtr<int> ptr2(new int(10));
  ptr1.Swap(ptr2);
  assert(*ptr1 == 10);
  assert(*ptr2 == 5);
}

int main() {
  TestDefaultConstructor();
  TestConstructorWithPointer();
  TestMoveConstructor();
  TestDestructor();
  TestMoveAssignmentOperator();
  TestDereferenceOperator();
  TestArrowOperator();
  TestBoolOperator();
  TestReleaseMethod();
  TestResetMethod();
  TestSwapMethod();

  std::cout << "All tests passed" << '\n';
  return 0;
}
