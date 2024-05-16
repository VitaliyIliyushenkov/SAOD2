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
    char value;
    std::unordered_map<char, std::shared_ptr<TrieNode>> children;
    std::unordered_set<char> childs;
    bool isEndOfWord;
    int count;

    TrieNode(char val) : value(val), isEndOfWord(false), count(0) {}
};

class Trie {
public:
    Trie() : root(std::make_shared<TrieNode>('\0')), nodeCount(1) {}

    void insert(const std::string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_shared<TrieNode>(ch);
                current->childs.insert(ch);
                ++nodeCount;
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
        ++current->count;
    }

    int find(const std::string& word) {
        auto current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return 0;
            }
            current = current->children[ch];
        }
        return current->isEndOfWord ? current->count : 0;
    }

    size_t size() {
        return sizeCount(root);
    }

    size_t NodeCount() {
        return nodeCount;
    }

private:
    std::shared_ptr<TrieNode> root;
    size_t nodeCount;

    size_t sizeCount(const std::shared_ptr<TrieNode>& node) {
        size_t count = 0;
        if (node->isEndOfWord) {
            count++;
        }
        for (const auto& child : node->children) {
            count += sizeCount(child.second);
        }
        return count;
    }
};

void triedict(const std::string& text, std::string word) {
    Trie trie;
    string str = "";
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

    cout << "\ndict size: " << trie.size() << endl;
    cout << "nodecount" << ": " << trie.NodeCount() << endl;
    cout << word << ": " << trie.find(word) << endl;
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
    triedict(text, word);
    auto time_two = chrono::high_resolution_clock::now();
    cout << "trie\t" << chrono::duration<double>(time_two - time_one).count() << endl;

    time_one = chrono::high_resolution_clock::now();
    umap(text, word);
    time_two = chrono::high_resolution_clock::now();
    cout << "umap\t" << chrono::duration<double>(time_two - time_one).count() << endl;

    time_one = chrono::high_resolution_clock::now();
    umap_slice(text, word);
    time_two = chrono::high_resolution_clock::now();
    cout << "smap\t" << chrono::duration<double>(time_two - time_one).count() << endl;

    return 0;
}