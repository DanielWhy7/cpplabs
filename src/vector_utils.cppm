module;
import std;
export module vector_utils;

export std::vector<int> input_vector(){
  int n = 0;
  std::cout << "Enter the number of sequence elements: ";
  std::cin >> n;

  if (n <= 0) {
    std::cout<<"The number of elements must be greater than 0.";
  }

  std::vector<int> v(n);

  bool mode=0;
  std::cout << "Choose input mode (0 - manual, 1 - random): ";
  std::cin >> mode;

  if (mode == 0) {
    for (int i = 0; i < n; ++i) {
      std::cin >> v[i];
    }
  } else {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-10, 10);
    for (int i = 0; i < n; ++i) {
      v[i] = dist(gen);
    }
  }

  return v;
}

export int count_elements_of_vector(const std::vector<int>& v){
  int count=0;
  for (int x : v)count++;
  return count;
}

export int sum_elements_of_vector(const std::vector<int>& v){
  int sum=0;
  for (int x : v) {
    sum+=x;
  }
  return sum;
}

export std::vector<int> algorithm(const std::vector<int>& v) {
  std::vector<int> result;
  for (int x : v) {
    if (x % 2 == 0) {
      result.push_back(x);
    }
  }
  return result;
}

export int show_vector(const std::vector<int>& v) {
  for (int x : v) {
    std::cout << x << ' ';
  }
  return 0;
}
