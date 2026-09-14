#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>

// ==========================================
// HELPER FUNCTIONS
// ==========================================

// Helper function to find the index of a character in the alphabet
int findIndex(char symbol, const std::string& alphabet) {
    for (size_t i = 0; i < alphabet.length(); ++i) {
        if (alphabet[i] == symbol) {
            return static_cast<int>(i);
        }
    }
    return -1; // Return -1 if character is not in the alphabet
}

// ==========================================
// TASK 1: SHIFT CIPHER (CAESAR CIPHER)
// ==========================================

// Encrypts text using shift substitution: Y = (X + K) mod N
std::string EncryptShift(const std::string& text, const std::string& alphabet, int shift) {
    std::string result = "";
    int N = static_cast<int>(alphabet.length());
    if (N == 0) return text;

    shift = (shift % N + N) % N; // Normalize negative shifts

    for (char symbol : text) {
        int index = findIndex(symbol, alphabet);
        if (index != -1) {
            int new_index = (index + shift) % N;
            result += alphabet[new_index];
        }
        else {
            result += symbol; // Leave non-alphabet characters unchanged
        }
    }
    return result;
}

// Decrypts shift cipher text: X = (Y - K + N) mod N
std::string DecryptShift(const std::string& text, const std::string& alphabet, int shift) {
    return EncryptShift(text, alphabet, -shift);
}

// ==========================================
// TASK 2: SIMPLE SUBSTITUTION CIPHER
// ==========================================

// Handles loading, user input validation, or random generation of the substitution key table
std::string GetSubstitutionTable(const std::string& alphabet, const std::string& userKeyInput = "", const std::string& filename = "keytable.txt") {
    // 1. Check if the user provided a key string or a key file path
    if (!userKeyInput.empty()) {
        std::ifstream userFile(userKeyInput);
        if (userFile.is_open()) {
            std::string fileKey;
            std::getline(userFile, fileKey);
            userFile.close();
            if (fileKey.length() == alphabet.length()) {
                std::cout << "[Info] Loaded substitution table from file: " << userKeyInput << std::endl;
                return fileKey;
            }
        }
        if (userKeyInput.length() == alphabet.length()) {
            std::cout << "[Info] Using user-provided substitution key string." << std::endl;
            return userKeyInput;
        }
    }

    // 2. Read from an existing default file
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string savedKey;
        std::getline(inFile, savedKey);
        inFile.close();
        if (savedKey.length() == alphabet.length()) {
            std::cout << "[Info] Loaded substitution table from file: " << filename << std::endl;
            return savedKey;
        }
    }

    // 3. Generate a new key table and save it to a file
    std::cout << "[Info] Substitution table not found. Generating a new one..." << std::endl;
    std::string keyTable = alphabet;
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::shuffle(keyTable.begin(), keyTable.end(), rng);

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << keyTable; // Save the shuffled alphabet string to the text file
        outFile.close();
        std::cout << "[Success] New substitution table saved to file: " << filename << std::endl;
    }

    return keyTable;
}

// Encrypts text using simple monoalphabetic substitution
std::string EncryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char symbol : text) {
        int pos = findIndex(symbol, alphabet);
        if (pos != -1) {
            result += keyTable[pos];
        }
        else {
            result += symbol;
        }
    }
    return result;
}

// Decrypts text using simple monoalphabetic substitution
std::string DecryptSubst(const std::string& text, const std::string& alphabet, const std::string& keyTable) {
    std::string result = "";
    for (char symbol : text) {
        int pos = findIndex(symbol, keyTable);
        if (pos != -1) {
            result += alphabet[pos];
        }
        else {
            result += symbol;
        }
    }
    return result;
}

// ==========================================
// MAIN FUNCTION (LOOPED INTERACTIVE MENU)
// ==========================================

int main(int argc, char* argv[]) {
#ifdef _WIN32
    system("chcp 1251 > nul"); // Set console code page to CP1251 for Windows Cyrillic support
#endif

    std::string default_alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789 .,!?";

    int cipher_type = 1;
    std::string alphabet;
    std::string mode;
    std::string text;
    int shift = 0;
    std::string userKeyInput = "";

    // --- MODE 1: Command Line Arguments Execution ---
    if (argc >= 5) {
        cipher_type = std::stoi(argv[1]);
        alphabet = argv[2];
        mode = argv[3];

        if (cipher_type == 1 && argc >= 6) {
            shift = std::stoi(argv[4]);
            text = argv[5];
        }
        else if (cipher_type == 2) {
            text = argv[4];
            if (argc >= 6) userKeyInput = argv[5];
        }

        std::cout << "\n--- RESULT ---" << std::endl;
        std::cout << "Alphabet size (N): " << alphabet.length() << std::endl;

        if (cipher_type == 1) {
            if (mode == "enc" || mode == "1") {
                std::cout << "Shift Cipher Result: " << EncryptShift(text, alphabet, shift) << std::endl;
            }
            else {
                std::cout << "Shift Decipher Result: " << DecryptShift(text, alphabet, shift) << std::endl;
            }
        }
        else if (cipher_type == 2) {
            std::string keyTable = GetSubstitutionTable(alphabet, userKeyInput);
            std::cout << "Key Table: " << keyTable << std::endl;
            if (mode == "enc" || mode == "1") {
                std::cout << "Substitution Cipher Result: " << EncryptSubst(text, alphabet, keyTable) << std::endl;
            }
            else {
                std::cout << "Substitution Decipher Result: " << DecryptSubst(text, alphabet, keyTable) << std::endl;
            }
        }
        return 0;
    }

    // --- MODE 2: Looped Interactive Console Menu ---
    while (true) {
        std::cout << "\n==========================================" << std::endl;
        std::cout << "=== CIPHER LAB PROGRAM ===" << std::endl;
        std::cout << "Select option:" << std::endl;
        std::cout << " 1. Shift Cipher" << std::endl;
        std::cout << " 2. Substitution Cipher" << std::endl;
        std::cout << " 0. Exit" << std::endl;
        std::cout << "Your choice: ";

        if (!(std::cin >> cipher_type)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        // Exit application if option '0' is chosen
        if (cipher_type == 0) {
            std::cout << "\nExiting application..." << std::endl;
            break;
        }

        if (cipher_type != 1 && cipher_type != 2) {
            std::cout << "Invalid choice! Please try again." << std::endl;
            continue;
        }

        std::cin.ignore(); // Flush input buffer after reading integer choice
        std::cout << "\n1. Enter alphabet (Press Enter for default):\n " << default_alphabet << "\n> ";
        std::getline(std::cin, alphabet);
        if (alphabet.empty()) alphabet = default_alphabet;

        std::cout << "2. Select mode (1 - Encrypt, 2 - Decrypt): ";
        int mode_choice;
        std::cin >> mode_choice;
        mode = (mode_choice == 1) ? "enc" : "dec";

        if (cipher_type == 1) {
            std::cout << "3. Enter shift value (K): ";
            std::cin >> shift;
            std::cin.ignore();
        }
        else {
            std::cin.ignore();
            std::cout << "3. Enter key table / file path (Press Enter to auto-generate/load keytable.txt): ";
            std::getline(std::cin, userKeyInput);
        }

        std::cout << "4. Enter text to process: ";
        std::getline(std::cin, text);

        std::cout << "\n--- RESULT ---" << std::endl;
        std::cout << "Alphabet size (N): " << alphabet.length() << std::endl;

        if (cipher_type == 1) {
            if (mode == "enc" || mode == "1") {
                std::cout << "Shift Cipher Result: " << EncryptShift(text, alphabet, shift) << std::endl;
            }
            else {
                std::cout << "Shift Decipher Result: " << DecryptShift(text, alphabet, shift) << std::endl;
            }
        }
        else if (cipher_type == 2) {
            std::string keyTable = GetSubstitutionTable(alphabet, userKeyInput);
            std::cout << "Key Table: " << keyTable << std::endl;

            if (mode == "enc" || mode == "1") {
                std::cout << "Substitution Cipher Result: " << EncryptSubst(text, alphabet, keyTable) << std::endl;
            }
            else {
                std::cout << "Substitution Decipher Result: " << DecryptSubst(text, alphabet, keyTable) << std::endl;
            }
        }
    }

    return 0;
}