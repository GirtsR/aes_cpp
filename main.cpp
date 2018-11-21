/**
 * Created by Ģirts Rudzišs, Emīls Ozoliņš
 *
 */

#include <iostream>

std::string hex_to_bin(std::string hex) {
    std::string binary;
    for (int i = 0; i < hex.length(); i++) {
        switch (std::toupper(hex[i])) {
            case '0':binary.append("0000");
                break;
            case '1':binary.append("0001");
                break;
            case '2':binary.append("0010");
                break;
            case '3':binary.append("0011");
                break;
            case '4':binary.append("0100");
                break;
            case '5':binary.append("0101");
                break;
            case '6':binary.append("0110");
                break;
            case '7':binary.append("0111");
                break;
            case '8':binary.append("1000");
                break;
            case '9':binary.append("1001");
                break;
            case 'A':binary.append("1010");
                break;
            case 'B':binary.append("1011");
                break;
            case 'C':binary.append("1100");
                break;
            case 'D':binary.append("1101");
                break;
            case 'E':binary.append("1110");
                break;
            case 'F':binary.append("1111");
                break;
        }
    }
    return binary;
}

std::string bin_to_hex(std::string binary) {
    std::string hex;
    for (int i = 0; i < binary.length(); i += 4) {
        std::string digits = binary.substr(i, 4);
        if (digits.compare("0000") == 0) hex += '0';
        else if (digits.compare("0001") == 0) hex += '1';
        else if (digits.compare("0010") == 0) hex += '2';
        else if (digits.compare("0011") == 0) hex += '3';
        else if (digits.compare("0100") == 0) hex += '4';
        else if (digits.compare("0101") == 0) hex += '5';
        else if (digits.compare("0110") == 0) hex += '6';
        else if (digits.compare("0111") == 0) hex += '7';
        else if (digits.compare("1000") == 0) hex += '8';
        else if (digits.compare("1001") == 0) hex += '9';
        else if (digits.compare("1010") == 0) hex += 'A';
        else if (digits.compare("1011") == 0) hex += 'B';
        else if (digits.compare("1100") == 0) hex += 'C';
        else if (digits.compare("1101") == 0) hex += 'D';
        else if (digits.compare("1110") == 0) hex += 'E';
        else if (digits.compare("1111") == 0) hex += 'F';
    }
    return hex;
}

int main() {
    std::string plaintext;
    std::string input;

    while (true) {
        std::cout << "Please enter a 128 bit or 32 hex digit plaintext: ";
        std::cin >> input;
        if (input.length() == 16) {
            plaintext = hex_to_bin(input);
            std::cout << "Entered hex, binary representation: " << plaintext << std::endl;
            break;
        } else if (input.length() == 64) {
            plaintext = input;
            std::string hex = bin_to_hex(plaintext);
            std::cout << "Entered binary, hex representation: " << hex << std::endl;
            break;
        } else {
            std::cout << "Incorrect plaintext length" << std::endl;
        }
    }

    std::string key;
    while (true) {
        std::cout << "Please enter a 128, 192 or 256 bit key: ";
        std::cin >> key;
        size_t key_len = key.length();
        if (key_len == 128 || key_len == 192 || key_len == 256) {
            break;
        } else {
            std::cout << "Incorrect key length";
        }
    }
    return 0;
}