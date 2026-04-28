import std;

// RAII-обёртка String
class String {
private:
    char* data_ = nullptr;
    size_t size_ = 0;

public:
    // 1. Конструктор по умолчанию
    String() = default;

    // 2. Конструктор по C‑строке
    explicit String(const char* s) {
        if (!s) {
            return;
        }
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::memcpy(data_, s, size_ + 1);
    }

    // 3. Деструктор
    ~String() { delete[] data_; }

    // 4. Copy конструктор
    String(const String& other) : size_(other.size_) {
        if (size_ > 0) {
            data_ = new char[size_ + 1];
            std::memcpy(data_, other.data_, size_ + 1);
        }
    }

    // 5. Copy assignment
    String& operator=(const String& other) {
        if (this != &other) {
            String tmp{other};
            swap(tmp);
        }
        return *this;
    }

    // 6. Move конструктор
    String(String&& other) noexcept : data_(other.data_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // 7. Move assignment
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 8. Метод для получения размера строки
    size_t size() const { return size_; }

    // 9. Операторы [] для доступа к символам
    char& operator[](size_t i) { return data_[i]; }
    const char& operator[](size_t i) const { return data_[i]; }

    // Для C‑строки (в случае необходимости)
    const char* c_str() const { return data_ ? data_ : ""; }

private:
    void swap(String& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }
};

// std::formatter специализация для String
template<>
struct std::formatter<String> : std::formatter<std::string_view> {
    auto format(const String& s, auto& ctx) const {
        std::string_view sv{s.c_str(), s.size()};
        return std::formatter<std::string_view>::format(sv, ctx);
    }
};

// StringBuilder — аналог std::stringstream
class StringBuilder {
private:
    std::string buffer_;

public:
    // 1. Конструктор по умолчанию
    StringBuilder() = default;

    // 2. Правило ноля (все действия делегируются std::string)

    // 3. Метод резервирования памяти
    void reserve(size_t size) { buffer_.reserve(size); }

    // 4. Перегрузки append
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

    // 5. &&-перегрузка build (перемещает buffer)
    String build() && {
        return String{buffer_.c_str()};
    }

    // 6. &-перегрузка build (копирует buffer)
    String build() const& {
        return String{buffer_.c_str()};
    }
};

// Пример демонстрации
int main() {
    std::cout << "=== RAII String demo ===\n";

    // String — конструктор по умолчанию и по C‑строке
    String s1;
    String s2{"Hello, RAII!"};

    std::cout << std::format("s2: '{}', size: {}\n", s2, s2.size());

    // Копирующая и перемещающая семантика
    String s3 = s2;
    String s4 = std::move(s2);

    std::cout << std::format("s3 (copy): '{}'\n", s3);
    std::cout << std::format("s4 (move): '{}'\n", s4);

    // StringBuilder и append
    std::cout << "\n=== StringBuilder demo ===\n";

    StringBuilder sb;
    sb.reserve(100);

    sb.append("The answer is: ");
    sb.append(42);
    sb.append(", and pi ≈ ");
    sb.append(3.1415f);

    // lvalue build (copy)
    String result1 = sb.build();
    std::cout << std::format("lvalue build: '{}'\n", result1);

    // rvalue build (move)
    String result2 = StringBuilder{}.append("Fast move!").build();
    std::cout << std::format("rvalue build: '{}'\n", result2);

    return 0;
}
