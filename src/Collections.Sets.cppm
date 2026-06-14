export module Collections.Sets;
import std;
export import Collections.Base;

template <typename T, typename Hash, typename Eq>
class HashSetEnumerator : public IEnumerator<T> {
  typename std::unordered_set<T, Hash, Eq>::const_iterator current_it, end_it;
  bool is_started = false;
public:
  HashSetEnumerator(auto b, auto e) : current_it(b), end_it(e) {}

  bool move_next() override {
    if (!is_started) {
      is_started = true;
    }
    else if (current_it != end_it) {
      ++current_it;
    }
    return current_it != end_it;
  }

  T current() const override {
    if (!is_started || current_it == end_it) {
      throw InvalidOperationException("За пределами границ множества");
    }
    return *current_it;
  }
};

template <typename K, typename V>
class DictionaryEnumerator : public IEnumerator<std::pair<K, V>> {
  typename std::unordered_map<K, V>::const_iterator current_it, end_it;
  bool is_started = false;
public:
  DictionaryEnumerator(auto b, auto e) : current_it(b), end_it(e) {}

  bool move_next() override {
    if (!is_started) {
      is_started = true;
    }
    else if (current_it != end_it) {
      ++current_it;
    }
    return current_it != end_it;
  }

  std::pair<K, V> current() const override {
    if (!is_started || current_it == end_it) {
      throw InvalidOperationException("За пределами границ словаря");
    }
    return { current_it->first, current_it->second };
  }
};

export template <typename T, typename Hash = std::hash<T>, typename Eq = std::equal_to<T>>
class HashSet : public ICollection<T> {
  std::unordered_set<T, Hash, Eq> data;
public:
  void add(const T& item) override { data.insert(item); }
  void clear() override { data.clear(); }
  int count() const override { return static_cast<int>(data.size()); }
  bool contains(const T& item) const override { return data.contains(item); }
  bool remove(const T& item) override { return data.erase(item) > 0; }
  
  int capacity() const { return static_cast<int>(data.bucket_count()); }
  void set_capacity(int cap) { data.rehash(cap); }

  std::shared_ptr<IEnumerator<T>> get_enumerator() const override {
    return std::make_shared<HashSetEnumerator<T, Hash, Eq>>(data.begin(), data.end());
  }
};

export template <typename K, typename V>
class Dictionary : public ICollection<std::pair<K, V>> {
  std::unordered_map<K, V> data;
public:
  void add(const std::pair<K, V>& item) override { data.insert(item); }
  void clear() override { data.clear(); }
  int count() const override { return static_cast<int>(data.size()); }
  bool contains(const std::pair<K, V>& item) const override { return data.contains(item.first); }
  bool remove(const std::pair<K, V>& item) override { return data.erase(item.first) > 0; }

  V& operator[](const K& key) { return data[key]; }

  std::shared_ptr<IEnumerator<std::pair<K, V>>> get_enumerator() const override {
    return std::make_shared<DictionaryEnumerator<K, V>>(data.begin(), data.end());
  }
};
