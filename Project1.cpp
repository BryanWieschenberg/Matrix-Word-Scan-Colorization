#include "colormod.h"
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

void matchMark(string currWord, int pos, vector <vector<bool>>* match, int i, int j) {
    for (int l = 0; l < currWord.length(); l++) {
        switch (pos) {
            case 1:
                (*match)[i][j+l] = true;
                break;
            case 2:
                (*match)[i+l][j+l] = true;
                break;
            case 3:
                (*match)[i+l][j] = true;
                break;
            case 4:
                (*match)[i+l][j-l] = true;
                break;
            case 5:
                (*match)[i][j-l] = true;
                break;
            case 6:
                (*match)[i-l][j-l] = true;
                break;
            case 7:
                (*match)[i-l][j] = true;
                break;
            case 8:
                (*match)[i-l][j+l] = true;
                break;
            default:
                break;
        }
    }
}

int posFinder(int i, int j, int row, int col, vector<vector<char>> matrix, string currWord, vector <vector<bool>>* match, int pos) {
    if (pos < 1 && (i >= 0 && i < row) && (j+1 >= 0 && j+1 < col)) {
        if (currWord[1] == matrix[i][j+1]) {
            if (currWord.length() == 2)
                (*match)[i][j+1] = true;
            return 1;
        }
    }
    if (pos < 2 && (i+1 >= 0 && i+1 < row) && (j+1 >= 0 && j+1 < col)) {
        if (currWord[1] == matrix[i+1][j+1]) {
            if (currWord.length() == 2)
                (*match)[i+1][j+1] = true;
            return 2;
        }
    }
    if (pos < 3 && (i+1 >= 0 && i+1 < row) && (j >= 0 && j < col)) {
        if (currWord[1] == matrix[i+1][j]) {
            if (currWord.length() == 2)
                (*match)[i+1][j] = true;
            return 3;
        }
    }
    if (pos < 4 && (i+1 >= 0 && i+1 < row) && (j-1 >= 0 && j-1 < col)) {
        if (currWord[1] == matrix[i+1][j-1]) {
            if (currWord.length() == 2)
                (*match)[i+1][j-1] = true;
            return 4;
        }
    }
    if (pos < 5 && (i >= 0 && i < row) && (j-1 >= 0 && j-1 < col)) {
        if (currWord[1] == matrix[i][j-1]) {
            if (currWord.length() == 2)
                (*match)[i][j-1] = true;
            return 5;
        }
    }
    if (pos < 6 && (i-1 >= 0 && i-1 < row) && (j-1 >= 0 && j-1 < col)) {
        if (currWord[1] == matrix[i-1][j-1]) {
            if (currWord.length() == 2)
                (*match)[i-1][j-1] = true;
            return 6;
        }
    }
    if (pos < 7 && (i-1 >= 0 && i-1 < row) && (j >= 0 && j < col)) {
        if (currWord[1] == matrix[i-1][j]) {
            if (currWord.length() == 2)
                (*match)[i-1][j] = true;
            return 7;
        }
    }
    if (pos < 8 && (i-1 >= 0 && i-1 < row) && (j+1 >= 0 && j+1 < col)) {
        if (currWord[1] == matrix[i-1][j+1]) {
            if (currWord.length() == 2)
                (*match)[i-1][j+1] = true;
            return 8;
        }
    }
    return 0;
}

bool finishWord(int charNum, string currWord, vector<vector<char>> matrix, int i, int j, int row, int col, int pos) {
    bool success;
    for (int k = 2; k < currWord.length(); k++) {
        success = false;
        charNum++;
        switch (pos) {
            case 1:
                if ((i >= 0 && i < row) && (j+charNum >= 0 && j+charNum < col)) {
                    if (currWord[charNum] == matrix[i][j+charNum])
                        success = true;
                }
                break;
            case 2:
                if ((i+charNum >= 0 && i+charNum < row) && (j+charNum >= 0 && j+charNum < col)) {
                    if (currWord[charNum] == matrix[i+charNum][j+charNum])
                        success = true;
                }
                break;
            case 3:
                if ((i+charNum >= 0 && i+charNum < row) && (j >= 0 && j < col)) {
                    if (currWord[charNum] == matrix[i+charNum][j])
                        success = true;
                }
                break;
            case 4:
                if ((i+charNum >= 0 && i+charNum < row) && (j-charNum >= 0 && j-charNum < col)) {
                    if (currWord[charNum] == matrix[i+charNum][j-charNum])
                        success = true;
                }
                break;
            case 5:
                if ((i >= 0 && i < row) && (j-charNum >= 0 && j-charNum < col)) {
                    if (currWord[charNum] == matrix[i][j-charNum])
                        success = true;
                }
                break;
            case 6:
                if ((i-charNum >= 0 && i-charNum < row) && (j-charNum >= 0 && j-charNum < col)) {
                    if (currWord[charNum] == matrix[i-charNum][j-charNum])
                        success = true;
                }
                break;
            case 7:
                if ((i-charNum >= 0 && i-charNum < row) && (j >= 0 && j < col)) {
                    if (currWord[charNum] == matrix[i-charNum][j])
                        success = true;
                }
                break;
            case 8:
                if ((i-charNum >= 0 && i-charNum < row) && (j+charNum >= 0 && j+charNum < col)) {
                    if (currWord[charNum] == matrix[i-charNum][j+charNum])
                        success = true;
                }
                break;
            default:
                break;
        }
        if (!success) return false;
    }
    return true;
}
void search(vector <vector<char>> matrix, vector <vector<bool>>* match, int row, int col, int argc, char* args[]) {
    /* 'pos' variable key
    6 7 8
    5   1
    4 3 2 */
    
    string currWord;
    int charNum, pos = 0;
    bool success, first;
    
    for (int wordNum = 1; wordNum < argc; wordNum++) {
        currWord = args[wordNum];
        
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                charNum = 0;
                pos = 0;
                
                if (currWord[charNum] == matrix[i][j]) {
                    
                    // Special case for 1-character words
                    if (currWord.length() == 1) {
                        (*match)[i][j] = true;
                        break;
                    }
                    
                    first = true;
                    while (first || (pos > 0 && pos < 8)) {
                        first = false;
                        success = false;
                        charNum = 1;
                        pos = posFinder(i, j, row, col, matrix, currWord, match, pos);
                        
                        // Special case for 2-character words
                        if (currWord.length() == 2 && pos > 0) {
                            (*match)[i][j] = true;
                        }

                        if (pos > 0 && currWord.length() > 2) {
                            success = finishWord(charNum, currWord, matrix, i, j, row, col, pos);
                            // If the finishWord function is successful, this makes the match vector coords true, printing out the matching chars as red
                            if (success) matchMark(currWord, pos, match, i, j);
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char* args[]) {
    Color::Setting def(Color::FG_DEFAULT);
    Color::Setting red(Color::FG_RED);
    
    int i, j, row, col;
    char value;
    cin >> row >> col;
    vector <vector<char>> matrix;
    vector <vector<bool>> match;
    matrix.resize(row);
    for (i = 0; i < matrix.size(); i++)
        matrix[i].resize(col);
    
    match.resize(row);
    for (i = 0; i < match.size(); i++)
        match[i].resize(col);
    
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cin >> value;
            matrix[i][j] = value;
        }
    }

    search(matrix, &match, row, col, argc, args);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (!(match[i][j])) cout << matrix[i][j] << " ";
            else cout << red << matrix[i][j] << def << " ";
        }
        cout << endl;
    }

    return 0;
}
