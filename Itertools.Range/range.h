#ifndef OOP_ASSIGNMENTS_ITERTOOLS_RANGE_RANGE_H_
#define OOP_ASSIGNMENTS_ITERTOOLS_RANGE_RANGE_H_
#define REVERSE_RANGE_IMPLEMENTED

#include <iostream>

class RangeObj {
 private:
  int64_t start_;
  int64_t finish_;
  int64_t size_;
  int64_t step_;

 public:
  // Constructors of Range Object
  RangeObj() = default;

  RangeObj(int64_t start, int64_t finish, int64_t size, int64_t step)
      : start_(start), finish_(finish), size_(size), step_(step) {
  }

  class Iterator {
   private:
    int64_t curr_;
    int64_t step_;

   public:
    // Getters
    int64_t GetCurr() const {
      return curr_;
    }

    int64_t GetStep() const {
      return step_;
    }

    // Constructors
    Iterator(int64_t curr, int64_t step) : curr_(curr), step_(step) {
    }

    Iterator(const Iterator &other) = default;

    // Operators overloading
    Iterator &operator++() {
      curr_ += step_;
      return *this;
    }

    Iterator operator++(int) {
      int64_t copy = curr_;
      curr_ += step_;
      return Iterator(copy, step_);
    }

    int64_t *operator->() {
      return &curr_;
    }

    int64_t &operator*() {
      return curr_;
    }
  };

  class RIterator {
   private:
    int64_t curr_;
    int64_t step_;

   public:
    // Getters
    int64_t GetCurr() const {
      return curr_;
    }

    int64_t GetStep() const {
      return step_;
    }

    // Constructors
    RIterator(int64_t curr, int64_t step) : curr_(curr), step_(step) {
    }

    RIterator(const RIterator &other) = default;

    // Operators overloading
    RIterator &operator++() {
      curr_ -= step_;
      return *this;
    }

    RIterator operator++(int) {
      int64_t copy = curr_;
      curr_ -= step_;
      return RIterator(copy, step_);
    }

    int64_t *operator->() {
      return &curr_;
    }

    int64_t &operator*() {
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

inline RangeObj Range(int64_t start, int64_t end, int64_t step = 1) {
  int64_t size = 0;

  if (step > 0 && start < end) {
    size = (end - start) / step + ((end - start) % step != 0);
  } else if (step < 0 && start > end) {
    size = (end - start) / step + ((end - start) % step != 0);
  } else {
    return RangeObj(0, 0, 0, 0);
  }

  return RangeObj(start, end, size, step);
}

inline RangeObj Range(int64_t end) {
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
