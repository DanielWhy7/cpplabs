module;
import std;
export module deposit_account;

export class DepositAccount {
  std::string owner_name;
  double balance;
  double annual_interest_rate;

  public:
  DepositAccount() : owner_name("Unknown"), balance(0.0), annual_interest_rate(0.0) {}

  DepositAccount(const std::string& name, double initial_balance, double rate)
    : owner_name(name), balance(initial_balance), annual_interest_rate(rate) {}

  std::string get_owner_name() const { return owner_name; }
  double get_balance() const { return balance; }
  double get_annual_interest_rate() const { return annual_interest_rate; }

  void accrue_monthly_interest() {
    double monthly_rate = annual_interest_rate / 100.0 / 12.0;
    balance += balance * monthly_rate;
  }

  std::string to_string() const {
    return std::format("Owner: {}, Balance: {:.2f} robux., Rate: {:.1f}% annually",
        owner_name, balance, annual_interest_rate);
  }
};

export void accrue_interest_for_all(std::vector<DepositAccount>& accounts) {
  for (auto& account : accounts) {
    account.accrue_monthly_interest();
  }
}

export int find_account_with_max_balance(const std::vector<DepositAccount>& accounts) {
  if (accounts.empty()) {
    return -1;
  }

  int max_index = 0;
  double max_balance = accounts[0].get_balance();

  for (std::size_t i = 1; i < accounts.size(); ++i) {
    if (accounts[i].get_balance() > max_balance) {
      max_balance = accounts[i].get_balance();
      max_index = static_cast<int>(i);
    }
  }

  return max_index;
}
