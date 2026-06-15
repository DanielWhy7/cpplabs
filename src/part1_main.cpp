import std;
import fraction;
import sorted_array;

void display_menu() {
  std::println("\n=== Sorted Fraction Array Menu ===");
  std::println("1. Create and add fraction");
  std::println("2. Remove element by index");
  std::println("3. View element by index");
  std::println("4. Display array");
  std::println("5. Exit");
  std::print("Choose option: ");
}

void view_element_menu(SortedFractionArray& arr, size_t index) {
  bool viewing = true;
  while (viewing) {
    std::println("\n--- Viewing Element [{}]: {} ---", index, arr.get_at(index).to_string());
    std::println("1. Apply operation (add fraction or multiply by integer)");
    std::println("2. Replace with new fraction");
    std::println("3. Stop viewing");
    std::print("Choose action: ");
    
    int action;
    std::cin >> action;
    std::cin.ignore();

    switch (action) {
      case 1: {
        std::println("\nApply operation:");
        std::print("Operation (+/mul): ");
        std::string op_str;
        std::getline(std::cin, op_str);
        
        char op = op_str[0];
        if (op != '+' && op != '*') {
          std::println("Invalid operation");
          break;
        }

        if (op == '+') {
          std::print("Enter fraction numerator: ");
          long long num;
          std::cin >> num;
          std::print("Enter fraction denominator: ");
          long long denom;
          std::cin >> denom;
          std::cin.ignore();
          
          Fraction operand(num, denom);
          arr.apply_operation(index, operand, '+');
        } else {
          std::print("Enter integer to multiply: ");
          long long num;
          std::cin >> num;
          std::cin.ignore();
          
          Fraction operand(num, 1);
          arr.apply_operation(index, operand, '*');
        }
        
        arr.display();
        break;
      }
      case 2: {
        std::print("Enter new fraction numerator: ");
        long long num;
        std::cin >> num;
        std::print("Enter new fraction denominator: ");
        long long denom;
        std::cin >> denom;
        std::cin.ignore();
        
        arr.replace_at(index, Fraction(num, denom));
        arr.display();
        break;
      }
      case 3: {
        viewing = false;
        break;
      }
      default:
        std::println("Invalid action");
    }
  }
}

int main() {
  SortedFractionArray arr;
  bool running = true;

  std::println("=== Sorted Fraction Array Application ===");
  std::println("\nNOTE: The array is automatically kept sorted after each operation.");
  std::println("When replacing an element, the array is re-sorted to maintain order.");

  while (running) {
    display_menu();
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    try {
      switch (choice) {
        case 1: {
          std::print("Enter numerator: ");
          long long num;
          std::cin >> num;
          std::print("Enter denominator: ");
          long long denom;
          std::cin >> denom;
          std::cin.ignore();

          Fraction f(num, denom);
          arr.add(f);
          std::println("Fraction added: {}", f.to_string());
          arr.display();
          break;
        }
        case 2: {
          arr.display();
          std::print("Enter index to remove: ");
          size_t idx;
          std::cin >> idx;
          std::cin.ignore();
          arr.remove_at(idx);
          std::println("Element removed");
          arr.display();
          break;
        }
        case 3: {
          arr.display();
          std::print("Enter index to view: ");
          size_t idx;
          std::cin >> idx;
          std::cin.ignore();
          view_element_menu(arr, idx);
          break;
        }
        case 4: {
          arr.display();
          break;
        }
        case 5: {
          running = false;
          std::println("Exiting...");
          break;
        }
        default:
          std::println("Invalid option");
      }
    } catch (const std::exception& e) {
      std::println("Error: {}", e.what());
    }
  }

  return 0;
}
