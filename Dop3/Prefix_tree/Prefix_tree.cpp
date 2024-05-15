#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
using namespace std;


class TrieNode {
public:
    TrieNode() : is_end_of_word(false), count(0) {}

    void insert(const std::string& word, size_t index = 0) {
        if (index == word.size()) {
            is_end_of_word = true;
            count++;
        }
        else {
            char c = word[index];
            if (children.find(c) == children.end()) {
                children.insert(std::make_pair(c, std::make_unique<TrieNode>()));
            }
            children[c]->insert(word, index + 1);
        }
    }

    size_t find(const std::string& word, size_t index = 0) const {
        if (index == word.size()) {
            return count;
        }
        char c = word[index];
        if (children.find(c) == children.end()) {
            return 0;
        }
        return children.at(c)->find(word, index + 1);
    }

    size_t size() const {
        size_t total = 0;
        if (is_end_of_word) {
            total += count;
        }
        for (const auto& child : children) {
            total += child.second->size();
        }
        return total;
    }

    size_t NodeCount() const {
        size_t total = 1; // Считаем текущий узел
        for (const auto& child : children) {
            total += child.second->NodeCount();
        }
        return total;
    }

private:
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    bool is_end_of_word;
    size_t count;
};

void trieDict(const std::string& text, std::string word) {
    TrieNode trie;
    std::string str = "";
    for (const auto& ch : text) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'') {
            str += ch;
        }
        else if (str.size() > 0) {
            trie.insert(str);
            str = "";
        }
    }
    if (str.size() > 0) {
        trie.insert(str);
    }
    std::cout << "\ntrie size: " << trie.size() << std::endl;
    std::cout << word << ": " << trie.find(word) << std::endl;
    std::cout << "Node count: " << trie.NodeCount() << std::endl;
}

void umapdict(const std::string& text, std::string word) {
    std::unordered_map<std::string, size_t> umap;
    std::istringstream iss(text);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        umap[token]++;
    }
    std::cout << "Number of occurrences of '" << word << "': " << umap[word] << std::endl;
    std::cout << "Total unique words in std::unordered_map: " << umap.size() << std::endl;
}

void umap(const std::string& text, std::string word)
{
    using namespace std;
    unordered_map<std::string, size_t> dict;
    string str = "";
    for (const auto& ch : text) // кроме последнего слова
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
            str += ch;
        else if (str.size() > 0)
        {
            ++dict[str];
            str = "";
        }
    }
    cout << "\ndict size: " << dict.size() << endl;
    cout << word << ": " << dict[word] << endl;
}

struct hash_pair {
    size_t operator()(const std::pair<const char*, size_t>& p) const {
        return std::hash<std::string>{}(std::string(p.first, p.second));
    }
};

struct equal_pair
{
    bool operator()(const std::pair<const char*, size_t>& lhs, const std::pair<const char*, size_t>& rhs) const
    {
        return std::strncmp(lhs.first, rhs.first, rhs.second) == 0;
    }
};

void umap_slice(const std::string& text, std::string word)
{
    using namespace std;
    unordered_map<pair<const char*, size_t>, size_t, hash_pair, equal_pair> dict;
    pair<const char*, size_t> p;
    for (size_t i = 0, j = 0; i < text.size(); i++) // кроме последнего слова
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') || text[i] == '\'')
            ++j;
        else if (j > 0)
        {
            ++dict[{text.c_str() + i - j, j}];
            j = 0;
        }
    }
    cout << "\ndict size: " << dict.size() << endl;
    cout << word << ": " << dict[{word.c_str(), word.length()}] << endl;
}

int main() {

    using namespace std;
    string text;
    ifstream fin("text.txt", ios::binary);
    if (!fin.is_open())
    {
        cout << "not open!" << endl;
        return 0;
    }
    text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    string word = "wiki"; // слово которое ищем
    auto time_one = chrono::high_resolution_clock::now();
    umap(text, word);
    auto time_two = chrono::high_resolution_clock::now();
    cout << "umap\t" << chrono::duration<double>(time_two - time_one).count() << endl;

    time_one = chrono::high_resolution_clock::now();
    umap_slice(text, word);
    time_two = chrono::high_resolution_clock::now();
    cout << "smap\t" << chrono::duration<double>(time_two - time_one).count() << endl;

    time_one = chrono::high_resolution_clock::now();
    trieDict(text, word);
    time_two = chrono::high_resolution_clock::now();
    cout << "trie\t" << chrono::duration<double>(time_two - time_one).count() << endl;


    return 0;
}