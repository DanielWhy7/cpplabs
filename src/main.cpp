import std;
import deposit_account;

void line(){
  std::println("--------------------");
}

void print_menu(const std::vector<DepositAccount>& accounts) {
  std::cout << "Deposit accounts: [";
  for (std::size_t i = 0; i < accounts.size(); ++i) {
    if (i > 0) std::cout << "; ";
    std::cout << accounts[i].get_owner_name() << ": " << accounts[i].get_balance() << " robux.";
  }
  std::cout << "]\n";
  std::cout << "[1] Insert a new deposit account\n";
  std::cout << "[2] Delete deposit account\n";
  std::cout << "[3] Calculate interest on all accounts\n";
  std::cout << "[4] Find the account with the highest current balance\n";
  std::cout << "[5] Exit\n";
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::println("Usage: {} <about>", argv[0]);
    return 1;
  }

  if (argc == 2 && std::strcmp(argv[1], "about") == 0){
    line();
    std::println("  Lab No.: 1");
    std::println("  Group: 6114");
    std::println("  Author: Bikmetov Daniel");
    std::println("  Variant: 1");
    line();
    return 0;
  }

  line();
  std::vector<DepositAccount> accounts;
  bool running = true;

  while (running) {
    print_menu(accounts);
    std::cout << "\nSelect a menu item: ";

    int choice = 6;//if program fails, it should exit
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
      case 1: {
        std::cout << "Enter the insertion index: ";
        std::size_t index = 0;
        std::cin >> index;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (index > accounts.size()) {
          std::cout << "Error: invalid index.\n";
          break;
        }

        std::string name = "";
        double balance = 0.0;
        double rate = 0.0;

        std::cout << "Enter client's name: ";
        std::getline(std::cin, name);

        std::cout << "Enter current balance: ";
        std::cin >> balance;

        std::cout << "Enter annual interest rate (%): ";
        std::cin >> rate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        accounts.insert(accounts.begin() + index, DepositAccount(name, balance, rate));
        std::cout << "Account successfully added.\n";
        break;
      }
      case 2: {
        std::cout << "Enter the index of the element to delete: ";
        std::size_t index = 0;
        std::cin >> index;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (index >= accounts.size()) {
          std::cout << "Error: invalid index.\n";
          break;
        }

        accounts.erase(accounts.begin() + index);
        std::cout << "Account successfully deleted.\n";
        break;
      }
      case 3: {
        accrue_interest_for_all(accounts);
        std::cout << "Interest accrued on all accounts.\n";
        break;
      }
      case 4: {
        int index = find_account_with_max_balance(accounts);
        if (index == -1) {
          std::cout << "Container is empty. No accounts to search.\n";
        } else {
          std::cout << "Account with the highest current balance:\n";
          std::cout << "- Account index in container: " << index << "\n";
          std::cout << "- " << accounts[index].to_string() << "\n";
        }
        break;
      }
      case 5: {
        std::cout << "Goodbye!\n";
        running = false;
        break;
      }
      default: std::cout << "Invalid menu item. Try again.\n";
    }
    std::cout << "\n";
  }

  return 0;
}
