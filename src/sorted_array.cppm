export module sorted_array;

import std;
import fraction;

export class SortedFractionArray {
private:
  std::vector<Fraction> data;

  void maintain_sorted_order() {
    std::sort(data.begin(), data.end());
  }

public:
  SortedFractionArray() = default;

  void add(const Fraction& f) {
    data.push_back(f);
    maintain_sorted_order();
  }

  void remove_at(size_t index) {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    data.erase(data.begin() + index);
  }

  const Fraction& get_at(size_t index) const {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

  size_t size() const { return data.size(); }

  void replace_at(size_t index, const Fraction& f) {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    data[index] = f;
    maintain_sorted_order();
  }

  void apply_operation(size_t index, const Fraction& operand, char op) {
    if (index >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
    
    Fraction result = data[index];
    if (op == '+') {
      result = result + operand;
    } else if (op == '*') {
      result = result * operand;
    }
    
    data[index] = result;
    maintain_sorted_order();
  }

  void display() const {
    if (data.empty()) {
      std::println("Array is empty");
      return;
    }
    for (size_t i = 0; i < data.size(); ++i) {
      std::println("[{}] {}", i, data[i].to_string());
    }
  }
};
