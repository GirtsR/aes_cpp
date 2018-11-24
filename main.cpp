/**
 * Created by Ģirts Rudzišs, Emīls Ozoliņš
 *
 *
 * 00010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001
 */

#include <iostream>
#include <bitset>
#include <queue>
#include <iomanip>

#define STATE_COLUMNS 4
#define BIT_8_MASK 0b11111111
#define BIT_4_MASK 0b1111

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

int hex_to_decimal(char hex) {
    if (hex == '0') return 0;
    else if (hex == '1') return 1;
    else if (hex == '2') return 2;
    else if (hex == '3') return 3;
    else if (hex == '4') return 4;
    else if (hex == '5') return 5;
    else if (hex == '6') return 6;
    else if (hex == '7') return 7;
    else if (hex == '8') return 8;
    else if (hex == '9') return 9;
    else if (hex == 'a' || hex == 'A') return 10;
    else if (hex == 'b' || hex == 'B') return 11;
    else if (hex == 'c' || hex == 'C') return 12;
    else if (hex == 'd' || hex == 'D') return 13;
    else if (hex == 'e' || hex == 'E') return 14;
    else if (hex == 'f' || hex == 'F') return 15;
    else return -1;
}

std::string xor_32(std::string block1, std::string block2) {
    auto bitset = std::bitset<32>(block1) ^std::bitset<32>(block2);
    return bitset.to_string();
}

static unsigned long s_box[16][16] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

std::string hex_to_string(unsigned long hex) {
    std::stringstream s;
    s << std::setfill('0') << std::setw(2) << std::hex << hex;
    return s.str();
}

std::string SubWord(std::string temp) {
    std::string result;

    for (int i = 0; i < 4; i++) {
        std::string byte = temp.substr(i * 8, 8);
        std::string hex_old = bin_to_hex(byte);
        unsigned long hex = s_box[hex_to_decimal(hex_old[0])][hex_to_decimal(hex_old[1])];
        result += hex_to_string(hex);
    }
    result = hex_to_bin(result);
    return result;
}

std::string RotWord(std::string temp) {
    std::string parts[4];
    for (int i = 0; i < 4; i++) {
        parts[i] = temp.substr(i * 8, 8);
    }
    std::string result = parts[1] + parts[2] + parts[3] + parts[0];
    return result;

}

void AddRoundKey(unsigned long (&state)[4][STATE_COLUMNS], std::string w[], unsigned int round) {
    unsigned l = round * STATE_COLUMNS;

    std::cout << "Key schedule: ";
    for (int col = 0; col < STATE_COLUMNS; col++) {
        unsigned long column = 0;
        for (int i = 0; i < 4; i++) {
            column = column << 8 | state[i][col];
        }
        std::cout << bin_to_hex(w[l + col]);
        unsigned long word = std::stoul(w[l + col], nullptr, 2);
        unsigned long tmp = column ^word;

        for (int i = 3; i >= 0; i--) {
            state[i][col] = tmp & BIT_8_MASK;
            tmp >>= 8;
        }
    }
    std::cout << std::endl;
}

void SubBytes(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int col = 0; col < STATE_COLUMNS; col++) {
        for (int row = 0; row < 4; row++) {
            unsigned long row_nr = state[row][col] >> 4; // Second digit
            unsigned long col_nr = state[row][col] & BIT_4_MASK; // first digit
            state[row][col] = s_box[row_nr][col_nr];
        }
    }
}

void ShiftRows(unsigned long (&state)[4][STATE_COLUMNS]) {
    int row_len = 4;
    for (int row = 0; row < row_len; row++) {
        int shift_pos = row;
        std::queue<unsigned long> tmp;
        for (int pos = 0; pos < shift_pos; pos++) {
            tmp.push(state[row][pos]);
        }
        for (int pos = shift_pos; pos < row_len; pos++) {
            state[row][pos - shift_pos] = state[row][pos];
        }
        for (int pos = row_len - shift_pos; pos < row_len; pos++) {
            state[row][pos] = tmp.front();
            tmp.pop();
        }
    }
}

unsigned char field_mul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void MixColumns(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int i = 0; i < STATE_COLUMNS; i++) {
        unsigned long tmp0 = field_mul(state[0][i], 2) ^field_mul(state[3][i], 1) ^field_mul(state[2][i], 1) ^field_mul(state[1][i], 3);
        unsigned long tmp1 = field_mul(state[1][i], 2) ^field_mul(state[0][i], 1) ^field_mul(state[3][i], 1) ^field_mul(state[2][i], 3);
        unsigned long tmp2 = field_mul(state[2][i], 2) ^field_mul(state[1][i], 1) ^field_mul(state[0][i], 1) ^field_mul(state[3][i], 3);
        unsigned long tmp3 = field_mul(state[3][i], 2) ^field_mul(state[2][i], 1) ^field_mul(state[1][i], 1) ^field_mul(state[0][i], 3);

        state[0][i] = tmp0;
        state[1][i] = tmp1;
        state[2][i] = tmp2;
        state[3][i] = tmp3;
    }
}

void InvMixColumns(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int i = 0; i < STATE_COLUMNS; i++) {
        unsigned long tmp0 = field_mul(state[0][i], 14) ^field_mul(state[3][i], 9) ^field_mul(state[2][i], 13) ^field_mul(state[1][i], 11);
        unsigned long tmp1 = field_mul(state[1][i], 14) ^field_mul(state[0][i], 9) ^field_mul(state[3][i], 13) ^field_mul(state[2][i], 11);
        unsigned long tmp2 = field_mul(state[2][i], 14) ^field_mul(state[1][i], 9) ^field_mul(state[0][i], 13) ^field_mul(state[3][i], 11);
        unsigned long tmp3 = field_mul(state[3][i], 14) ^field_mul(state[2][i], 9) ^field_mul(state[1][i], 13) ^field_mul(state[0][i], 11);

        state[0][i] = tmp0;
        state[1][i] = tmp1;
        state[2][i] = tmp2;
        state[3][i] = tmp3;
    }
}

void InvShiftRows(unsigned long (&state)[4][STATE_COLUMNS]) {
    int row_len = 4;
    for (int row = 0; row < row_len; row++) {
        int shift_pos = row;
        std::queue<unsigned long> tmp;
        for (int pos = row_len - shift_pos; pos < row_len; pos++) {
            tmp.push(state[row][pos]);
        }
        for (int pos = shift_pos; pos >= 0; pos--) {
            state[row][pos + shift_pos] = state[row][pos];
        }
        for (int pos = 0; pos < shift_pos; pos++) {
            state[row][pos] = tmp.front();
            tmp.pop();
        }
    }
}

static unsigned long inverse_s_box[16][16] = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d,}
};

void InvSubBytes(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int col = 0; col < STATE_COLUMNS; col++) {
        for (int row = 0; row < 4; row++) {
            unsigned long row_nr = state[row][col] >> 4; // Second digit
            unsigned long col_nr = state[row][col] & BIT_4_MASK; // first digit
            state[row][col] = inverse_s_box[row_nr][col_nr];
        }
    }
}

void print_state_hex(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << hex_to_string(state[j][i]);
        }
    }
    std::cout << std::endl;
}

std::string bin_to_string(unsigned long bin) {
    return std::bitset<8>(bin).to_string();
}

void print_state_bin(unsigned long (&state)[4][STATE_COLUMNS]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << bin_to_string(state[i][j]);
        }
    }
    std::cout << std::endl;
}

int main() {
    /**
     * C.1: AES-128
     * 00000000000100010010001000110011010001000101010101100110011101111000100010011001101010101011101111001100110111011110111011111111
     * 00000000000000010000001000000011000001000000010100000110000001110000100000001001000010100000101100001100000011010000111000001111
     * C.2 AES-192
     * 00000000000100010010001000110011010001000101010101100110011101111000100010011001101010101011101111001100110111011110111011111111
     * 000000000000000100000010000000110000010000000101000001100000011100001000000010010000101000001011000011000000110100001110000011110001000000010001000100100001001100010100000101010001011000010111
     * C.3 AES-256
     * 00000000000100010010001000110011010001000101010101100110011101111000100010011001101010101011101111001100110111011110111011111111
     * 0000000000000001000000100000001100000100000001010000011000000111000010000000100100001010000010110000110000001101000011100000111100010000000100010001001000010011000101000001010100010110000101110001100000011001000110100001101100011100000111010001111000011111
     */
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

    /**
     * Some keys:
     * 128: 00101011011111100001010100010110001010001010111011010010101001101010101111110111000101011000100000001001110011110100111100111100
     * 192: 100011100111001110110000111101111101101000001110011001000101001011001000000100001111001100101011100000001001000001111001111001010110001011111000111010101101001001010010001011000110101101111011
     * 256: 0110000000111101111010110001000000010101110010100111000110111110001010110111001110101110111100001000010101111101011101111000000100011111001101010010110000000111001110110110000100001000110101110010110110011000000100001010001100001001000101001101111111110100
     */
    std::string key;
    unsigned int number_of_rounds;
    unsigned int key_columns;
    while (true) {
        std::cout << "Please enter a 128, 192 or 256 bit key: ";
        std::cin >> key;
        size_t key_len = key.length();
        if (key_len == 128) {
            number_of_rounds = 10;
            key_columns = 4;
            break;
        } else if (key_len == 192) {
            number_of_rounds = 12;
            key_columns = 6;
            break;
        } else if (key_len == 256) {
            number_of_rounds = 14;
            key_columns = 8;
            break;
        } else {
            std::cout << "Incorrect key length" << std::endl;
        }
    }

    unsigned long state[4][STATE_COLUMNS]; // 4 rows and Nb columns
    int state_count = 0;
    for (int i = 0; i < STATE_COLUMNS; i++) {
        for (int j = 0; j < 4; j++) {
            std::string bin = plaintext.substr(state_count * 8, 8); // TODO: Remove convertation to binary
            state[j][i] = (unsigned int) std::stoi(bin, nullptr, 2); // Fill by column
            state_count++;
        }
    }

    std::string cipher_key[4][key_columns]; // 4 rows and Nk columns
    int key_count = 0;
    for (int i = 0; i < key_columns; i++) {
        for (int j = 0; j < 4; j++) {
            cipher_key[j][i] = key.substr(key_count * 8, 8);  // Fill by column
            key_count++;
        }
    }

    /**
     * KeyExpansion
     */
    std::string temp;

    int i = 0;
    int keys_total = 4 * (number_of_rounds + 1);
    std::string w[keys_total];

    while (i < key_columns) {
        for (int j = 0; j < key_columns; j++) {
            for (int k = 0; k < 4; k++) {
                std::cout << cipher_key[k][j] << std::endl;
                temp += cipher_key[k][j];
            }
            w[i] = temp;
            temp.clear();
            std::cout << "Key " << i << ": " << w[i] << std::endl;
            i++;
        }
    }

    //Round constants - https://en.wikipedia.org/wiki/Rijndael_key_schedule
    std::string rc_i[10] = {"01", "02", "04", "08", "10", "20", "40", "80", "1B", "36"};

    while (i < keys_total) {
        temp = w[i - 1];
        if (i % key_columns == 0) {
            std::string rcon_i = rc_i[(i / key_columns) - 1] + "00" + "00" + "00";
            rcon_i = hex_to_bin(rcon_i);
            temp = xor_32(SubWord(RotWord(temp)), rcon_i);
        } else if (key_columns > 6 && i % key_columns == 4) {
            temp = SubWord(temp);
        }
        w[i] = xor_32(w[i - key_columns], temp);
        i++;
    }
    std::cout << "Final expanded keys:" << std::endl;
    for (int j = 0; j < i; j++) {
        std::cout << j << ") " << w[j] << " | " << bin_to_hex(w[j]) << std::endl;
    }
    /**
     * KeyExpansion end
     */

    /**
     * Encryption
     */
    std::cout << "Encrypting.." << std::endl;
    unsigned int round = 0;
    AddRoundKey(state, w, round);

    round++;

    for (; round <= number_of_rounds; round++) {
        std::cout << "Round " << std::dec << round << ": " << std::endl;

        std::cout << "Start: ";
        print_state_hex(state);

        SubBytes(state);
        std::cout << "Sub Bytes: ";
        print_state_hex(state);

        ShiftRows(state);
        std::cout << "Shift rows: ";
        print_state_hex(state);

        if (round != number_of_rounds) {
            MixColumns(state);
            std::cout << "Mix columns: ";
            print_state_hex(state);

            AddRoundKey(state, w, round);
        } else { //Last round
            AddRoundKey(state, w, round);
        }
    }

    std::cout << "------------------------------" << "\nCiphertext:\nHex: ";
    print_state_hex(state);
    std::cout << "Binary: ";
    print_state_bin(state);
    std::cout << "------------------------------" << std::endl;

    /**
     * Decryption
     */
    std::cout << "Decrypting.." << std::endl;
    unsigned int round_dec = number_of_rounds;
    AddRoundKey(state, w, round_dec);

    round_dec--;

    for (int i = 1 ; i <= number_of_rounds; i++) {
        std::cout << "Round " << std::dec << i << ": " << std::endl;

        std::cout << "Start: ";
        print_state_hex(state);

        InvShiftRows(state);
        std::cout << "Shift rows: ";
        print_state_hex(state);

        InvSubBytes(state);
        std::cout << "Sub Bytes: ";
        print_state_hex(state);

        if (round_dec != number_of_rounds) {
            AddRoundKey(state, w, round_dec);

            InvMixColumns(state);
            std::cout << "Mix columns: ";
            print_state_hex(state);
        } else { //Last round
            AddRoundKey(state, w, round_dec);
        }
        round_dec--;
    }
    return 0;
}