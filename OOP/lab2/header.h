#pragma once

#include <memory>
#include <stdexcept>

using ld = long double;

namespace nstu {

const ld pi = 3.14159265358979;

inline ld randNum() {
  ld r;
  do {
    r = static_cast<ld>(rand()) / RAND_MAX;
  } while (r == 0 || r == 1);
  return r;
}

class vector {
 private:
  std::unique_ptr<ld[]> data;
  uint32_t length;
  uint32_t full_length;
  // ========== Vector Iterator =========
  class VectorIterator {
   private:
    ld* ptr;

   public:
    using iterator_category = std::random_access_iterator_tag;
    explicit VectorIterator(ld* p) : ptr(p) {}

    ld& operator*() const { return *ptr; }
    ld* operator->() { return ptr; }

    VectorIterator& operator++() {
      ++ptr;
      return *this;
    }

    VectorIterator operator++(int) {
      VectorIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    VectorIterator& operator--() {
      --ptr;
      return *this;
    }

    VectorIterator operator--(int) {
      VectorIterator tmp = *this;
      --(*this);
      return tmp;
    }

    VectorIterator operator+(int i) const { return VectorIterator(ptr + i); }
    VectorIterator operator-(int i) const { return VectorIterator(ptr - i); }

    friend bool operator==(const VectorIterator& a, const VectorIterator& b) {
      return a.ptr == b.ptr;
    }
    friend bool operator!=(const VectorIterator& a, const VectorIterator& b) {
      return a.ptr != b.ptr;
    }
  };

  class ConstVectorIterator {
   private:
    ld* ptr;

   public:
    using iterator_category = std::random_access_iterator_tag;
    explicit ConstVectorIterator(ld* p) : ptr(p) {}

    const ld operator*() const { return *ptr; }
    const ld* operator->() { return ptr; }

    ConstVectorIterator& operator++() {
      ++ptr;
      return *this;
    }

    ConstVectorIterator operator++(int) {
      ConstVectorIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    ConstVectorIterator& operator--() {
      --ptr;
      return *this;
    }

    ConstVectorIterator operator--(int) {
      ConstVectorIterator tmp = *this;
      --(*this);
      return tmp;
    }

    ConstVectorIterator operator+(int i) const {
      return ConstVectorIterator(ptr + i);
    }
    ConstVectorIterator operator-(int i) const {
      return ConstVectorIterator(ptr - i);
    }

    friend bool operator==(const ConstVectorIterator& a,
                           const ConstVectorIterator& b) {
      return a.ptr == b.ptr;
    }
    friend bool operator!=(const ConstVectorIterator& a,
                           const ConstVectorIterator& b) {
      return a.ptr != b.ptr;
    }
  };
  // ===================================
 public:
  using iterator = VectorIterator;
  using const_iterator = ConstVectorIterator;

  explicit vector() : length(0), full_length(1) {
    data = std::unique_ptr<ld[]>(new ld[full_length]);
    if (!data) throw std::bad_alloc();
  }

  explicit vector(uint32_t length, ld value = 0) : full_length(length * 2) {
    this->length = length;
    data = std::unique_ptr<ld[]>(new ld[full_length]);
    if (!data) throw std::bad_alloc();
    if (value != 0) std::fill(data.get(), data.get() + length, value);
  }

  vector(std::initializer_list<ld> list)
      : length(list.size()), full_length(list.size() * 2) {
    data = std::unique_ptr<ld[]>(new ld[full_length]);
    if (!data) throw std::bad_alloc();
    std::copy(list.begin(), list.end(), data.get());
  }

  vector(const vector& other)
      : length(other.length), full_length(other.full_length) {
    data = std::unique_ptr<ld[]>(new ld[full_length]);
    if (!data) throw std::bad_alloc();
    std::copy(other.data.get(), other.data.get() + other.length, data.get());
  }

  vector& operator=(const vector& other) {
    if (this != &other) {
      length = other.length;
      full_length = other.full_length;
      data = std::unique_ptr<ld[]>(new ld[full_length]);
      if (!data) throw std::bad_alloc();
      std::copy(other.data.get(), other.data.get() + other.length, data.get());
    }
    return *this;
  }

  vector(vector&& other) noexcept
      : data(std::move(other.data)),
        length(other.length),
        full_length(other.full_length) {
    other.length = 0;
    other.full_length = 0;
  }

  vector& operator=(vector&& other) noexcept {
    if (this != &other) {
      data = std::move(other.data);
      length = other.length;
      full_length = other.full_length;
      other.length = 0;
      other.full_length = 0;
    }
    return *this;
  }

  uint32_t size() const noexcept { return length; }
  uint32_t capacity() const noexcept { return full_length; }
  bool empty() const noexcept { return length == 0; }

  const ld operator[](uint32_t i) const {
    if (i >= length) throw std::out_of_range("Выход за границы массива");
    return data.get()[i];
  }

  ld& operator[](uint32_t i) {
    if (i >= length) throw std::out_of_range("Выход за границы массива");
    return data.get()[i];
  }

  void push_back(ld value) {
    if (length >= full_length) {
      full_length *= 2;
      std::unique_ptr<ld[]> new_data(new ld[full_length]);
      if (!new_data) throw std::bad_alloc();
      std::copy(data.get(), data.get() + length, new_data.get());
      data = std::move(new_data);
    }
    data.get()[length++] = value;
  }

  void pop_back() {
    if (length == 0) throw std::out_of_range("Вектор пустой");
    --length;
  }

  ld pop() {
    if (length == 0) throw std::out_of_range("Вектор пустой");
    return data.get()[--length];
  }

  iterator begin() noexcept { return iterator(data.get()); }
  iterator end() noexcept { return iterator(data.get() + length); }
  const_iterator begin() const noexcept { return const_iterator(data.get()); }
  const_iterator end() const noexcept {
    return const_iterator(data.get() + length);
  }

  ~vector() {}
};

}  // namespace nstu