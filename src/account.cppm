module;
import std;
export module account;

export class Account {
  protected:
  std::string owner_name;
  double balance;

  public:
  Account() : owner_name("Unknown"), balance(0.0) {}

  Account(const std::string& name, double initial_balance)
    : owner_name(name), balance(initial_balance) {}

  virtual ~Account() = default;

  std::string get_owner_name() const { return owner_name; }
  double get_balance() const { return balance; }

  virtual void process_monthly_interest() = 0;
  virtual std::string to_string() const = 0;
};

export class CheckingAccount : public Account {
  public:
  CheckingAccount() : Account("Unknown", 0.0) {}

  CheckingAccount(const std::string& name, double initial_balance)
    : Account(name, initial_balance) {}

  void process_monthly_interest() override {
    // Ничего не происходит для расчётного счёта
  }

  std::string to_string() const override {
    return std::format("Checking Account - Owner: {}, Balance: {:.2f} robux.",
        owner_name, balance);
  }
};

export class DepositAccount : public Account {
  private:
  double annual_interest_rate;

  public:
  DepositAccount() : Account("Unknown", 0.0), annual_interest_rate(0.0) {}

  DepositAccount(const std::string& name, double initial_balance, double rate)
    : Account(name, initial_balance), annual_interest_rate(rate) {}

  double get_annual_interest_rate() const { return annual_interest_rate; }

  void process_monthly_interest() override {
    double monthly_rate = annual_interest_rate / 100.0 / 12.0;
    balance += balance * monthly_rate;
  }

  std::string to_string() const override {
    return std::format("Deposit Account - Owner: {}, Balance: {:.2f} robux., Rate: {:.1f}% annually",
        owner_name, balance, annual_interest_rate);
  }
};

export class CreditAccount : public Account {
  private:
  double annual_interest_rate;

  public:
  CreditAccount() : Account("Unknown", 0.0), annual_interest_rate(0.0) {}

  CreditAccount(const std::string& name, double initial_balance, double rate)
    : Account(name, initial_balance), annual_interest_rate(rate) {}

  double get_annual_interest_rate() const { return annual_interest_rate; }

  void process_monthly_interest() override {
    // Проценты списываются только если баланс < 0
    if (balance < 0) {
      double monthly_rate = annual_interest_rate / 100.0 / 12.0;
      balance -= std::abs(balance) * monthly_rate;
    }
  }

  std::string to_string() const override {
    return std::format("Credit Account - Owner: {}, Balance: {:.2f} robux., Rate: {:.1f}% annually",
        owner_name, balance, annual_interest_rate);
  }
};

export void process_interest_for_all(std::vector<std::shared_ptr<Account>>& accounts) {
  for (auto& account : accounts) {
    account->process_monthly_interest();
  }
}

export std::shared_ptr<Account> find_account_with_min_balance(
    const std::vector<std::shared_ptr<Account>>& accounts) {
  if (accounts.empty()) {
    return nullptr;
  }

  std::shared_ptr<Account> min_account = accounts[0];
  double min_balance = accounts[0]->get_balance();

  for (std::size_t i = 1; i < accounts.size(); ++i) {
    if (accounts[i]->get_balance() < min_balance) {
      min_balance = accounts[i]->get_balance();
      min_account = accounts[i];
    }
  }

  return min_account;
}

export std::shared_ptr<Account> find_account_with_max_balance(
    const std::vector<std::shared_ptr<Account>>& accounts) {
  if (accounts.empty()) {
    return nullptr;
  }

  std::shared_ptr<Account> max_account = accounts[0];
  double max_balance = accounts[0]->get_balance();

  for (std::size_t i = 1; i < accounts.size(); ++i) {
    if (accounts[i]->get_balance() > max_balance) {
      max_balance = accounts[i]->get_balance();
      max_account = accounts[i];
    }
  }

  return max_account;
}
