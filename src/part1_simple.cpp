import std;
import fraction;

void process(const Fraction& f) {
  std::println("{} {}", f.a(), f.b());
  std::println("{}", to_string(add(f, 2)));
}

int main() {
  Fraction frac(3, 4);
  process(frac);
  return 0;
}
