#include "Utils.h"
#include <regex>
#include <iostream>
#include <string>

static std::wstring StringToWString(const std::string& str) {
    std::wstring wstr;
    wstr.reserve(str.length());
    for (char c : str) {
        wstr += static_cast<wchar_t>(static_cast<unsigned char>(c));
    }
    return wstr;
}

static std::string WStringToString(const std::wstring& wstr) {
    std::string str;
    str.reserve(wstr.length());
    for (wchar_t wc : wstr) {
        str += static_cast<char>(wc);
    }
    return str;
}

int findIndex(char symbol, const std::string& alphabet) {
    for (size_t i = 0; i < alphabet.length(); ++i) {
        if (alphabet[i] == symbol) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::string BuildAlphabetFromRegex(const std::string& defaultAlphabet, const std::string& userPattern) {
    if (userPattern.empty()) {
        return defaultAlphabet;
    }

    std::wstring wDefault = StringToWString(defaultAlphabet);
    std::wstring wPattern = StringToWString(userPattern);

    if (wPattern.front() != L'[') {
        wPattern = L"[" + wPattern;
    }
    if (wPattern.back() != L']') {
        wPattern = wPattern + L"]";
    }

    for (size_t i = 1; i + 2 < wPattern.length(); ++i) {
        if (wPattern[i] == L'-') {
            wchar_t start = wPattern[i - 1];
            wchar_t end = wPattern[i + 1];
            if (start > end) {
                wPattern[i - 1] = end;
                wPattern[i + 1] = start;
            }
        }
    }

    std::wstring wResult;
    try {
        std::wregex reg(wPattern);
        for (wchar_t wc : wDefault) {
            std::wstring s(1, wc);
            if (std::regex_match(s, reg)) {
                wResult += wc;
            }
        }
    }
    catch (const std::regex_error&) {
        std::cout << "\n[Error] Invalid regex syntax! Defaulting to full alphabet.\n";
        return "";
    }

    return WStringToString(wResult);
}