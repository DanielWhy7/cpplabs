import std;
import account;

void line(){
  std::println("--------------------");
}

void print_menu(const std::vector<std::shared_ptr<Account>>& accounts) {
  std::cout << "Accounts: [";
  for (std::size_t i = 0; i < accounts.size(); ++i) {
    if (i > 0) std::cout << "; ";
    std::cout << accounts[i]->get_owner_name() << ": " << accounts[i]->get_balance() << " robux.";
  }
  std::cout << "]\n";
  std::cout << "[1] Insert a new account\n";
  std::cout << "[2] Delete account\n";
  std::cout << "[3] Display all accounts\n";
  std::cout << "[4] Process monthly interest for all accounts\n";
  std::cout << "[5] Find account with minimum balance\n";
  std::cout << "[6] Find account with maximum balance\n";
  std::cout << "[7] Exit\n";
}

int main(int argc, char *argv[]) {
  if (argc > 2) {
    std::println("Usage: {} <about>", argv[0]);
    return 1;
  }

  if (argc == 2 && std::strcmp(argv[1], "about") == 0){
    line();
    std::println("  Lab No.: 4");
    std::println("  Group: 6114");
    std::println("  Author: Bikmetov Daniel");
    std::println("  Variant: 1");
    line();
    return 0;
  }

  line();
  std::vector<std::shared_ptr<Account>> accounts;
  bool running = true;

  while (running) {
    print_menu(accounts);
    std::cout << "\nSelect a menu item: ";

    int choice = 7;
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

        std::cout << "Select account type:\n";
        std::cout << "[1] Checking Account\n";
        std::cout << "[2] Deposit Account\n";
        std::cout << "[3] Credit Account\n";
        std::cout << "Choice: ";

        int type = 1;
        std::cin >> type;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string name = "";
        double balance = 0.0;

        std::cout << "Enter owner's name: ";
        std::getline(std::cin, name);

        std::cout << "Enter current balance: ";
        std::cin >> balance;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::shared_ptr<Account> new_account;

        switch (type) {
          case 1: {
            new_account = std::make_shared<CheckingAccount>(name, balance);
            break;
          }
          case 2: {
            double rate = 0.0;
            std::cout << "Enter annual interest rate (%): ";
            std::cin >> rate;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            new_account = std::make_shared<DepositAccount>(name, balance, rate);
            break;
          }
          case 3: {
            double rate = 0.0;
            std::cout << "Enter annual interest rate (%): ";
            std::cin >> rate;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            new_account = std::make_shared<CreditAccount>(name, balance, rate);
            break;
          }
          default: {
            std::cout << "Error: invalid account type.\n";
            break;
          }
        }

        if (new_account) {
          accounts.insert(accounts.begin() + index, new_account);
          std::cout << "Account successfully added.\n";
        }
        break;
      }
      case 2: {
        std::cout << "Enter the index of the account to delete: ";
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
        if (accounts.empty()) {
          std::cout << "No accounts in the container.\n";
        } else {
          std::cout << "\n=== All Accounts ===\n";
          for (std::size_t i = 0; i < accounts.size(); ++i) {
            std::cout << "[" << i << "] " << accounts[i]->to_string() << "\n";
          }
        }
        break;
      }
      case 4: {
        process_interest_for_all(accounts);
        std::cout << "Monthly interest processed for all accounts.\n";
        break;
      }
      case 5: {
        auto min_account = find_account_with_min_balance(accounts);
        if (!min_account) {
          std::cout << "Container is empty. No accounts to search.\n";
        } else {
          std::cout << "Account with the minimum balance:\n";
          std::cout << "- " << min_account->to_string() << "\n";
        }
        break;
      }
      case 6: {
        auto max_account = find_account_with_max_balance(accounts);
        if (!max_account) {
          std::cout << "Container is empty. No accounts to search.\n";
        } else {
          std::cout << "Account with the maximum balance:\n";
          std::cout << "- " << max_account->to_string() << "\n";
        }
        break;
      }
      case 7: {
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
