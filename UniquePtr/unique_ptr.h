#ifndef UNIQUE_PTR_H_
#define UNIQUE_PTR_H_

template <typename T>
class UniquePtr {
 private:
  T *pointer_;

 public:
  // Constructors
  UniquePtr() : pointer_(nullptr) {
  }

  explicit UniquePtr(T *ptr) : pointer_(ptr) {
  }

  UniquePtr(const UniquePtr<T> &other) = delete;

  UniquePtr(UniquePtr &&other) noexcept : pointer_(other.pointer_) {
    other.pointer_ = nullptr;
  }

  ~UniquePtr() {
    delete pointer_;
  }

  // Operators overloading
  UniquePtr &operator=(const UniquePtr<T> &other) = delete;

  UniquePtr &operator=(UniquePtr &&other) noexcept {
    Reset(other.pointer_);
    other.pointer_ = nullptr;
    return *this;
  }

  T &operator*() const {
    return *pointer_;
  }

  T *operator->() const {
    return pointer_;
  }

  explicit operator bool() const {
    return (pointer_ != nullptr);
  }

  // Methods
  T *Release() {
    T *ptr = pointer_;
    pointer_ = nullptr;
    return ptr;
  }

  void Reset(T *ptr = nullptr) {
    if (ptr != pointer_) {
      delete pointer_;
      pointer_ = ptr;
    }
  }

  void Swap(UniquePtr<T> &other) {
    std::swap(this->pointer_, other.pointer_);
  }

  T *Get() const {
    return pointer_;
  }
};
#endif