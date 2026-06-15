import std;
import fraction;

int main() {
  std::println("=== Birthday Paradox ===");
  std::print("Enter n (number of people): ");
  int n;
  std::cin >> n;

  if (n <= 0 || n > 365) {
    std::println("n must be between 1 and 365");
    return 1;
  }

  Fraction product(1, 1);
  
  for (int k = 0; k < n; ++k) {
    Fraction term(365 - k, 365);
    product = product * term;
  }

  Fraction probability = Fraction(1, 1) - product;

  std::println("\nProbability that at least 2 people share birthday for n = {}: {}", 
    n, probability.to_string());
  std::println("Decimal: {:.6f}", 
    static_cast<double>(probability.a()) / probability.b());

  return 0;
}
