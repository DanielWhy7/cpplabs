import std;

class String {
  char* _data = nullptr;
  std::size_t _size = 0;

  void swap(String& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
  }
public:
  String() = default;

  explicit String(const char* s) {
    if (!s) {return;} _size = std::strlen(s); _data = new char[_size + 1]; std::memcpy(_data, s, _size + 1); } ~String() { delete[] _data; } String(const String& other) : _size(other._size) {
    if (_size > 0) {
      _data = new char[_size + 1];
      std::memcpy(_data, other._data, _size + 1);
    }
  }

  String& operator=(const String& other) {
    if (this != &other) {
      String tmp{other};
      swap(tmp);
    }
    return *this;
  }

  String(String&& other) noexcept : _data(other._data), _size(other._size) {
    other._data = nullptr;
    other._size = 0;
  }

  String& operator=(String&& other) noexcept {
    if (this != &other) {
      delete[] _data;
      _data = other._data;
      _size = other._size;
      other._data = nullptr;
      other._size = 0;
    }
    return *this;
  }

  std::size_t size() const { return _size; }

  char& operator[](std::size_t i) { return _data[i]; }
  const char& operator[](std::size_t i) const { return _data[i]; }

  const char* c_str() const { return _data ? _data : ""; }
};

template<>
struct std::formatter<String> : std::formatter<std::string_view> {
  auto format(const String& s, auto& ctx) const {
      std::string_view sv{s.c_str(), s.size()};
      return std::formatter<std::string_view>::format(sv, ctx);
  }
};

class StringBuilder {
  std::string buffer_;

public:
  StringBuilder() : buffer_{} {}

  void reserve(std::size_t size) { buffer_.reserve(size); }

  StringBuilder& append(const std::string& s) {
    buffer_.append(s);
    return *this;
  }

  StringBuilder& append(int value) {
    buffer_.append(std::to_string(value));
    return *this;
  }

  StringBuilder& append(float value) {
    buffer_.append(std::to_string(value));
    return *this;
  }

  String build() && {
    return String{buffer_.c_str()};
  }

  String build() const& {
    return String{buffer_.c_str()};
  }
};

int main() {
  std::cout<<"=== RAII STRING DEMO ===\n";

  String s1;
  String s2{"Hello, RAII!"};

  std::cout << std::format("s1: '{}', size: {}\n", s1, s1.size());
  std::cout << std::format("s2: '{}', size: {}\n", s2, s2.size());

  String s3 = s2;//s3(s2)//s3{s2}
  String s4 = std::move(s2);

  std::cout << std::format("s3 (copy): '{}'\n", s3);
  std::cout << std::format("s4 (move): '{}'\n", s4);

  std::cout << "\n=== StringBuilder demo ===\n";

  StringBuilder sb;
  sb.reserve(100);

  sb.append("The answer is: ");
  sb.append(42);
  sb.append(", and pi ~= ");
  sb.append(3.1415f);

  String result1 = sb.build();
  std::cout << std::format("lvalue build: '{}'\n", result1);

  String result2 = StringBuilder{}.append("Fast move!").build();
  std::cout << std::format("rvalue build: '{}'\n", result2);

  return 0;
}
