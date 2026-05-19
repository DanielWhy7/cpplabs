module;
import std;
export module casino;

export int dep(int money){

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(-10, 10);
  for (int i = 0; i < n; ++i) {
    v[i] = dist(gen);
  }

  return v;
}
