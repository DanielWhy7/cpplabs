export module Collections.Specialized;
import std;
export import Collections.Base;

template <typename T>
class StackEnumerator : public IEnumerator<T> {
  typename std::deque<T>::const_reverse_iterator _current_it, _end_it;
  bool _is_started = false;
public:
  StackEnumerator(auto b, auto e) : _current_it(b), _end_it(e) {}

  bool move_next() override {
    if (!_is_started) {
      _is_started = true;
    }
    else if (_current_it != _end_it) {
      ++_current_it;
    }
    return _current_it != _end_it;
  }

  T current() const override {
    if (!_is_started || _current_it == _end_it) {
      throw InvalidOperationException("За пределами границ стека");
    }
    return *_current_it;
  }
};

template <typename T>
class QueueEnumerator : public IEnumerator<T> {
  typename std::deque<T>::const_iterator _current_it, _end_it;
  bool _is_started = false;
public:
  QueueEnumerator(auto b, auto e) : _current_it(b), _end_it(e) {}

  bool move_next() override {
    if (!_is_started) {
      _is_started = true;
    }
    else if (_current_it != _end_it) {
      ++_current_it;
    }
    return _current_it != _end_it;
  }

  T current() const override {
    if (!_is_started || _current_it == _end_it) {
      throw InvalidOperationException("За пределами границ очереди");
    }
    return *_current_it;
  }
};

export template <typename T>
class Stack : public IEnumerable<T> {
  std::deque<T> _data;
public:
  void push(const T& item) { _data.push_back(item); }

  T pop() {
    if (_data.empty()) {
      throw InvalidOperationException("Стек пуст");
    }
    T val = _data.back();
    _data.pop_back();
    return val;
  }

  T peek() const {
    if (_data.empty()) {
      throw InvalidOperationException("Стек пуст");
    }
    return _data.back();
  }

  int count() const { return static_cast<int>(_data.size()); }

  std::shared_ptr<IEnumerator<T>> get_enumerator() const override {
    return std::make_shared<StackEnumerator<T>>(_data.rbegin(), _data.rend());
  }
};

export template <typename T>
class Queue : public IEnumerable<T> {
  std::deque<T> _data;
public:
  void enqueue(const T& item) { _data.push_back(item); }

  T dequeue() {
    if (_data.empty()) {
      throw InvalidOperationException("Очередь пуста");
    }
    T val = _data.front();
    _data.pop_front();
    return val;
  }

  T peek() const {
    if (_data.empty()) {
      throw InvalidOperationException("Очередь пуста");
    }
    return _data.front();
  }

  int count() const { return static_cast<int>(_data.size()); }

  std::shared_ptr<IEnumerator<T>> get_enumerator() const override {
    return std::make_shared<QueueEnumerator<T>>(_data.begin(), _data.end());
  }
};
