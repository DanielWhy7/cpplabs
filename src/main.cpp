import std;

void print_line(){
  std::println("--------------------");
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::println("Usage: {} <about>", argv[0]);
    return 1;
  }

  if (argc == 2 && std::strcmp(argv[1], "about") == 0){
    print_line();
    std::println("  Lab №: 1");
    std::println("  Group: 6114");
    std::println("  Author: Bikmetov Daniel");
    std::println("  Variant: 1");
    print_line();
    return 0;
  }

  int n = 0;
  std::println("Enter the number of sequence elements: ");
  std::cin >> n;

  if (n <= 0) {
    std::println("The number of elements must be greater than 0.");
    return 1;
  }

  int sum = 0;
  int count = 0;

  std::println("Enter {} elements of the sequence:", n);
  while (count < n) {
    int x = 0;
    std::cin >> x;
    sum += x;
    count++;
  }

  std::println("Amount of elements: {}", n);
  std::println("Sum of elements: {}", sum);

  return 0;
}
