#ifndef ARRAY__ARRAY_H_
#define ARRAY__ARRAY_H_
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template<typename T, size_t N>
class Array {
 public:
  T arr[N];

  // Operators overloading
  T &operator[](size_t index) {
    return arr[index];
  }

  const T &operator[](size_t index) const {
    return arr[index];
  }

  // Methods
  T &At(size_t idx) {
    if (idx < N) {
      return arr[idx];
    }

    throw ArrayOutOfRange{};
  }

  const T &At(size_t idx) const {
    if (idx < N) {
      return arr[idx];
    }

    throw ArrayOutOfRange{};
  }

  T &Front() {
    return arr[0];
  }

  const T &Front() const {
    return arr[0];
  }

  T &Back() {
    return arr[N - 1];
  }

  const T &Back() const {
    return arr[N - 1];
  }

  T *Data() {
    return arr;
  }

  const T *Data() const {
    return arr;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return (N == 0);
  }

  void Fill(const T &value) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = value;
    }
  }

  void Swap(Array<T, N> &other) {
    std::swap(*this, other);
  }
};
#endif
