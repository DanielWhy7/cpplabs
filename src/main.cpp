import std;
import Collections.List;
import Collections.Sets;
import Collections.Specialized;

template <typename T>
struct RangeIterator {
  std::shared_ptr<IEnumerator<T>> enumerator;
  bool has_more;

  bool operator!=(const RangeIterator& other) const {
    return has_more != other.has_more;
  }

  void operator++() {
    has_more = enumerator->move_next();
  }

  T operator*() const {
    return enumerator->current();
  }
};

template <typename T>
auto begin(const IEnumerable<T>& collection) {
  auto enumerator = collection.get_enumerator();
  bool has_more = enumerator->move_next();
  return RangeIterator<T>{ enumerator, has_more };
}

template <typename T>
auto end(const IEnumerable<T>&) {
  return RangeIterator<T>{ nullptr, false };
}

int main() {

  std::print("=== Тестирование List ===\n");
  List<std::string> list;
  list.add("Первый");
  list.add("Второй");
  list.add("Третий");

  list[1] = "Измененный Второй";

  std::print("Элемент по индексу 1: {}\n", list[1]);

  try {
    std::print("{}", list[99]);
  }
  catch (const InvalidOperationException& ex) {
    std::print("Ошибка индекса: {}\n", ex.what());
  }

  std::print("Количество элементов в списке: {}\n", list.count());

  std::print("Содержимое списка: ");
  for (const auto& item : list) {
    std::print("{} | ", item);
  }
  std::print("\n\n");


  std::print("=== Тестирование HashSet ===\n");
  HashSet<int> set;
  set.add(10);
  set.add(20);
  set.add(10);

  std::print("Элементов в множестве (ожидается 2): {}\n", set.count());
  std::print("Содержит 20? {}\n", set.contains(20) ? "Да" : "Нет");

  std::print("Элементы множества: ");
  for (int num : set) {
    std::print("{} ", num);
  }
  std::print("\n\n");


  std::print("=== Тестирование Dictionary ===\n");
  Dictionary<int, std::string> dict;
  dict.add({ 1, "One" });
  dict.add({ 2, "Two" });
  dict[3] = "Three";

  std::print("Значение по ключу 3: {}\n", dict[3]);
  std::print("Элементы словаря:\n");
  for (auto pair : dict) {
    std::print(" Ключ: {} -> Значение: {}\n", pair.first, pair.second);
  }
  std::print("\n");


  std::print("=== Тестирование Stack (LIFO) ===\n");
  Stack<int> stack;
  stack.push(100);
  stack.push(200);
  stack.push(300);

  std::print("Обход стека через итератор (с вершины): ");
  for (int val : stack) {
    std::print("{} ", val);
  }
  std::print("\n");

  std::print("Извлекаем из стека (pop): {}\n", stack.pop());
  std::print("Текущая вершина (peek): {}\n", stack.peek());
  std::print("\n");


  std::print("=== Тестирование Queue (FIFO) ===\n");
  Queue<std::string> queue;
  queue.enqueue("Пациент А");
  queue.enqueue("Пациент Б");

  std::print("Обход очереди через итератор: ");
  for (const auto& patient : queue) {
    std::print("{} -> ", patient);
  }
  std::print("Конец очереди\n\n");


  std::print("=== Тестирование исключений ===\n");
  try {
    Stack<double> empty_stack;
    empty_stack.pop();
  }
  catch (const InvalidOperationException& ex) {
    std::print("Перехвачено ожидаемое исключение: {}\n", ex.what());
  }
  catch (const std::exception& ex) {
    std::print("Другое исключение: {}\n", ex.what());
  }

  return 0;
}
