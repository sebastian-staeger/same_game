#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tuple>

using namespace std;

std::tuple<int, int> zugeingabe(string zug);


vector<vector<string>> search_and_color(vector<vector<string>> &feld);

vector<vector<string>> group(int i, int j, vector<vector<string>> &marked, const vector<vector<string>> &feld);

int main() {

    /*std::cout << "\033[31;41;4m___\033[0m" << " ";
    std::cout << "\033[32;42;4m___\033[0m" << " ";
    std::cout << "\033[33;43;4m___\033[0m" << " ";
    std::cout << "\033[34;44;4m___\033[0m" << " ";
    std::cout << "\033[37;47;4m___\033[0m" << " " << endl;
*/
    vector<vector<string> > spielfeld(9, vector<string>(9));
    vector<vector<string> > marked(9, vector<string>(9));
    vector<string> farben{"\033[31;41;4m___\033[0m", "\033[32;42;4m___\033[0m", "\033[33;43;4m___\033[0m",
                          "\033[34;44;4m___\033[0m", "\033[35;45;4m___\033[0m"};

    //srand(time(NULL));
    srand(11);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int v1 = rand() % 5;
            spielfeld[i][j] = farben[v1];
            //cout << farben[v1] << "wurde an stelle " << i << " " << j << "eingefügt" << endl;
            //cout << spielfeld[i][j] << endl;
        }
    }
    marked = spielfeld;

    for (int i = 0; i < spielfeld.size(); i++) {

        for (int j = 0; j < spielfeld[i].size(); j++) {
            cout << spielfeld[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << " I " << endl;

    /* DEBUG zugeingabe
    auto zug = zugeingabe("d2");
    cout << std::get<0>(zug) << std::get<1>(zug) << endl;

    cout << spielfeld[std::get<0>(zug)][std::get<1>(zug)] << endl;
*/

    vector<vector<string>> haha = search_and_color(spielfeld);

    for (int i = 0; i < haha.size(); i++) {

        for (int j = 0; j < haha[i].size(); j++) {
            cout << haha[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << endl;
    auto zug = zugeingabe("e5");
    vector<vector<string>> hehe = group(std::get<0>(zug), std::get<1>(zug), marked, spielfeld);

    for (int i = 0; i < hehe.size(); i++) {

        for (int j = 0; j < hehe[i].size(); j++) {
            cout << hehe[i][j];
        }
        cout << " " << i + 1 << endl;
    }

    return 0;
}


std::tuple<int, int> zugeingabe(string zug) {

    char row = zug[1];
    char col = zug[0];
    int zeile;
    int spalte;

    if (row == '1') zeile = 0;
    if (row == '2') zeile = 1;
    if (row == '3') zeile = 2;
    if (row == '4') zeile = 3;
    if (row == '5') zeile = 4;
    if (row == '6') zeile = 5;
    if (row == '7') zeile = 6;
    if (row == '8') zeile = 7;
    if (row == '9') zeile = 8;

    if (col == 'a') spalte = 0;
    if (col == 'b') spalte = 1;
    if (col == 'c') spalte = 2;
    if (col == 'd') spalte = 3;
    if (col == 'e') spalte = 4;
    if (col == 'f') spalte = 5;
    if (col == 'g') spalte = 6;
    if (col == 'h') spalte = 7;
    if (col == 'i') spalte = 8;

    return std::make_tuple(zeile, spalte);
}

vector<vector<string>> search_and_color(vector<vector<string>> &feld) {

    //make copy of feld
    vector<vector<string>> white_spots = feld;

    for (int i = 0; i < white_spots.size(); i++) {

        for (int j = 0; j < white_spots[i].size(); j++) {
            if (i == 0 && j == 0) {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j + 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (i == 0 && j == 8) {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (i == 8 && j == 0) {
                if (feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j + 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (i == 8 && j == 8) {
                if (feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j - 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (i == 0 && j < 8 && j > 0) {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] || feld[i][j] == feld[i][j + 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (j == 0 && i < 8 && i > 0) {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j + 1] || feld[i][j] == feld[i - 1][j]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (i == 8 && j < 8 && j > 0) {
                if (feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j + 1] || feld[i][j] == feld[i][j - 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else if (j == 8 && i < 8 && i > 0) {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] || feld[i][j] == feld[i - 1][j]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            } else {
                if (feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] || feld[i][j] == feld[i - 1][j] ||
                    feld[i][j] == feld[i][j + 1]) {
                    white_spots[i][j] = "\033[97;107;4m___\033[0m";
                }
            }
        }
    }
    return white_spots;
}

vector<vector<string>> group(int i, int j, vector<vector<string>> &marked, const vector<vector<string>> &feld) {

    //upper left corner
    if (i == 0 && j == 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }
    //lower left corner
    if (i == 8 && j == 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }
    //lower right corner
    if (i == 8 && j == 8) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }
    //upper right corner
    if (i == 0 && j == 8) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    //left side
    if (j == 0 && i < 8 && i > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    //bottom side
    if (i == 8 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    //right side
    if (j == 8 && i < 8 && i > 0) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    //top side
    if (i == 0 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    //middle
    if (i < 8 && i > 0 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != "\033[30;40;4m___\033[0m") {
            marked[i][j] = "\033[30;40;4m___\033[0m";
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = "\033[30;40;4m___\033[0m";
        }
    }

    return marked;
}

void has_neighbour(vector<vector<string>> &feld) {

}