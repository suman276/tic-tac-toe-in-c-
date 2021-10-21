/* Code inspired by: http://www.cs.mun.ca/~av/courses/5895-current/?page_id=24
  Tic Tac Toe Object Oriented Programming with C++.                        */
 
#include <iostream>
#include <vector>
#include <string>
 
using namespace std;
 
enum GameStatus {IN_PROGRESS, X_WON, O_WON, DRAW};
 
class Move {
 public:
  Move(int i, int j, int piece) : i(i), j(j), piece(piece) {}
  int getI(void) { return i; }
  int getJ(void) { return j; }
  int getPiece(void) { return piece; }
 private:
  int i;
  int j;
  int piece;
};
 
class Board {
 public:
  Board(int N, int M) {
    table.resize(N);
    for(int i = 0; i < N; ++i)
      for(int j = 0; j < M; ++j)
        table[i].push_back(-1);
  }
  size_t getRows(void) { return table.size(); }
  size_t getCols(void) { return table.size() ? table[0].size() : -1; }
  int get(int i, int j) { return table[i][j]; }
  bool set(Move m) {
    if(table[m.getI()][m.getJ()] == -1)
    {
      table[m.getI()][m.getJ()] = m.getPiece();
      return true;
    }
    return false;
  }
  bool full(void) {
    for(size_t i = 0; i < table.size(); ++i)
      for(size_t j = 0; j < table[i].size(); ++j)
        if(table[i][j] == -1)
          return false;
    return true;
  }
  void print(void) {
    for(size_t i = 0; i < table.size(); ++i)
    {
      for(size_t j = 0; j < table[i].size(); ++j)
        cout << table[i][j] << " ";
      cout << "\n";
    }
  }
 private:
  vector< vector<int> > table;  // -1 empty, 0 for '0' and 1 for 'X'
};
 
class Player {
 public:
  Player(string name, int symbol) : name(name) {
    symbol = (symbol == '0') ? 0 : 1;
  }
  string& getName(void) { return name; }
  int getSymbol(void) { return symbol; }
  void chooseMove(Board& b) {
    int i, j;
    do {
      cout << "Your turn: ";
      cin >> i;
      cin >> j;
      cout << "\n";
    } while(!b.set(Move(i, j, symbol)));
  }
 private:
  string name;
  int symbol;
};
 
class AI {
 public:
  AI(int symbol) : symbol(symbol) {}
  virtual Move chooseMove(Board& b) = 0;
  int getSymbol(void) { return symbol; }
  virtual ~AI() {};
 private:
  int symbol;
};
 
class DumbAI : public AI {
 public:
  DumbAI(const int symbol) : AI(symbol) {}
  virtual Move chooseMove(Board& b) {
    for(size_t i = 0; i < b.getRows(); ++i)
      for(size_t j = 0; j < b.getCols(); ++j)
        if(b.get(i, j) == -1)
          return Move(i, j, AI::getSymbol());
  }
};
 
class cleverAI : public AI {
 public:
  cleverAI(const int symbol) : AI(symbol) {}
  // imagine that it does something clever
  virtual Move chooseMove(Board& b) {
    for(size_t i = 0; i < b.getRows(); ++i)
      for(size_t j = 0; j < b.getCols(); ++j)
        if(b.get(i, j) == -1)
          return Move(i, j, AI::getSymbol());
  }
};
 
class Game {
 public:
  Game(int difficulty, string name, char symbol) : board(3, 3), player(name, symbol), status(IN_PROGRESS) {
    int symbolAI = (symbol == '0') ? 1 : 0;
    if(difficulty == 1)
      pAI = new DumbAI(symbolAI);
    else
      pAI = new cleverAI(symbolAI);
  }
  void makeMovePlayer() {
    player.chooseMove(board);
  }
  void makeMoveAI() {
    Move m = pAI->chooseMove(board);
    board.set(m);
  }
  GameStatus getStatus(void) { return status; }
  void setStatus(GameStatus gameStatus) { status = gameStatus; }
  Board& getBoard(void) { return board; }
  void pirntBoard(void) { return board.print(); }
  ~Game() { delete pAI; }
 private:
  Board board;
  Player player;
  AI* pAI;
  GameStatus status;
};
 
class ConsoleRunner {
 public:
  ConsoleRunner(int difficulty, string name, char symbol) : game(difficulty, name, symbol) {}
  void play(void) {
    // assume that player always choses 'X'
    bool playerTurn = true;
    while(!game.getBoard().full() && victory(game.getBoard()) == -1)
    {
      if(playerTurn)
        game.makeMovePlayer();
      else
        game.makeMoveAI();
      playerTurn = (playerTurn == true) ? false : true;
    }
    if(game.getBoard().full())
      game.setStatus(GameStatus::DRAW);
    else if(victory(game.getBoard()) == 0)
      game.setStatus(GameStatus::O_WON);
    else if(victory(game.getBoard()) == 1)
      game.setStatus(GameStatus::X_WON);
  }
 
  int victory(Board& b) {
    // return winning symbol or -1 if no winner yet
    // implement logic ..
    return -1;
  }
 
  void printResult(void) {
    if(game.getStatus() == GameStatus::DRAW)
      cout << "Draw!\n";
    else if(game.getStatus() == GameStatus::O_WON)
      cout << "O won!\n";
    else
      cout << "X won!\n";
  }
 private:
  Game game;
};
 
int main(void)
{
  ConsoleRunner consoleRunner(1, "gsamaras", 'X');
  consoleRunner.play();
  consoleRunner.printResult();
  return 0;
}
