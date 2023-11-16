#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;
typedef struct {
    int* row;
} WinList;

class Player {
private:
    string name;
    int score;

public:
    Player() : Player { "" } {}
    Player(string n) : score { 0 }, name { n } {}

    void won() {
        score++;
    }
    int getScore() {
        return this->score;
    }

    string getName() {
        return this->name;
    }
};

class Game {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn;
    int emptyCount;
    WinList winlist[8];

    void displayBoard() {
        cout << endl;
        cout << "   |   |   " << endl;
        cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
        cout << "   |   |   " << endl;
        cout << "-----------" << endl;
        cout << "   |   |   " << endl;
        cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
        cout << "   |   |   " << endl;
        cout << "-----------" << endl;
        cout << "   |   |   " << endl;
        cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
        cout << "   |   |   " << endl;
        cout << endl;
    }

    void playerInput(Player& player) {
        int pos;
        cout << endl;
        cout << player.getName() << " Turn: ";
        cout << "Enter the position " << endl;
        cin >> pos;
        pos -= 1;
        if (emptyIndex[pos] == 1) {
            cout << "-----Position not empty-------" << endl;
            playerInput(player);
        } else {
            emptyIndex[pos] = 1;
            emptyCount -= 1;
            player.getName().compare("Player I") == 0 ? board[pos] = 'X' : board[pos] = 'O';
        }
    }

    void checkWin(Player& p1, Player& p2) {
        int i, j, k;
        bool flag = false;
        char first_symbol;
        for (i = 0; i < 8; i++) {
            first_symbol = board[winlist[i].row[0]];

            if ((first_symbol != 'X') && (first_symbol != 'O')) {
                flag = false;
                continue;
            }
            flag = true;
            for (j = 0; j < 3; j++) {
                if (first_symbol != board[winlist[i].row[j]]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                gameOn = 0;
                if (first_symbol == 'X') {
                    cout << "-----------------------" << endl;
                    cout << "\t Player I WON" << endl;
                    cout << "-----------------------" << endl;
                    p1.won();
                } else {
                    p2.won();
                    cout << "-----------------------" << endl;
                    cout << "\t Player II WON" << endl;
                    cout << "-----------------------" << endl;
                }
                displayScore(p1, p2);
                break;
            }
        }
    }

    void play(Player& p1, Player& p2) {
        char rematch = '\0';
        int hand = 0;
        gameOn = 1;
        displayBoard();
        while ((emptyCount > 0) && (gameOn != 0)) {
            playerInput(hand == 0 ? p1 : p2);
            hand = !hand;
            displayBoard();
            checkWin(p1, p2);
        }
        if (emptyCount <= 0) {
            cout << "      -----------------------" << endl;
            cout << "\t No WINNER" << endl;
            cout << "      -----------------------" << endl;
        }
        cout << endl;
        cout << "Rematch Y/N: ";
        cin >> rematch;
        if ((rematch == 'Y') || (rematch == 'y')) {
            init();
            play(p1, p2);
        }
    }

    void displayScore(Player& p1, Player& p2) {
        cout << endl;
        cout << "\t SCORE: \t";
        cout << "Player I: " << p1.getScore() << " \t Player II: " << p2.getScore() << endl;
    }

public:
    Game() : emptyCount{ 0 }, gameOn{ 1 } {
        init();
        winlist[0].row = new int[3]{ 0, 1, 2 };
        winlist[1].row = new int[3]{ 3, 4, 5 };
        winlist[2].row = new int[3]{ 6, 7, 8 };
        winlist[3].row = new int[3]{ 0, 3, 6 };
        winlist[4].row = new int[3]{ 1, 4, 7 };
        winlist[5].row = new int[3]{ 2, 5, 8 };
        winlist[6].row = new int[3]{ 0, 4, 8 };
        winlist[7].row = new int[3]{ 2, 4, 6 };
    }

    void init() {
        gameOn = 1;
        emptyCount = 0;
        srand(time(0));
        for (size_t i = 0; i < 10; i++) {
            emptyIndex[i] = 0;
            board[i] = (i + 1) + '0';
            emptyCount++;
        }
        emptyCount--;
    }

    void twoPlayerGame() {
        Player p1("Player I");
        Player p2("Player II");
        cout << "       -----------------------" << endl;
        cout << "\t Player I: X \t Player II: O" << endl;
        cout << "       -----------------------" << endl;
        cout << endl;
        play(p1, p2);
    }
};

int main() {
    int ch;

    while (true) {
        cout << "      ----------MENU----------" << endl;
        cout << "\t 1. Player game" << endl;
        cout << "\t 2. To exit" << endl;
        cout << "      ------------------------" << endl;
        cout << endl;
        cout << "\t Select an option" << endl;
        cin >> ch;
        switch (ch) {
        case 1: {
            Game* game = new Game;
            game->init();
            game->twoPlayerGame();
        }
        break;
        case 2:
            return 0;
            default:
            cout << "OOPs Invalid Option! TRY AGAIN";
        }
 
    }
    return 0;
}
