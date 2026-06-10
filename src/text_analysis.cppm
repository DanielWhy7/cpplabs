module;
import std;
export module text_analyzer;

export std::string normalize_word(std::string word) {
  for (char& c : word) {
    c = std::tolower(static_cast<unsigned char>(c));
  }
  
  while (!word.empty() && !std::isalpha(static_cast<unsigned char>(word.front()))) {
    word.erase(0, 1);
  }
  
  while (!word.empty() && !std::isalpha(static_cast<unsigned char>(word.back()))) {
    word.pop_back();
  }
  
  if (word.empty()) {
    return "";
  }
  
  for (char c : word) {
    if (!std::isalpha(static_cast<unsigned char>(c)) && c != '-') {
      return "";
    }
  }
  
  if (!word.empty() && (word.front() == '-' || word.back() == '-')) {
    return "";
  }
  
  for (std::size_t i = 0; i + 1 < word.length(); ++i) {
    if (word[i] == '-' && word[i + 1] == '-') {
      return "";
    }
  }
  
  return word;
}

export std::vector<std::string> load_file(const std::string& filepath) {
  std::vector<std::string> words;
  std::ifstream file(filepath);
  
  if (!file.is_open()) {
    return words;
  }
  
  std::string word;
  while (file >> word) {
    std::string normalized = normalize_word(word);
    if (!normalized.empty()) {
      words.push_back(normalized);
    }
  }
  
  file.close();
  return words;
}
export std::size_t count_unique_words(
  const std::vector<std::string>& words,
  const std::unordered_set<std::string>& stop_words) {
  
  std::unordered_set<std::string> unique_words;
  
  for (const auto& word : words) {
    if (stop_words.find(word) == stop_words.end()) {
      unique_words.insert(word);
    }
  }
  
  return unique_words.size();
}

export std::pair<std::size_t, std::set<std::string>> find_most_frequent_words(
  const std::vector<std::string>& words,
  const std::unordered_set<std::string>& stop_words) {
  
  std::unordered_map<std::string, std::size_t> word_count;
  std::size_t max_count = 0;
  
  for (const auto& word : words) {
    if (stop_words.find(word) == stop_words.end()) {
      word_count[word]++;
      max_count = std::max(max_count, word_count[word]);
    }
  }
  
  std::set<std::string> most_frequent;
  
  for (const auto& [word, count] : word_count) {
    if (count == max_count) {
      most_frequent.insert(word);
    }
  }
  
  return {max_count, most_frequent};
}
