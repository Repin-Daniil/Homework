#include "string_view.h"

StringView::StringView(const char *str) : data_(str) {  // NOLINT
  while (*str) {
    ++size_;
    ++str;
  }
}

StringView::StringView(const char *str, size_t size) : data_(str), size_(size) {
}

// Operators overloading
const char &StringView::operator[](size_t index) const {
  return data_[index];
}

// Methods
const char &StringView::At(size_t index) const {
  if (index >= size_) {
    throw StringViewOutOfRange{};
  }

  return data_[index];
}

const char &StringView::Front() const {
  return *data_;
}

const char &StringView::Back() const {
  return *(data_ + size_ - 1);
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return (size_ == 0);
}

const char *StringView::Data() const {
  return data_;
}

void StringView::Swap(StringView &other) {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  data_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  if (pos + std::min(count, Size() - pos) > Size()) {
    throw StringViewOutOfRange{};
  }

  return StringView(data_ + pos, std::min(count, Size() - pos));
}
