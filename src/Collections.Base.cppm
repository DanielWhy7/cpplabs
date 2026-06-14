export module Collections.Base;
import std;

export class InvalidOperationException : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

export template <typename T>
class IEnumerator {
public:
  virtual ~IEnumerator() = default;
  virtual bool move_next() = 0;
  virtual T current() const = 0;

protected:
  IEnumerator() = default;
  IEnumerator(const IEnumerator&) = default;
  IEnumerator& operator=(const IEnumerator&) = default;
};

export template <typename T>
class IEnumerable {
public:
  virtual ~IEnumerable() = default;
  virtual std::shared_ptr<IEnumerator<T>> get_enumerator() const = 0;

protected:
  IEnumerable() = default;
  IEnumerable(const IEnumerable&) = default;
  IEnumerable& operator=(const IEnumerable&) = default;
};

export template <typename T>
class ICollection : public IEnumerable<T> {
public:
  virtual int count() const = 0;
  virtual void add(const T& item) = 0;
  virtual void clear() = 0;
  virtual bool contains(const T& item) const = 0;
  virtual bool remove(const T& item) = 0;
};
