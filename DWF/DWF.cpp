// DWF.cpp : This file contains the 'main' function. Program execution begins and ends there.
/**
* 
* Part 1: Data Structures and Algorithms
Create a data-set of words from the book https://www.gutenberg.org/files/98/98-0.txt. Implement a
fixed sized hash table by using linear probing to resolve collisions. Assume that the keys are the
words from the given data-set and the hash table’s values are integers. You need to implement the
following functions with O(1)-complexity:
◦ insert(key, value): inserts a new key-value pair or replaces a key’s existing
value,
◦ remove(key): removes the corresponding key-value pair,
◦ get(key): returns the value of the corresponding key,
◦ get_last(): returns the most recently inserted or changed key-value pair,
◦ get_first(): returns the least recently inserted or changed key-value pair
**/
// Task 1
// Alternative Solutions: there could be instead of linear probing- chaining to handle collisions by storing linked lists of key-value pairs at each index. 
// This would lead to non-O(1) time complexity for insertion and retrieval in case of long chains.
// Dynamic resizing of the hash table: there could be dynamically resized the hash table when it's nearly ful. However, this adds complexity
// and is here not required.
// Tracking Insertions: first_index and last_index keep track of the first and last inserted or updated keys.
// Word Parsing: The parseBook() function reads the book, splits it into words, removes punctuation, and converts them to lowercase.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

const std::string BOOK_PATH = "..\\resources\\book.txt";

const int TABLE_SIZE = 10000;

struct HashEntry {
    std::string key;
    int value;
    bool isOccupied;
    bool isDeleted;
};

class HashTable {
private:
    std::vector<HashEntry> table;
    int first_index;
    int last_index;

    // Hash function
    int hashFunction(const std::string& key) {
        const int p = 31;
        const int m = TABLE_SIZE;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : key) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }

public:
    HashTable() : table(TABLE_SIZE), first_index(-1), last_index(-1) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].isOccupied = false;
            table[i].isDeleted = false;
        }
    }

    // Insert key-value pair (or update)
    void insert(const std::string& key, int value) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index].isOccupied && table[index].key != key) {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                std::cerr << "Hash table is full!" << std::endl;
                return;
            }
        }

        // Update first/last index for insertion order tracking
        if (!table[index].isOccupied || table[index].isDeleted) {
            if (first_index == -1) first_index = index;  // First insert
            last_index = index;  // Always update last
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
    
    }

    // Remove key-value pair
    void remove(const std::string& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index].isOccupied) {
            if (table[index].key == key && !table[index].isDeleted) {
                table[index].isDeleted = true;
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) return;
        }
        std::cerr << "Key not found!" << std::endl;
    }

    // Get value by key
    int get(const std::string& key) {
        int index = hashFunction(key);
        int originalIndex = index;
        while (table[index].isOccupied) {
            if (table[index].key == key && !table[index].isDeleted) {
                return table[index].value;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) break;
        }
        std::cerr << "Key not found!" << std::endl;
        return -1;
    }

    // Get the most recently inserted key-value pair
    std::pair<std::string, int> get_last() {
        if (last_index != -1 && table[last_index].isOccupied && !table[last_index].isDeleted) {
            return { table[last_index].key, table[last_index].value };
        }
        return { "", -1 };
    }

    // Get the least recently inserted key-value pair
    std::pair<std::string, int> get_first() {
        if (first_index != -1 && table[first_index].isOccupied && !table[first_index].isDeleted) {
            return { table[first_index].key, table[first_index].value };
        }
        return { "", -1 };
    }

};

// Parse words from a book file
static std::vector<std::string> parseBook(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;
    if (file.is_open()) {
        while (file >> word) {
            // Remove punctuation and convert to lowercase
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return ::ispunct(c); }),
                word.end());
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            words.push_back(word);
        }
        file.close();
    }
    return words;
}
/*
* End of the task 1
*/

int main()
{
    /*
    * Task 1
    */
    HashTable hashTable;

    // Parse the book    
    std::vector<std::string> words = parseBook(BOOK_PATH);

    std::cout << "words[0]: " << words[0] << std:: endl;
    std::cout << "words[1]: " << words[1] << std::endl;
    std::cout << "words[2]: " << words[2] << std::endl;
    std::cout << "words[3]: " << words[3] << std::endl;

    // Example usage
    std::string key = "charles";
    std::cout << "Value for key '" << key << "': " << hashTable.get(key) << std::endl;

    auto last = hashTable.get_last();
    std::cout << "Last inserted: (" << last.first << ", " << last.second << ")" << std::endl;

    auto first = hashTable.get_first();
    std::cout << "First inserted: (" << first.first << ", " << first.second << ")" << std::endl;
    /*
    * End of the task 1
    */
    return 0;
}

