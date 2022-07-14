/*Author: Randal Obringer
 * Date Last Modified: 7/14/2022
 *
 * Difficulty: Easy
 *
 * NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
 *	as the input is given through the IDE.
 *
 * Problem Statement:
 *   A logic gate is an electronic device implementing a boolean function, performing a logical operation on one or more binary inputs and producing a single binary output.
 *
 *   Given n input signal names and their respective data, and m output signal names with their respective type of gate and two input signal names, provide m output signal names and their respective data, in the same order as provided in input description.
 *
 *   All type of gates will always have two inputs and one output.
 *   All input signal data always have the same length.
 *
 *   The type of gates are :
 *   AND : performs a logical AND operation.
 *   OR : performs a logical OR operation.
 *   XOR : performs a logical exclusive OR operation.
 *   NAND : performs a logical inverted AND operation.
 *   NOR : performs a logical inverted OR operation.
 *   NXOR : performs a logical inverted exclusive OR operation.
 *
 * Signals are represented with underscore and minus characters, an undescore matching a low level (0, or false) and a minus matching a high level (1, or true).
 *
 * Constraints:
 *	1 ≤ n ≤ 4
 *  1 ≤ m ≤ 16
 *
 * Example Input:
 * 2
 * 3
 * A __---___---___---___---___
 * B ____---___---___---___---_
 * C AND A B
 * D OR A B
 * E XOR A B
 *
 * Example Output:
 * C ____-_____-_____-_____-___
 * D __-----_-----_-----_-----_
 * E __--_--_--_--_--_--_--_--_
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool toBool(char value) {
    if (value == '_') {
        return 0;
    }
    else
    {
        return 1;
    }
}

char toChar(bool value) {
    if (value == 1) {
        return '-';
    }
    else
    {
        return '_';
    }
}

string logicalAND(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(toBool(value1[i]) && toBool(value2[i]));
    }

    return result;
}

string logicalOR(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(toBool(value1[i]) || toBool(value2[i]));
    }

    return result;
}

string logicalXOR(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(toBool(value1[i]) != toBool(value2[i]));
    }

    return result;
}

string logicalNAND(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(!(toBool(value1[i]) && toBool(value2[i])));
    }

    return result;
}

string logicalNOR(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(!(toBool(value1[i]) || toBool(value2[i])));
    }

    return result;
}

string logicalNXOR(string value1, string value2) {
    string result = "";
    for (int i = 0; i < value1.length(); i++) {
        result += toChar(!(toBool(value1[i]) != toBool(value2[i])));
    }

    return result;
}

int main()
{
    map<string, string> inputSignals;

    /**
     * Auto-generated code below aims at helping you parse
     * the standard input according to the problem statement.
     **/
    int n;
    cin >> n; cin.ignore();
    int m;
    cin >> m; cin.ignore();

    // example: A __---___---___---___---___
    for (int i = 0; i < n; i++) {
        string input_name;
        string input_signal;
        cin >> input_name >> input_signal; cin.ignore();

        inputSignals[input_name] = input_signal;
    }

    // C AND A B
    for (int i = 0; i < m; i++) {
        string output_name;
        string type;
        string input_name_1;
        string input_name_2;
        cin >> output_name >> type >> input_name_1 >> input_name_2; cin.ignore();

        // C ____-_____-_____-_____-___
        string temp = "";
        if (type == "AND") {
            temp = logicalAND(inputSignals[input_name_1], inputSignals[input_name_2]);
        }
        else if (type == "OR") {
            temp = logicalOR(inputSignals[input_name_1], inputSignals[input_name_2]);
        }
        else if (type == "XOR") {
            temp = logicalXOR(inputSignals[input_name_1], inputSignals[input_name_2]);
        }
        else if (type == "NAND") {
            temp = logicalNAND(inputSignals[input_name_1], inputSignals[input_name_2]);
        }
        else if (type == "NOR") {
            temp = logicalNOR(inputSignals[input_name_1], inputSignals[input_name_2]);
        }
        else if (type == "NXOR") {
            temp = logicalNXOR(inputSignals[input_name_1], inputSignals[input_name_2]);
        }

        cout << output_name << " " << temp << endl;
    }
}