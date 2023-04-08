#ifndef SHARED_PTR__SHARED_PTR_H_
#define SHARED_PTR__SHARED_PTR_H_
#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

struct Count {
  size_t strong_counter = 0;
  size_t weak_counter = 0;
};

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
 public:
  // Constructors
  SharedPtr() = default;

  explicit SharedPtr(T *other) : ptr_(other), counter_(other != nullptr ? new Count{1} : nullptr) {
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_ != nullptr) {
      ++counter_->strong_counter;
    }
  }

  SharedPtr(SharedPtr &&other) noexcept: ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  explicit SharedPtr(const WeakPtr<T> &other) {
    if(other.Expired()){
      throw BadWeakPtr{};
    }

    counter_ = other.counter_;
    ++counter_->strong_counter;
    ptr_ = other.ptr_;
  }

  ~SharedPtr() {
    Reset();
  }

  // Operators overloading
  SharedPtr &operator=(const SharedPtr &other) {
    if (ptr_ != other.ptr_) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;

      if (ptr_ != nullptr) {
        ++counter_->strong_counter;
      }
    }

    return *this;
  }

  SharedPtr &operator=(SharedPtr &&other) noexcept {
    if (ptr_ != other.ptr_) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }

    return *this;
  }

  T &operator*() const noexcept {
    return *ptr_;
  }

  T *operator->() const noexcept {
    return ptr_;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }

  // Methods
  void Reset(T *other = nullptr) {
    if (counter_ != nullptr) {
      --counter_->strong_counter;

      if (counter_->strong_counter == 0) {
        delete ptr_;

        if (counter_->weak_counter == 0) {
          delete counter_;
        }
      }
    }

    ptr_ = other;
    counter_ = nullptr;

    if (ptr_ != nullptr) {
      counter_ = new Count{1};
    }
  }

  T *Get() const {
    return ptr_;
  }

  Count *GetCounter() const {
    return counter_;
  }

  size_t UseCount() const {
    return (counter_ != nullptr ? counter_->strong_counter : 0);
  }

  void Swap(SharedPtr<T> &other) {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->counter_, other.counter_);
  }

 private:
  T *ptr_ = nullptr;
  Count *counter_ = nullptr;

  void Copy(SharedPtr &&other) {
    ptr_ = other.ptr_;
    counter_ = other.counter_;

    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }
};
#endif
