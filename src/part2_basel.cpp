import std;
import fraction;

int main() {
  std::println("=== Basel Series Partial Sum ===");
  std::print("Enter n (number of terms): ");
  int n;
  std::cin >> n;

  if (n <= 0) {
    std::println("n must be positive");
    return 1;
  }

  Fraction sum(0, 1);

  for (int k = 1; k <= n; ++k) {
    Fraction term(1, k * k);
    sum = sum + term;
  }

  std::println("\nPartial sum for n = {}: {}", n, sum.to_string());
  std::println("pi^2/6 ~= 1.644934...");
  std::println("Your result ~= {:.6f}", 
    static_cast<double>(sum.a()) / sum.b());

  return 0;
}
