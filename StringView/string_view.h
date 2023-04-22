#ifndef STRING_VIEW__STRING_VIEW_H_
#define STRING_VIEW__STRING_VIEW_H_
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
 public:
  // Constructors
  StringView() = default;
  StringView(const char *str);  // NOLINT
  StringView(const char *str, size_t size);

  // Operators overloading
  const char &operator[](size_t index) const;

  // Methods
  const char &At(size_t index) const;
  const char &Front() const;
  const char &Back() const;
  size_t Size() const;
  size_t Length() const;
  bool Empty() const;
  const char *Data() const;

  void Swap(StringView &other);
  void RemovePrefix(size_t prefix_size);
  void RemoveSuffix(size_t suffix_size);
  StringView Substr(size_t pos, size_t count = -1);

 private:
  const char *data_ = nullptr;
  size_t size_ = 0;
};
#endif
