export module Collections.List;
import std;
export import Collections.Base;

template <typename T>
class ListEnumerator : public IEnumerator<T> {
  std::vector<T>::const_iterator current_it, end_it;
  bool started = false;
public:
  ListEnumerator(auto b, auto e) : current_it(b), end_it(e) {}
  bool move_next() override {
    if (!started) started = true;
    else if (current_it != end_it) ++current_it;
    return current_it != end_it;
  }
  T current() const override {
    if (!started || current_it == end_it) throw InvalidOperationException("За пределами границ");
    return *current_it;
  }
};

export template <typename T>
class List : public ICollection<T> {
  std::vector<T> data;
public:
  void add(const T& item) override { data.push_back(item); }
  void clear() override { data.clear(); }
  int count() const override { return static_cast<int>(data.size()); }
  bool contains(const T& item) const override { return std::find(data.begin(), data.end(), item) != data.end(); }
  bool remove(const T& item) override {
    auto it = std::find(data.begin(), data.end(), item);
    if (it == data.end()) return false;
    data.erase(it); 
    return true;
  }

  T& operator[](int index) {
    if (index < 0 || index >= count()) {
      throw InvalidOperationException("Индекс находится за пределами границ списка");
    }
    return data[index];
  }

  const T& operator[](int index) const {
    if (index < 0 || index >= count()) {
      throw InvalidOperationException("Индекс находится за пределами границ списка");
    }
    return data[index];
  }
  std::shared_ptr<IEnumerator<T>> get_enumerator() const override {
    return std::make_shared<ListEnumerator<T>>(data.begin(), data.end());
  }
};
