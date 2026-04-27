import std;

class Fraction {
  int _a,_b;//a is numerator //b is denominator

  bool check_den(int k)const{
    if(k!=0) return 0;
    std::cerr<<"\n"<<"\033[31mError: Denominator cannot be zero!\033[0m"<<std::endl;
    return 1;
  }

  int rdc(){
    int g=std::gcd(_a,_b);_a=_a/g;_b=_b/g;
    return 0;
  }

  public:
  Fraction(const Fraction&) = default;
  Fraction() : _a(0), _b(1) {}
  Fraction(int k) : _a(k), _b(1) {}
  Fraction(int k, int j) : _a(k), _b((j == 0) ? 1 : j) {rdc();}

  int num()const {return _a;}
  int den()const {return _b;}

  int set_num(int k){_a=k;return rdc();}
  int set_den(int k){
    if(check_den(k)){
      _b=k;
      return 0;
    }
    return 1;
  }

  Fraction& operator+=(const Fraction& other) {
    _a = _a * other._b + other._a * _b;
    _b = _b * other._b;
    rdc();
    return *this;
  }
};

Fraction operator+(Fraction a, const Fraction& b) {
  return a += b;
}

//int gcd(int a,int b){//Greatest Common Divisor
//  a = std::abs(a);
//  b = std::abs(b);
//  if (b==0){return a;}//a is numerator //b is denominator
//  else return gcd(b,a%b);
//}

int promt_user_set(Fraction& x){
  int n,d;
  std::cout << "Enter a numerator of the first number: ";
  std::cin >> n;
  std::cout << "Enter a denominator of the first number: ";
  std::cin >> d;
  x=Fraction(n,d);
  return 0;
}

int main() {
  Fraction a;Fraction b;promt_user_set(a);promt_user_set(b);

  Fraction result = a+b;
  std::cout << "\033[1;32mResult\033[0m:" << result.num() << "/" << result.den() << "\n";
  return 0;
}
