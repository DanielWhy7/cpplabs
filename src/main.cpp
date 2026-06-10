import std;
import text_analyzer;

void print_line() {
  std::println("--------------------");
}

int main(int argc, char* argv[]) {
  if (argc > 2) {
    std::println("Usage: {} <about>", argv[0]);
    return 1;
  }

  if (argc == 2 && std::strcmp(argv[1], "about") == 0) {
    print_line();
    std::println("   Lab №: 5");
    std::println("  Group: 6114");
    std::println("  Author: Bikmetov Daniel");
    std::println(" Variant: 1");
    print_line();
    return 0;
  }

  print_line();

  std::string filename = "input.txt";
  
  std::vector<std::string> words = load_file(filename);
  
  if (words.empty()) {
    std::println("Error: could not load file or file is empty.");
    return 1;
  }

  std::unordered_set<std::string> stop_words = {
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
    "has", "have", "he", "her", "his", "i", "if", "in", "is", "it",
    "its", "me", "my", "no", "of", "on", "or", "she", "that", "the",
    "to", "was", "we", "what", "which", "who", "will", "with", "you",
    "your", "not", "can", "could", "would", "should", "may", "might",
    "must", "shall", "do", "does", "did", "been", "being", "than",
    "just", "between", "about", "up", "out", "into", "through", "during",
    "before", "after", "above", "below", "over", "under", "again",
    "further", "then", "there", "where", "why", "how", "all", "each",
    "every", "both", "few", "more", "most", "some", "such", "only",
    "same", "so", "very", "but"
  };

  std::println("\nAnalysis of text from file:");
  std::println("\"{}\"", filename);

  std::println("\nTotal number of words in text: {}.", words.size());

  std::println("\nStop words:");
  std::cout << "\"";
  bool first = true;
  for (const auto& word : stop_words) {
    if (!first) std::cout << "\" \"";
    std::cout << word;
    first = false;
  }
  std::println("\"");

  std::size_t unique_count = count_unique_words(words, stop_words);
  std::println("\nNumber of unique words: {}", unique_count);

  auto [max_frequency, most_frequent] = find_most_frequent_words(words, stop_words);
  
  std::println("\nNumber of occurrences of the most popular word: {}", max_frequency);

  std::println("\nMost popular words:");
  for (const auto& word : most_frequent) {
    std::println("\"{}\"", word);
  }

  print_line();

  return 0;
}
