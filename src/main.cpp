import std;

int main() {
 int task = -1;

 while (task != 0) {
  std::println("\nSelect a task number (1, 2, 3) or 0 to exit:");
  std::println("1 — Sum and product of digits of a three-digit number");
  std::println("2 — Full minutes since the start of the last hour");
  std::println("3 — Determine the day of the week for the n-th day of the year");
  std::println("4 — Check for ascending sequence of digits");
  std::println("5 — Check the move of a rook");
  std::println("6 — Determine the number of days in a year");
  std::println("7 — Get a text description of a number");
  std::println("8 — Convert a three-digit number to text");
  std::println("9 — Output numbers in the range from a to b and their count"); 
  std::println("10 — Output all integer powers of number a from 1 to n"); 
  std::println("0 — Exit the program");
  std::print("Your choice: "); 

  std::cin >> task;
  std::println("----------------------------------------");

  switch (task) {
  case 0:
   std::println("Program completed. Goodbye!");
   break;

  case 1: {
   int number;
   std::print("[Task 1] Enter a three-digit number: ");
   std::cin >> number;

   int digit3 = number % 10;
   int digit2 = (number / 10) % 10;
   int digit1 = number / 100;

   int sum = digit1 + digit2 + digit3;
   int product = digit1 * digit2 * digit3;

   std::println("Sum of digits: {}", sum);
   std::println("Product of digits: {}", product);
   break;
  }
  case 2: {
   int n;
   std::print("[Task 2] Enter the number of seconds (n): ");
   std::cin >> n;

   int minutes = (n % 3600) / 60;

   std::println("Full minutes elapsed since the start of the hour: {}", minutes);
   break;
  }
  case 3: {
   int n, k;
   std::print("[Task 3] Enter the day of the year n (1-365): ");
   std::cin >> n;
   std::print("Enter the day of the week for January 1 k (1-7): ");
   std::cin >> k;

   int day_of_week = (n + k - 2) % 7 + 1;

   std::println("Day of the week for day {} of the year: {}", n, day_of_week);
   break;
  }
  case 4: {
   int number;
   std::print("[Task 4] Enter a three-digit number: ");
   std::cin >> number;
   int digit3 = number % 10;   
   int digit2 = (number / 10) % 10; 
   int digit1 = number / 100;  

   bool is_increasing = (digit1 < digit2) && (digit2 < digit3);

   std::println("Digits form an ascending sequence: {}", is_increasing);
   break;
  }
  case 5: {
   int x1, y1, x2, y2;
   std::println("[Task 5] Enter the coordinates of two squares (x1, y1, x2, y2) from 1 to 8:");
   std::print("Coordinates of the first square: ");
   std::cin >> x1 >> y1;
   std::print("Coordinates of the second square: ");
   std::cin >> x2 >> y2;
   bool can_move = (x1 == x2) || (y1 == y2);

   std::println("The rook can move from one square to another: {}", can_move);
   break;
  }
  case 6: {
   int year;
   std::print("[Task 6] Enter the year: ");
   std::cin >> year;
   bool is_leap = (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));

   int days = is_leap ? 366 : 365;

   std::println("Number of days in year {}: {}", year, days);
   break;
  }
  case 7: {
   int number;
   std::print("[Task 7] Enter a number from 1 to 999: ");
   std::cin >> number;

   if (number < 1 || number > 999) {
    std::println("Error: number must be in the range from 1 to 999!");
    break;
   }

   std::string parity = (number % 2 == 0) ? "even" : "odd";

   std::string length;
   if (number < 10) {
    length = "single-digit";
   }
   else if (number < 100) {
    length = "two-digit";
   }
   else {
    length = "three-digit";
   }

   std::println("Description: {} {} number", parity, length);
   break;
  }
  case 8: {
   int number;
   std::print("[Task 8] Enter a number from 100 to 999: ");
   std::cin >> number;

   if (number < 100 || number > 999) {
    std::println("Error: number must be in the range from 100 to 999!");
    break;
   }
   int hundreds = number / 100;
   int tens = (number / 10) % 10;
   int units = number % 10;
   std::string result = "";
  
   switch (hundreds) {
   case 1: result += "one hundred "; break;
   case 2: result += "two hundred "; break;
   case 3: result += "three hundred "; break;
   case 4: result += "four hundred "; break;
   case 5: result += "five hundred "; break;
   case 6: result += "six hundred "; break;
   case 7: result += "seven hundred "; break;
   case 8: result += "eight hundred "; break;
   case 9: result += "nine hundred "; break;
   }

   if (tens == 1) {
    int teens = tens * 10 + units;
    switch (teens) {
    case 10: result += "ten"; break;
    case 11: result += "eleven"; break;
    case 12: result += "twelve"; break;
    case 13: result += "thirteen"; break;
    case 14: result += "fourteen"; break;
    case 15: result += "fifteen"; break;
    case 16: result += "sixteen"; break;
    case 17: result += "seventeen"; break;
    case 18: result += "eighteen"; break;
    case 19: result += "nineteen"; break;
    }
   }
   else {
    switch (tens) {
    case 2: result += "twenty "; break;
    case 3: result += "thirty "; break;
    case 4: result += "forty "; break;
    case 5: result += "fifty "; break;
    case 6: result += "sixty "; break;
    case 7: result += "seventy "; break;
    case 8: result += "eighty "; break;
    case 9: result += "ninety "; break;
    }

    switch (units) {
    case 1: result += "one"; break;
    case 2: result += "two"; break;
    case 3: result += "three"; break;
    case 4: result += "four"; break;
    case 5: result += "five"; break;
    case 6: result += "six"; break;
    case 7: result += "seven"; break;
    case 8: result += "eight"; break;
    case 9: result += "nine"; break;
    }
   }

   if (!result.empty() && result.back() == ' ') {
    result.pop_back();
   }

   std::println("Result: \"{}\"", result);
   break;
  }
  case 9: {
   int a, b;
   std::print("[Task 9] Enter an integer a: ");
   std::cin >> a;
   std::print("Enter an integer b (greater than a): ");
   std::cin >> b;

   if (a >= b) {
    std::println("Error: number a must be strictly less than b!");
    break;
   }

   std::print("Numbers between {} and {}: ", a, b);

   for (int i = a; i <= b; ++i) {
    std::print("{} ", i);
   }
   std::println(""); 

   int count = b - a + 1;
   std::println("Count n of these numbers: {}", count);
   break;
  }
  case 10: {
   double a;
   int n;
   std::print("[Task 10] Enter a real number a: ");
   std::cin >> a;
   std::print("Enter an integer n (n > 0): ");
   std::cin >> n;

   if (n <= 0) {
    std::println("Error: number n must be greater than 0!");
    break;
   }

   double current_power = 1.0;

   std::println("Powers of {} from 1 to {}:", a, n);
   for (int i = 1; i <= n; ++i) {
    current_power *= a;
    std::println("{}^{} = {}", a, i, current_power);
   }
   break;
  }

  default:
   std::println("Error: no task with this number exists!");
   break;
  }
  std::println("----------------------------------------");
 }

 return 0;
}
