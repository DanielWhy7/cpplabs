import std;
import vector_utils;

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

  std::vector<int> v = input_vector();
  std::cout << "Count vector: ";
  std::cout << sum_elements_of_vector(v) << std::endl;
  std::cout << "Input vector: ";
  show_vector(v);
  std::cout << std::endl;

  return 0;
}
