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

// That's not the main point of the task, so it was simplified


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

const std::string BOOK_PATH = "..\\resources\\book.txt";

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


int main()
{
    // Parse the book    
    std::vector<std::string> words = parseBook(BOOK_PATH);

    std::cout << "words[0]: " << words[0] << std:: endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
