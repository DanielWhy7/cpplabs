export module sequence_reader;

import std;

export enum class SequenceSource {
  CONSOLE,
  RANDOM,
  PREDEFINED
};

export template<typename T>
concept ReadableType = requires(T & obj, std::istream & is) {
  { is >> obj } -> std::same_as<std::istream&>;
};

export template<ReadableType T>
class SequenceReader {
public:
  virtual ~SequenceReader() = default;
  virtual std::vector<T> read() = 0;
};

export template<ReadableType T>
class ConsoleReader : public SequenceReader<T> {
public:
  std::vector<T> read() override {
    std::vector<T> sequence;
    std::print("Enter number of elements: ");
    int count;
    std::cin >> count;

    if (count <= 0) {
      std::println("Count must be positive");
      return sequence;
    }

    for (int i = 0; i < count; ++i) {
      std::print("Enter element [{}]: ", i + 1);
      T element;
      std::cin >> element;
      sequence.push_back(element);
    }

    return sequence;
  }
};

export template<typename T>
concept Randomizable = requires(T & obj) {
  { T::random() } -> std::same_as<T>;
};

export template<Randomizable T>
class RandomReader : public SequenceReader<T> {
public:
  std::vector<T> read() override {
    std::vector<T> sequence;
    std::print("Enter number of elements to generate: ");
    int count;
    std::cin >> count;
    
    if (count <= 0) {
      std::println("Count must be positive");
      return sequence;
    }

    for (int i = 0; i < count; ++i) {
      sequence.push_back(T::random());
    }

    return sequence;
  }
};

export template<typename T>
class PredefinedReader : public SequenceReader<T> {
private:
  std::vector<T> predefined_data;

public:
  PredefinedReader(const std::vector<T>& data) : predefined_data(data) {}

  std::vector<T> read() override {
    return predefined_data;
  }
};
