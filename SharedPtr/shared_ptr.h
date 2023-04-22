#ifndef SHARED_PTR__SHARED_PTR_H_
#define SHARED_PTR__SHARED_PTR_H_
#define WEAK_PTR_IMPLEMENTED
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

template <typename T>
class WeakPtr;

template <typename T>
class SharedPtr {
 public:
  // Constructors
  SharedPtr() = default;

  SharedPtr(T *other) : ptr_(other), counter_(other != nullptr ? new Count{1} : nullptr) {  // NOLINT
  }

  SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_ != nullptr) {
      ++counter_->strong_counter;
    }
  }

  SharedPtr(SharedPtr &&other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  explicit SharedPtr(const WeakPtr<T> &other) {
    if (other.Expired()) {
      throw BadWeakPtr{};
    }

    counter_ = other.GetCounter();
    ++counter_->strong_counter;
    ptr_ = other.Get();
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

template <class T, class... Args>
SharedPtr<T> MakeShared(Args &&... args) {
  return SharedPtr<T>{new T(std::forward<Args>(args)...)};
}

template <typename T>
class WeakPtr {
 public:
  // Constructors
  WeakPtr() = default;

  WeakPtr(const WeakPtr &other) : ptr_(other.ptr_), counter_(other.counter_) {
    if (counter_ != nullptr) {
      ++counter_->weak_counter;
    }
  }

  WeakPtr(const SharedPtr<T> &shared) : ptr_(shared.Get()), counter_(shared.GetCounter()) {  // NOLINT
    if (counter_ != nullptr) {
      ++counter_->weak_counter;
    }
  }

  WeakPtr(WeakPtr &&other) noexcept : ptr_(other.ptr_), counter_(other.counter_) {
    other.ptr_ = nullptr;
    other.counter_ = nullptr;
  }

  ~WeakPtr() {
    Reset();
  }

  // Operators overloading
  WeakPtr &operator=(const WeakPtr &other) {
    if (ptr_ != other.ptr_) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;

      if (ptr_ != nullptr) {
        ++counter_->weak_counter;
      }
    }

    return *this;
  }

  WeakPtr &operator=(WeakPtr &&other) noexcept {
    if (ptr_ != other.ptr_) {
      Reset();
      ptr_ = other.ptr_;
      counter_ = other.counter_;
      other.ptr_ = nullptr;
      other.counter_ = nullptr;
    }
  }

  WeakPtr &operator=(const SharedPtr<T> &other) {
    if (ptr_ != other.Get()) {
      Reset();
      ptr_ = other.Get();
      counter_ = other.GetCounter();

      if (ptr_ != nullptr) {
        ++counter_->weak_counter;
      }
    }

    return *this;
  }

  // Methods
  void Swap(WeakPtr<T> &other) {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->counter_, other.counter_);
  }

  void Reset() {
    if (counter_ != nullptr) {
      --counter_->weak_counter;

      if (counter_->strong_counter == 0 && counter_->weak_counter == 0) {
        delete counter_;
      }

      counter_ = nullptr;
      ptr_ = nullptr;
    }
  }

  size_t UseCount() const {
    return (counter_ != nullptr ? counter_->strong_counter : 0);
  }

  bool Expired() const {
    return (UseCount() == 0);
  }

  SharedPtr<T> Lock() const {
    return (Expired() ? nullptr : SharedPtr<T>(*this));
  }

  T *Get() const {
    return ptr_;
  }

  Count *GetCounter() const {
    return counter_;
  }

 private:
  T *ptr_ = nullptr;
  Count *counter_ = nullptr;
};
#endif
