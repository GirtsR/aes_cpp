/**
 * Created by Ģirts Rudzišs, Emīls Ozoliņš
 *
 *
 * 00010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001
 */

#include <iostream>
#include <bitset>
#include <queue>

#define STATE_COLUMNS 4

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

static std::string s_box[16][16] = {
    {"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
    {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
    {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
    {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
    {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
    {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
    {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
    {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
    {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
    {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
    {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
    {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
    {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
    {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
    {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
    {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}
};

std::string SubWord(std::string temp) {
    std::string result;

    for (int i = 0; i < 4; i++) {
        std::string byte = temp.substr(i * 8, 8);
        std::string hex_old = bin_to_hex(byte);
        std::string hex = s_box[hex_to_decimal(hex_old[0])][hex_to_decimal(hex_old[1])];
        result += hex;
        std::cout << result;
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

void AddRoundKey(std::string (&state)[4][STATE_COLUMNS], std::string w[], unsigned int round) {
    unsigned l = round * STATE_COLUMNS;

    for (int col = 0; col < STATE_COLUMNS; col++) {
        std::string column = state[0][col] + state[1][col] + state[2][col] + state[3][col];
        std::string tmp = xor_32(hex_to_bin(column), w[l + col]);

        for (int i = 0; i < 4; i++) {
            std::string byte = tmp.substr(i * 8, 8);
            state[i][col] = byte;
        }
    }
}

void SubBytes(std::string (&state)[4][STATE_COLUMNS]) {
    for (int col = 0; col < STATE_COLUMNS; col++) {
        for (auto &row : state) {
            std::string byte = row[col];
            int col_nr = hex_to_decimal(byte[1]);
            int row_nr = hex_to_decimal(byte[0]);
            row[col] = s_box[row_nr][col_nr];
        }
    }
}

// TODO: Not sure if works
void ShiftRows(std::string (&state)[4][STATE_COLUMNS]) { // TODO: I am sorry for this crap. Will rewrite it (maybe)
    int row_len = 4; // TODO: Constant
    for (int row = 0; row < row_len; row++) {
        int shift_pos = row;
        std::queue<std::string> tmp;
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

unsigned long field_mul(unsigned long a, unsigned long b) { // Multiplication in G(256).
    unsigned long res = 0;

    for (int i = 0; i < 8; i++) {
        if ((b & 1) != 0) {
            res ^= a;
        }

        bool out_of_field = (a & 0x80) != 0;
        a <<= 1;
        if (out_of_field) {
            a ^= 0x1B;
        }
        b >>= 1;
    }

    return res;
}

unsigned long hex_to_ul(const std::string &hex) {
    return std::bitset<8>(hex_to_bin(hex)).to_ulong();
}

void MixColumns(std::string (&state)[4][STATE_COLUMNS]) {
    for (int i = 0; i < STATE_COLUMNS; i++) {
        unsigned long z = hex_to_ul(state[0][i]); // TODO: Keep states as numbers
        unsigned long f = hex_to_ul(state[1][i]);
        unsigned long s = hex_to_ul(state[2][i]);
        unsigned long t = hex_to_ul(state[3][i]);

        unsigned long tmp0 = field_mul(0x02, z) ^field_mul(0x03, f) ^s ^t;
        unsigned long tmp1 = z ^field_mul(0x02, f) ^field_mul(0x03, s) ^t;
        unsigned long tmp2 = z ^f ^field_mul(0x02, s) ^field_mul(0x03, t);
        unsigned long tmp3 = field_mul(0x03, z) ^f ^s ^field_mul(0x02, t);

        state[0][i] = bin_to_hex(std::bitset<8>(tmp0).to_string());
        state[1][i] = bin_to_hex(std::bitset<8>(tmp1).to_string());
        state[2][i] = bin_to_hex(std::bitset<8>(tmp2).to_string());
        state[3][i] = bin_to_hex(std::bitset<8>(tmp3).to_string());
    }
}

int main() {
    std::string plaintext;
    std::string input;

    // TODO: Uncomment
//    while (true) {
//        std::cout << "Please enter a 128 bit or 32 hex digit plaintext: ";
//        std::cin >> input;
//        if (input.length() == 32) {
//            plaintext = hex_to_bin(input);
//            std::cout << "Entered hex, binary representation: " << plaintext << std::endl;
//            break;
//        } else if (input.length() == 128) {
//            plaintext = input;
//            std::string hex = bin_to_hex(plaintext);
//            std::cout << "Entered binary, hex representation: " << hex << std::endl;
//            break;
//        } else {
//            std::cout << "Incorrect plaintext length" << std::endl;
//        }
//    }

// TODO: Remove
    plaintext = "00010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001000100010001";

    /**
     * Some keys:
     * 128: 00101011011111100001010100010110001010001010111011010010101001101010101111110111000101011000100000001001110011110100111100111100
     * 192: 100011100111001110110000111101111101101000001110011001000101001011001000000100001111001100101011100000001001000001111001111001010110001011111000111010101101001001010010001011000110101101111011
     * 256: 0110000000111101111010110001000000010101110010100111000110111110001010110111001110101110111100001000010101111101011101111000000100011111001101010010110000000111001110110110000100001000110101110010110110011000000100001010001100001001000101001101111111110100
     */
    std::string key;
    unsigned int number_of_rounds;
    unsigned int key_columns;
    // TODO: Uncomment
//    while (true) {
//        std::cout << "Please enter a 128, 192 or 256 bit key: ";
//        std::cin >> key;
//        size_t key_len = key.length();
//        if (key_len == 128) {
//            number_of_rounds = 10;
//            key_columns = 4;
//            break;
//        } else if (key_len == 192) {
//            number_of_rounds = 12;
//            key_columns = 6;
//            break;
//        } else if (key_len == 256) {
//            number_of_rounds = 14;
//            key_columns = 8;
//            break;
//        } else {
//            std::cout << "Incorrect key length" << std::endl;
//        }
//    }

    // TODO: Remove
    key = "00101011011111100001010100010110001010001010111011010010101001101010101111110111000101011000100000001001110011110100111100111100";
    number_of_rounds = 10;
    key_columns = 4;

    std::string state[4][STATE_COLUMNS]; // 4 rows and Nb columns
    int state_count = 0;
    for (int i = 0; i < STATE_COLUMNS; i++) {
        for (int j = 0; j < 4; j++) {
            std::string bin = plaintext.substr(state_count * 8, 8); // TODO: Remove convertation to binary
            state[j][i] = bin_to_hex(bin); // Fill by column
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

    unsigned int round = 0;
    AddRoundKey(state, w, round);

    for (; round <= number_of_rounds; round++) {
        std::cout << "Round " << round << ": ";
        //TODO - do stuff

        SubBytes(state);

        ShiftRows(state);

        if (round != number_of_rounds) {
            MixColumns(state);
            AddRoundKey(state, w, round);
        } else { //Last round
            AddRoundKey(state, w, round);
        }
    }

    return 0;
}