import std;
import fraction;
import sequence_reader;

template<>
struct std::formatter<Fraction> {
  constexpr auto parse(std::format_parse_context& ctx) {
    return ctx.begin();
  }

  auto format(const Fraction& f, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "{}", f.to_string());
  }
};

std::istream& operator>>(std::istream& is, Fraction& f) {
  long long num, denom;
  is >> num >> denom;
  f = Fraction(num, denom);
  return is;
}

template<>
class RandomReader<Fraction> : public SequenceReader<Fraction> {
public:
  std::vector<Fraction> read() override {
    std::vector<Fraction> sequence;
    std::print("Enter number of random fractions to generate: ");
    int count;
    std::cin >> count;
    
    if (count <= 0) {
      std::println("Count must be positive");
      return sequence;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    for (int i = 0; i < count; ++i) {
      long long num = dis(gen);
      long long denom = dis(gen);
      sequence.push_back(Fraction(num, denom));
    }

    return sequence;
  }
};

template<typename T>
Fraction calculate_average_online(const std::vector<T>& sequence) {
  if (sequence.empty()) {
    return Fraction(0, 1);
  }

  Fraction sum(0, 1);
  for (const auto& element : sequence) {
    sum = sum + Fraction(element.a() * 1, element.b());
  }

  return Fraction(sum.a(), sum.b() * static_cast<long long>(sequence.size()));
}

int main() {
  std::println("=== Fraction Sequence Average Calculator ===");
  std::println("\nSelect input mode:");
  std::println("1. Console input");
  std::println("2. Random generation");
  std::println("3. Predefined sequence");
  std::print("Choose mode: ");
  
  int mode;
  std::cin >> mode;
  std::cin.ignore();

  std::vector<Fraction> sequence;

  try {
    switch (mode) {
      case 1: {
        ConsoleReader<Fraction> reader;
        sequence = reader.read();
        break;
      }
      case 2: {
        RandomReader<Fraction> reader;
        sequence = reader.read();
        std::println("\nGenerated sequence:");
        for (size_t i = 0; i < sequence.size(); ++i) {
          std::println("[{}] {}", i, sequence[i].to_string());
        }
        break;
      }
      case 3: {
        std::vector<Fraction> predefined = {
          Fraction(1, 2),
          Fraction(1, 3),
          Fraction(1, 4),
          Fraction(1, 6)
        };
        PredefinedReader<Fraction> reader(predefined);
        sequence = reader.read();
        std::println("\nPredefined sequence:");
        for (size_t i = 0; i < sequence.size(); ++i) {
          std::println("[{}] {}", i, sequence[i].to_string());
        }
        break;
      }
      default:
        std::println("Invalid mode");
        return 1;
    }

    if (sequence.empty()) {
      std::println("No elements in sequence");
      return 1;
    }

    Fraction average = calculate_average_online(sequence);
    std::println("\nAverage: {}", average.to_string());
    std::println("Decimal: {:.6f}", 
      static_cast<double>(average.a()) / average.b());

  } catch (const std::exception& e) {
    std::println("Error: {}", e.what());
    return 1;
  }

  return 0;
}
