#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <tuple>


using namespace std;

#define BLACK       "\033[30;40;4m___\033[0m"
#define WHITE       "\033[97;107;4m___\033[0m"

std::tuple<int, int> zugeingabe(string zug);

vector<vector<string>> search_and_color(vector<vector<string>> &feld);

vector<vector<string>> group(int i, int j, vector<vector<string>> &marked, const vector<vector<string>> &feld);

vector<vector<string>> nachrutschen_spalte(vector<vector<string>> &feld);

bool game_over(vector<vector<string>> &white_spot_field);

int count_score(vector<vector<string>> &game_board);

int main() {
/*
    vector<vector<string> > spielfeld(9, vector<string>(9));
    vector<vector<string> > marked(9, vector<string>(9));
    vector<string> farben{"\033[31;41;4m___\033[0m", "\033[32;42;4m___\033[0m", "\033[33;43;4m___\033[0m",
                          "\033[34;44;4m___\033[0m", "\033[35;45;4m___\033[0m"};

    //srand(time(NULL));
    srand(7);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int v1 = rand() % 5;
            spielfeld[i][j] = farben[v1];
        }
    }
    //KOPIE VOM SPIELFELD ANLEGEN
    marked = spielfeld;

    for (int i = 0; i < spielfeld.size(); i++) {

        for (int j = 0; j < spielfeld[i].size(); j++) {
            cout << spielfeld[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << " I " << endl;

     DEBUG zugeingabe
    auto zug = zugeingabe("d2");
    cout << std::get<0>(zug) << std::get<1>(zug) << endl;
    cout << spielfeld[std::get<0>(zug)][std::get<1>(zug)] << endl;


    // FINDE ALLE STEINE DIE TEIL IRGENDEINER GRUPPE SIND UND FÄRBE SIE WEISS EIN
    vector<vector<string>> haha = search_and_color(spielfeld);

    for (int i = 0; i < haha.size(); i++) {

        for (int j = 0; j < haha[i].size(); j++) {
            cout << haha[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << endl;
    auto zug = zugeingabe("c8");

    // GRUPPE FINDEN UND SCHWARZ EINFÄRBEN
    vector<vector<string>> hehe = group(std::get<0>(zug), std::get<1>(zug), marked, spielfeld);

    for (int i = 0; i < hehe.size(); i++) {

        for (int j = 0; j < hehe[i].size(); j++) {
            cout << hehe[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << endl;

    // NACHRUTSCHEN
    vector<vector<string>> pushed_up = nachrutschen_spalte(hehe);

    for (int i = 0; i < pushed_up.size(); i++) {

        for (int j = 0; j < pushed_up[i].size(); j++) {
            cout << pushed_up[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << endl;
    //KOPIE VOM SPIELFELD ANLEGEN
    vector<vector<string> > NAECHSTEMARKE(9, vector<string>(9));
    NAECHSTEMARKE = pushed_up;

    vector<vector<string>> NAECHSTERUNDE = group(std::get<0>(zug), std::get<1>(zug), NAECHSTEMARKE, pushed_up);

    for (int i = 0; i < NAECHSTERUNDE.size(); i++) {

        for (int j = 0; j < NAECHSTERUNDE[i].size(); j++) {
            cout << NAECHSTERUNDE[i][j];
        }
        cout << " " << i + 1 << endl;
    }

    cout << endl;
    vector<vector<string>> pushed_up1 = nachrutschen_spalte(NAECHSTERUNDE);

    for (int i = 0; i < pushed_up1.size(); i++) {

        for (int j = 0; j < pushed_up1[i].size(); j++) {
            cout << pushed_up1[i][j];
        }
        cout << " " << i + 1 << endl;
    }


*/
    // implementation

    vector<vector<string> > game_board(9, vector<string>(9));
    vector<vector<string> > copy_game_board(9, vector<string>(9));
    vector<vector<string> > white_board(9, vector<string>(9));
    vector<string> colors{"\033[31;41;4m___\033[0m", "\033[32;42;4m___\033[0m", "\033[33;43;4m___\033[0m",
                          "\033[34;44;4m___\033[0m", "\033[35;45;4m___\033[0m"};
    int score_total = 0;
    int score_after = 0;
    int score_before = 0;

    // set colors
    //srand(time(NULL));
    srand(2);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int c = rand() % 5;
            game_board[i][j] = colors[c];
        }
    }

    for (int i = 0; i < game_board.size(); i++) {

        for (int j = 0; j < game_board[i].size(); j++) {
            cout << game_board[i][j];
        }
        cout << " " << i + 1 << endl;
    }
    cout << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << " I " << endl;

    do {
        copy_game_board = game_board;

        cout << "Insert a move (e.g. 'f3')";
        string move_input;
        cin >> move_input;
        auto move = zugeingabe(move_input);

        score_before = count_score(game_board);

        game_board = group(std::get<0>(move), std::get<1>(move), copy_game_board, game_board);

        game_board = nachrutschen_spalte(game_board);

        white_board = search_and_color(game_board);

        score_after = count_score(game_board);
        score_after = (score_after - score_before) * (score_after - score_before - 1);
        score_total += score_after;

        for (int i = 0; i < game_board.size(); i++) {

            for (int j = 0; j < game_board[i].size(); j++) {
                cout << game_board[i][j];
            }
            cout << " " << i + 1 << endl;
        }
        cout << " A " << " B " << " C " << " D " << " E " << " F " << " G " << " H " << " I " << endl;

        cout << "SCORE: "<< score_total << endl;




    } while (!game_over(white_board));

    return 0;
}


std::tuple<int, int> zugeingabe(string zug) {

    char row = zug[1];
    char col = zug[0];
    int zeile;
    int spalte;

    if (row == '1') zeile = 0;
    else if (row == '2') zeile = 1;
    else if (row == '3') zeile = 2;
    else if (row == '4') zeile = 3;
    else if (row == '5') zeile = 4;
    else if (row == '6') zeile = 5;
    else if (row == '7') zeile = 6;
    else if (row == '8') zeile = 7;
    else if (row == '9') zeile = 8;
    else cout << "Illegal move" << endl;

    if (col == 'a') spalte = 0;
    else if (col == 'b') spalte = 1;
    else if (col == 'c') spalte = 2;
    else if (col == 'd') spalte = 3;
    else if (col == 'e') spalte = 4;
    else if (col == 'f') spalte = 5;
    else if (col == 'g') spalte = 6;
    else if (col == 'h') spalte = 7;
    else if (col == 'i') spalte = 8;
    else cout << "Illegal move" << endl;

    return std::make_tuple(zeile, spalte);
}

vector<vector<string>> search_and_color(vector<vector<string>> &feld) {

    //make copy of feld
    vector<vector<string>> white_spots = feld;

    for (int i = 0; i < white_spots.size(); i++) {
        for (int j = 0; j < white_spots[i].size(); j++) {
            if (i == 0 && j == 0) {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j + 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (i == 0 && j == 8) {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (i == 8 && j == 0) {
                if ((feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j + 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (i == 8 && j == 8) {
                if ((feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j - 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (i == 0 && j < 8 && j > 0) {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] ||
                     feld[i][j] == feld[i][j + 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (j == 0 && i < 8 && i > 0) {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j + 1] ||
                     feld[i][j] == feld[i - 1][j]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (i == 8 && j < 8 && j > 0) {
                if ((feld[i][j] == feld[i - 1][j] || feld[i][j] == feld[i][j + 1] ||
                     feld[i][j] == feld[i][j - 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else if (j == 8 && i < 8 && i > 0) {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] ||
                     feld[i][j] == feld[i - 1][j]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            } else {
                if ((feld[i][j] == feld[i + 1][j] || feld[i][j] == feld[i][j - 1] || feld[i][j] == feld[i - 1][j] ||
                     feld[i][j] == feld[i][j + 1]) && feld[i][j] != BLACK) {
                    white_spots[i][j] = WHITE;
                }
            }
        }
    }
    return white_spots;
}

vector<vector<string>> group(int i, int j, vector<vector<string>> &marked, const vector<vector<string>> &feld) {

    //upper left corner
    if (i == 0 && j == 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }
    //lower left corner
    if (i == 8 && j == 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }
    //lower right corner
    if (i == 8 && j == 8) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }
    //upper right corner
    if (i == 0 && j == 8) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    //left side
    if (j == 0 && i < 8 && i > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    //bottom side
    if (i == 8 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    //right side
    if (j == 8 && i < 8 && i > 0) {
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    //top side
    if (i == 0 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    //middle
    if (i < 8 && i > 0 && j < 8 && j > 0) {
        if (feld[i][j] == feld[i][j + 1] && marked[i][j + 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j + 1, marked, feld);
        } else if (feld[i][j + 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i][j - 1] && marked[i][j - 1] != BLACK) {
            marked[i][j] = BLACK;
            group(i, j - 1, marked, feld);
        } else if (feld[i][j - 1] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i + 1][j] && marked[i + 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i + 1, j, marked, feld);
        } else if (feld[i + 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
        if (feld[i][j] == feld[i - 1][j] && marked[i - 1][j] != BLACK) {
            marked[i][j] = BLACK;
            group(i - 1, j, marked, feld);
        } else if (feld[i - 1][j] == feld[i][j]) {
            marked[i][j] = BLACK;
        }
    }

    return marked;
}

vector<vector<string>> nachrutschen_spalte(vector<vector<string>> &feld) {
    for (int k = 0; k < 9; k++) {
        for (int i = feld.size() - 1; i > 0; i--) {
            for (int j = feld.size() - 1; j >= 0; j--) {
                if (feld[i][j] == BLACK && feld[i - 1][j] != BLACK) {
                    feld[i][j] = feld[i - 1][j];
                    feld[i - 1][j] = BLACK;
                }
            }
        }
    }
    return feld;
}

bool game_over(vector<vector<string>> &white_spot_field) {
    for (int i = 0; i < white_spot_field.size(); i++) {
        for (int j = 0; j < white_spot_field[i].size(); j++) {
            if (white_spot_field[i][j] == WHITE) return false;
        }
    }
    cout << "GAME OVER" << endl;
    return true;
}

int count_score(vector<vector<string>> &game_board) {
    int score = 0;

    for (int i = 0; i < game_board.size(); i++) {
        for (int j = 0; j < game_board[i].size(); j++) {
            if (game_board[i][j] == BLACK) score++;

        }
    }
    return score;
}
