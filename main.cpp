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
        if (digits == "0000") hex += '0';
        else if (digits == "0001") hex += '1';
        else if (digits == "0010") hex += '2';
        else if (digits == "0011") hex += '3';
        else if (digits == "0100") hex += '4';
        else if (digits == "0101") hex += '5';
        else if (digits == "0110") hex += '6';
        else if (digits == "0111") hex += '7';
        else if (digits == "1000") hex += '8';
        else if (digits == "1001") hex += '9';
        else if (digits == "1010") hex += 'A';
        else if (digits == "1011") hex += 'B';
        else if (digits == "1100") hex += 'C';
        else if (digits == "1101") hex += 'D';
        else if (digits == "1110") hex += 'E';
        else if (digits == "1111") hex += 'F';
    }
    return hex;
}

int main() {
    std::string plaintext;
    std::string input;

    while (true) {
        std::cout << "Please enter a 128 bit or 32 hex digit plaintext: ";
        std::cin >> input;
        if (input.length() == 32) {
            plaintext = hex_to_bin(input);
            std::cout << "Entered hex, binary representation: " << plaintext << std::endl;
            break;
        } else if (input.length() == 128) {
            plaintext = input;
            std::string hex = bin_to_hex(plaintext);
            std::cout << "Entered binary, hex representation: " << hex << std::endl;
            break;
        } else {
            std::cout << "Incorrect plaintext length" << std::endl;
        }
    }

    std::string key;
    unsigned int number_of_rounds;
    while (true) {
        std::cout << "Please enter a 128, 192 or 256 bit key: ";
        std::cin >> key;
        size_t key_len = key.length();
        if (key_len == 128) {
            number_of_rounds = 10;
            break;
        } else if (key_len == 192) {
            number_of_rounds = 12;
            break;
        } else if (key_len == 256) {
            number_of_rounds = 14;
            break;
        } else {
            std::cout << "Incorrect key length" << std::endl;
        }
    }

    for (unsigned int i = 1; i <= number_of_rounds; i++) {
        std::cout << "Round " << i << ": ";
        //TODO - do stuff
    }
    return 0;
}