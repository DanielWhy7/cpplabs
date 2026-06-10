module;
import std;
export module casino;

export class Casino {
  int balance;

  public:
  Casino(int initial_balance) : balance(initial_balance) {}

  int get_balance() const { return balance; }

  bool play_slot_machine(int bet) {
    if (bet > balance) {
      std::cout << "Error: insufficient funds. Your balance: " << balance << " robux.\n";
      return false;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-15, 8);

    int result = dist(gen);
    balance += result * bet / 10;

    if (result > 0) {
      std::cout << "🎰 Lucky! You won " << balance << " robux!\n";
    } else if (result < 0) {
      std::cout << "😢 Unlucky! You lost " << balance << " robux.\n";
    } else {
      std::cout << "Draw! No change in balance.\n";
    }

    std::cout << "Current casino balance: " << balance << " robux.\n";
    return true;
  }

  std::string to_string() const {
    return std::format("Your balance: {} robux.", balance);
  }
};

export int play_casino_game(int initial_balance) {
  Casino casino(initial_balance);
  bool playing = true;

  std::cout << "\n=== Welcome to the Casino ===\n";
  std::cout << "You have " << initial_balance << " robux to play with!\n\n";

  while (playing && casino.get_balance() > 0) {
    std::cout << "Current balance: " << casino.get_balance() << " robux\n";
    std::cout << "[1] Play slot machine\n";
    std::cout << "[2] Exit casino\n";
    std::cout << "Select an option: ";

    int choice = 2;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
      case 1: {
        std::cout << "Enter your bet: ";
        int bet = 0;
        std::cin >> bet;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (bet > 0) {
          casino.play_slot_machine(bet);
        } else {
          std::cout << "Error: bet must be positive.\n";
        }
        break;
      }
      case 2: {
        std::cout << "Leaving casino with " << casino.get_balance() << " robux.\n";
        playing = false;
        break;
      }
      default:
        std::cout << "Invalid option. Try again.\n";
    }
    std::cout << "\n";
  }

  if (casino.get_balance() == 0) {
    std::cout << "Game Over! You've lost all your money!\n";
  }

  return casino.get_balance();
}
