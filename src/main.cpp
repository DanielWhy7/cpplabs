import std;

int invert_digits(int n) {
  int reversed = 0;
  while (n > 0) {
    reversed = reversed * 10 + (n % 10);
    n /= 10;
  }
  return reversed;
}

int add_right_digit(int n, int d) {
  return n * 10 + d;
}

bool is_prime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) return false;
  }
  return true;
}

unsigned long long fact(int n) {
  if (n <= 1) return 1;
  return n * fact(n - 1);
}

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int digit_sum(int n) {
  if (n == 0) return 0;
  return (n % 10) + digit_sum(n / 10);
}

int main() {
  int task{-1};

  while (task != 0) {
    std::println("1. Invert digits of the number");
    std::println("2. Add digits to right");
    std::println("3. Check if the number is prime");
    std::println("4. Calculate the factorial");
    std::println("5. FInd GSD via Evclids's algorithm");
    std::println("6. Find the sum of digits of the number recursevly");
    std::println("");
    std::cin >> task;
    switch (task) {
    case 1: {
      int n{0};
      std::print("[Task 1] Enter a positive number n: ");
      std::cin >> n;
      if (n <= 0) { std::println("The number must be positive!"); break; }

      std::println("Rotated number: {}", invert_digits(n));
      break;
    }
    case 2: {
      int n{0}, d{0};
      std::print("[Task 2] Enter positive number n: ");
      std::cin >> n;
      std::print("Enter digit d (0-9): ");
      std::cin >> d;
      if (n <= 0 || d < 0 || d > 9) { std::println("Incorrect input!"); break; }

      std::println("Result of adding: {}", add_right_digit(n, d));
      break;
    }
    case 3: {
      int n{0};
      std::print("[Task 3] Enter natural number: ");
      std::cin >> n;

      std::println("Number is prime: {}", is_prime(n));
      break;
    }
    case 4: {
      int n{0};
      std::print("[Task 4] Enter number to calculate factorial: ");
      std::cin >> n;
      if (n < 0) { std::println("The factorial is defined for non-negative numbers!"); break; }

      std::println("{}! = {}", n, fact(n));
      break;
    }
    case 5: {
      int a{0}, b{0};
      std::print("[Task 5] Enter two positive numbers (a and b): ");
      std::cin >> a >> b;
      if (a <= 0 || b <= 0) { std::println("Numbers must be greater than zero!"); break; }

      std::println("GSD({}, {}) = {}", a, b, gcd(a, b));
      break;
    }
    case 6: {
      int n{0};
      std::print("[Task 6] Enter integer number: ");
      std::cin >> n;

      std::println("Sum of digits of a number: {}", digit_sum(std::abs(n)));
      break;
    }
  }
}
