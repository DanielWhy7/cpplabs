import std;

struct Fraction {
  int numerator = 0;
  int denominator = 1;
};

int gcd(int a,int b){//Greatest Common Divisor
  a = std::abs(a);
  b = std::abs(b);
  if (b==0){return a;}//a is numerator //b is denominator
  else return gcd(b,a%b);
}

Fraction rdc(int a,int b){
  int g=gcd(a,b);return {a/g,b/g};
}

Fraction add(int a, int b, int c, int d) {
  if (b == 0 || d == 0) {
    std::cerr<<"\n"<<"\033[31mError: Denominator cannot be zero!\033[0m"<<std::endl;
    return {0, 1};
  }
  int num = a * d + c * b;
  int den = b * d;
  int g = gcd(num, den);
  return {num / g, den / g};
}

int main() {
  int a = 0, b = 1, c = 0, d = 1;
  std::cout << "Enter a numerator of the first number: ";
  std::cin >> a;
  std::cout << "Enter a denominator of the first number: ";
  std::cin >> b;
  std::cout << "Enter a numerator of the second number: ";
  std::cin >> c;
  std::cout << "Enter a demominator of the second number: ";
  std::cin >> d;

  Fraction result = add(a, b, c, d);
  std::print("\033[1;32mResult\033[0m: {}/{}\n", result.numerator, result.denominator);
  return 0;
}
