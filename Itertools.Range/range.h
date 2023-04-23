#ifndef OOP_ASSIGNMENTS_ITERTOOLS_RANGE_RANGE_H_
#define OOP_ASSIGNMENTS_ITERTOOLS_RANGE_RANGE_H_
#define REVERSE_RANGE_IMPLEMENTED

#include <iostream>

class RangeObj {
 private:
  int start_;
  int finish_;
  int size_;
  int step_;

 public:
  // Constructors of Range Object
  RangeObj() = default;

  RangeObj(int start, int finish, int size, int step) : start_(start), finish_(finish), size_(size), step_(step) {
  }

  class Iterator {
   private:
    int curr_;
    int step_;

   public:
    // Getters
    int GetCurr() const {
      return curr_;
    }

    int GetStep() const {
      return step_;
    }

    // Constructors
    Iterator(int curr, int step) : curr_(curr), step_(step) {
    }

    Iterator(const Iterator &other) = default;

    // Operators overloading
    Iterator &operator++() {
      curr_ += step_;
      return *this;
    }

    Iterator operator++(int) {
      int copy = curr_;
      curr_ += step_;
      return Iterator(copy, step_);
    }

    int *operator->() {
      return &curr_;
    }

    int &operator*() {
      return curr_;
    }
  };

  class RIterator {
   private:
    int curr_;
    int step_;

   public:
    // Getters
    int GetCurr() const {
      return curr_;
    }

    int GetStep() const {
      return step_;
    }

    // Constructors
    RIterator(int curr, int step) : curr_(curr), step_(step) {
    }

    RIterator(const RIterator &other) = default;

    // Operators overloading
    RIterator &operator++() {
      curr_ -= step_;
      return *this;
    }

    RIterator operator++(int) {
      int copy = curr_;
      curr_ -= step_;
      return RIterator(copy, step_);
    }

    int *operator->() {
      return &curr_;
    }

    int &operator*() {
      return curr_;
    }
  };

  // Methods of Range Object
  Iterator begin() const {  // NOLINT
    return Iterator(start_, step_);
  }

  Iterator end() const {  // NOLINT
    return Iterator(start_ + size_ * step_, step_);
  }

  RIterator rbegin() const {  // NOLINT
    return RIterator(start_ + (size_ - 1) * step_, step_);
  }

  RIterator rend() const {  // NOLINT
    return RIterator(start_ - step_, step_);
  }
};

inline RangeObj Range(int start, int end, int step = 1) {
  if (step == 0 || start == end) {
    return RangeObj(0, 0, 0, 0);
  }

  if ((step > 0) == (start < end)) {
    int size = (end - start) / step + ((end - start) % step != 0);
    return RangeObj(start, end, size, step);
  }

  return RangeObj(0, 0, 0, 0);
}

inline RangeObj Range(int end) {
  return RangeObj(0, end, (end < 0 ? 0 : end), 1);
}

// Operators overloading
inline bool operator==(const RangeObj::Iterator &first, const RangeObj::Iterator &second) {
  return first.GetCurr() == second.GetCurr();
}

inline bool operator!=(const RangeObj::Iterator &first, const RangeObj::Iterator &second) {
  return first.GetCurr() != second.GetCurr();
}

inline bool operator==(const RangeObj::RIterator &first, const RangeObj::RIterator &second) {
  return first.GetCurr() == second.GetCurr();
}

inline bool operator!=(const RangeObj::RIterator &first, const RangeObj::RIterator &second) {
  return first.GetCurr() != second.GetCurr();
}
#endif  // OOP_ASSIGNMENTS_ITERTOOLS_RANGE_RANGE_H_
