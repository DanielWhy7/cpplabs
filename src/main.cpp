import std;

int foo(int x){return x + 1 > x;}

int main(){
  int max_int = std::numeric_limits<int>::max();
  std::cout << "INT_MAX = " << max_int << "\n";
  int result = foo(max_int);
  std::cout << "foo(INT_MAX) = " << result << "\n";
  return 0;
}
