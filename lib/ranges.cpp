#include <iostream>
#include <iterator>

template <typename T>
concept Container = requires(T container) {
  container.begin();
  container.end();
  requires std::derived_from<typename T::const_iterator::iterator_category,
                             std::forward_iterator_tag>;
};

template <typename T>
concept Pair = requires(T c) {
  typename T::first_type;
  typename T::second_type;
};

template <typename T>
class Keys {
 public:
  explicit Keys(T& container) : container(container) {}

  using value_type = typename T::value_type;

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");
  static_assert(Pair<value_type>, "Keys requires Associative Container");

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr) : ptr(ptr) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const { return (*ptr).first; }
    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
  };

  const_iterator begin() { return const_iterator(container.begin()); }
  const_iterator end() { return const_iterator(container.end()); }

 private:
  T& container;
};

template <typename T>
class Values {
 public:
  explicit Values(T& container) : container(container) {}

  using value_type = typename T::value_type;

  static_assert(Pair<value_type>, "Values requires Associative Container");
  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr) : ptr(ptr) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const { return (*ptr).second; }
    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
  };

  const_iterator begin() { return const_iterator(container.begin()); }
  const_iterator end() { return const_iterator(container.end()); }

 private:
  T& container;
};

template <typename T>
class Take {
 public:
  explicit Take(T& container_, size_t n_) : container(container_), n(n_) {}

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");

  using value_type = typename T::value_type;

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr) : ptr(ptr) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const { return *ptr; }
    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
  };

  const_iterator begin() { return const_iterator(container.begin()); }
  const_iterator end() {
    auto it = container.begin();
    for (int i = 0; i < n; ++i) {
      if (it == container.end()) {
        break;
      }
      ++it;
    }
    return const_iterator(it);
  }

 private:
  T& container;
  size_t n;
};

template <typename T>
class Drop {
 public:
  explicit Drop(T& container_, size_t n_) : container(container_), n(n_) {}

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");

  using value_type = typename T::value_type;

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr) : ptr(ptr) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const { return *ptr; }
    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
  };

  const_iterator begin() {
    auto it = container.begin();
    for (int i = 0; i < n; ++i) {
      if (it == container.end()) {
        break;
      }
      ++it;
    }
    return const_iterator(it);
  }
  const_iterator end() { return const_iterator(container.end()); }

 private:
  T& container;
  size_t n;
};

template <typename T>
class Reverse {
 public:
  explicit Reverse(T& container) : container(container) {}

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");
  static_assert(std::derived_from<typename T::const_iterator::iterator_category,
                                  std::bidirectional_iterator_tag>,
                "Reverse requires at least bidirectional iterator");

  using value_type = typename T::value_type;

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr) : ptr(ptr) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const {
      auto it = ptr;
      return *(--it);
    }
    const_iterator& operator++() {
      --ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }
    const_iterator& operator--() {
      ++ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
  };

  const_iterator begin() { return const_iterator(container.end()); }
  const_iterator end() { return const_iterator(container.begin()); }

 private:
  T& container;
};

template <typename T, typename F>
class Filter {
 public:
  explicit Filter(T& container, F f) : container(container), f(f) {}

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");

  using value_type = typename T::value_type;

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr_,
                   typename T::const_iterator begin_,
                   typename T::const_iterator end_, F f_)
        : ptr(ptr_), begin(begin_), end(end_), f(f_) {
      while (ptr != end && !f(*ptr)) {
        ++ptr;
      }
    }
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;
    auto operator*() const { return *ptr; }

    using iterator_category = typename T::const_iterator::iterator_category;

    const_iterator& operator++() {
      ++ptr;
      while (ptr != end && !f(*ptr)) {
        ++ptr;
      }
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      while (ptr != begin && !f(*ptr)) {
        --ptr;
      }
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
    typename T::const_iterator begin;
    typename T::const_iterator end;
    F f;
  };

  const_iterator begin() {
    auto it = container.begin();
    while (it != container.end() && !f(*it)) {
      ++it;
    }
    return const_iterator(it, container.begin(), container.end(), f);
  }
  const_iterator end() {
    return const_iterator(container.end(), container.begin(), container.end(),
                          f);
  }

 private:
  T& container;
  F f;
};

template <typename T, typename F>
class Transform {
 public:
  explicit Transform(T& container, F f) : container(container), f(f) {}

  static_assert(
      Container<T>,
      "Container requires begin() and end() and at least forward iterator");

  using value_type = typename T::value_type;

  class const_iterator {
   public:
    const_iterator(typename T::const_iterator ptr, F f) : ptr(ptr), f(f) {}
    const_iterator(const const_iterator&) = default;
    const_iterator& operator=(const const_iterator&) = default;

    using iterator_category = typename T::const_iterator::iterator_category;

    auto operator*() const { return f(*ptr); }

    const_iterator& operator++() {
      ++ptr;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }
    const_iterator& operator--() {
      --ptr;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      --(*this);
      return temp;
    }

    bool operator==(const const_iterator& other) const = default;
    bool operator!=(const const_iterator& other) const = default;

   private:
    typename T::const_iterator ptr;
    F f;
  };

  const_iterator begin() { return const_iterator(container.begin(), f); }
  const_iterator end() { return const_iterator(container.end(), f); }

 private:
  T& container;
  F f;
};

struct keys_buff {};

struct values_buff {};

struct take_buff {
  take_buff(size_t n) : n(n) {}
  size_t n;
};

struct drop_buff {
  drop_buff(size_t n) : n(n) {}
  size_t n;
};

struct reverse_buff {};

template <typename F>
struct filter_buff {
  filter_buff(F f) : f(f) {}
  F f;
};

template <typename F>
struct transform_buff {
  transform_buff(F f) : f(f) {}
  F f;
};

template <typename T>
Keys<T> keys(T& container) {
  return Keys<T>(container);
}

template <typename T>
Values<T> values(T& container) {
  return Values<T>(container);
}

template <typename T>
Take<T> take(T& container, size_t n) {
  return Take<T>(container, n);
}

template <typename T>
Drop<T> drop(T& container, size_t n) {
  return Drop<T>(container, n);
}

template <typename T>
Reverse<T> reverse(T& container) {
  return Reverse<T>(container);
}

template <typename T, typename F>
Filter<T, F> filter(T& container, F f) {
  return Filter<T, F>(container, f);
}

template <typename T, typename F>
Transform<T, F> transform(T& container, F f) {
  return Transform<T, F>(container, f);
}

keys_buff keys() { return keys_buff(); }

values_buff values() { return values_buff(); }

take_buff take(size_t n) { return take_buff(n); }

drop_buff drop(size_t n) { return drop_buff(n); }

reverse_buff reverse() { return reverse_buff(); }

template <typename F>
filter_buff<F> filter(F f) {
  return filter_buff<F>(f);
}

template <typename F>
transform_buff<F> transform(F f) {
  return transform_buff<F>(f);
}

template <typename T>
auto operator|(T&& r, keys_buff()) {
  return Keys<std::remove_reference_t<T>>(r);
}

template <typename T>
auto operator|(T&& r, values_buff()) {
  return Values<std::remove_reference_t<T>>(r);
}

template <typename T>
auto operator|(T&& r, take_buff b) {
  return Take<std::remove_reference_t<T>>(r, b.n);
}

template <typename T>
auto operator|(T&& r, drop_buff b) {
  return Drop<std::remove_reference_t<T>>(r, b.n);
}

template <typename T>
auto operator|(T&& r, reverse_buff()) {
  return Reverse<std::remove_reference_t<T>>(r);
}

template <typename T, typename F>
auto operator|(T&& r, filter_buff<F> b) {
  return Filter<std::remove_reference_t<T>, F>(r, b.f);
}

template <typename T, typename F>
auto operator|(T&& r, transform_buff<F> b) {
  return Transform<std::remove_reference_t<T>, F>(r, b.f);
}
