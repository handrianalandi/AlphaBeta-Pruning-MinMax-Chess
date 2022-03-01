// Charlton Gilbert C14190037
// Andreas Kevin C14190079
// Kevin Natan C14190080
// Jeremy Muliawan C14190227
// Handrian Alandi C14190231
// Topik : Aplikasi MiniMax + Alpha Beta Pruning ke permainan catur
// Untuk testing AI cari fungsi testSatu() atau testDua()
// Thankyou ko Hans !
#include <iostream>
#include <vector>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <sstream>  
using namespace std;
class CAPiece
{
public:
	CAPiece(char color) : pieceColor(color) {}
	~CAPiece() {}
	virtual char getPiece() = 0;
	virtual string getPieceName() = 0;
	char getColor() {
		return pieceColor;
	}
	bool IsLegalMove(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		CAPiece* destBox = currBoard[destRow][destCol];
		if ((destBox == 0) || (pieceColor != destBox->getColor())) {
			return isSquaresLegal(startRow, startCol, destRow, destCol, currBoard);
		}
		return false;
	}
private:
	virtual bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) = 0;
	char pieceColor;
};

class CPawn : public CAPiece
{
public:
	CPawn(char color) : CAPiece(color) {}
	~CPawn() {}
private:
	virtual char getPiece() {
		return 'P';
	}
	virtual string getPieceName() {
		return "Pion";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		CAPiece* destBox = currBoard[destRow][destCol];
		if (destBox == 0) {
			if (startCol == destCol) {
				if (getColor() == 'W') {

					if (destRow == startRow + 1) {
						return true;
					}
					if (startRow == 1 && destRow == startRow + 2) {
						return true;
					}
				}
				else {
					if (destRow == startRow - 1) {
						return true;
					}
					if (startRow == 6 && destRow == startRow - 2) {
						return true;
					}

				}
			}
		}
		else {
			if ((startCol == destCol + 1) || (startCol == destCol - 1)) {
				if (getColor() == 'W') {
					if (destRow == startRow + 1) {
						return true;
					}
				}
				else {
					if (destRow == startRow - 1) {
						return true;
					}
				}
			}
		}
		return false;
	}
};

class CBishop : public CAPiece
{
public:
	CBishop(char color) : CAPiece(color) {}
	~CBishop() {}
private:
	virtual char getPiece() {
		return 'B';
	}
	virtual string getPieceName() {
		return "Mentri";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		if ((destCol - startCol == destRow - startRow) || (destCol - startCol == startRow - destRow)) {
			int rowOffset = (destRow - startRow > 0) ? 1 : -1;
			int colOffset = (destCol - startCol > 0) ? 1 : -1;
			int checkRow;
			int checkCol;
			for (checkRow = startRow + rowOffset, checkCol = startCol + colOffset;
				checkRow != destRow;
				checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
			{
				if (currBoard[checkRow][checkCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class CKnight : public CAPiece
{
public:
	CKnight(char color) : CAPiece(color) {}
	~CKnight() {}
private:
	virtual char getPiece() {
		return 'N';
	}
	virtual string getPieceName() {
		return "Kuda";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		if ((startCol == destCol + 1) || (startCol == destCol - 1)) {
			if ((startRow == destRow + 2) || (startRow == destRow - 2)) {
				return true;
			}
		}
		if ((startCol == destCol + 2) || (startCol == destCol - 2)) {
			if ((startRow == destRow + 1) || (startRow == destRow - 1)) {
				return true;
			}
		}
		return false;
	}
};

class CRook : public CAPiece
{
public:
	CRook(char color) : CAPiece(color) {}
	~CRook() {}
private:
	virtual char getPiece() {
		return 'R';
	}
	virtual string getPieceName() {
		return "Benteng";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		if (startRow == destRow) {
			int colOffset = (destCol - startCol > 0) ? 1 : -1;
			for (int checkCol = startCol + colOffset; checkCol != destCol; checkCol = checkCol + colOffset) {
				if (currBoard[startRow][checkCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if (destCol == startCol) {
			int rowOffset = (destRow - startRow > 0) ? 1 : -1;
			for (int checkRow = startRow + rowOffset; checkRow != destRow; checkRow = checkRow + rowOffset) {
				if (currBoard[checkRow][startCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class CQueen : public CAPiece
{
public:
	CQueen(char color) : CAPiece(color) {}
	~CQueen() {}
private:
	virtual char getPiece() {
		return 'Q';
	}
	virtual string getPieceName() {
		return "Ratu";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		if (startRow == destRow) {
			int colOffset = (destCol - startCol > 0) ? 1 : -1;
			for (int checkCol = startCol + colOffset; checkCol != destCol; checkCol = checkCol + colOffset) {
				if (currBoard[startRow][checkCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if (destCol == startCol) {
			int rowOffset = (destRow - startRow > 0) ? 1 : -1;
			for (int checkRow = startRow + rowOffset; checkRow != destRow; checkRow = checkRow + rowOffset) {
				if (currBoard[checkRow][startCol] != 0) {
					return false;
				}
			}
			return true;
		}
		else if ((destCol - startCol == destRow - startRow) || (destCol - startCol == startRow - destRow)) {
			int rowOffset = (destRow - startRow > 0) ? 1 : -1;
			int colOffset = (destCol - startCol > 0) ? 1 : -1;
			int checkRow;
			int checkCol;
			for (checkRow = startRow + rowOffset, checkCol = startCol + colOffset;
				checkRow != destRow;
				checkRow = checkRow + rowOffset, checkCol = checkCol + colOffset)
			{
				if (currBoard[checkRow][checkCol] != 0) {
					return false;
				}
			}
			return true;
		}
		return false;
	}
};

class CKing : public CAPiece
{
public:
	CKing(char color) : CAPiece(color) {}
	~CKing() {}
private:
	virtual char getPiece() {
		return 'K';
	}
	virtual string getPieceName() {
		return "Raja";
	}
	bool isSquaresLegal(int startRow, int startCol, int destRow, int destCol, CAPiece* currBoard[8][8]) {
		int rowDelta = destRow - startRow;
		int colDelta = destCol - startCol;
		if (((rowDelta >= -1) && (rowDelta <= 1)) &&
			((colDelta >= -1) && (colDelta <= 1)))
		{
			return true;
		}
		return false;
	}
};

class cekjalan {
public:
	int fromx, fromy, tox, toy;
	string lengkap;
	void print(CAPiece* board[8][8]) {
		cout << board[fromx][fromy]->getPieceName() << "(" << fromx + 1 << "," << fromy + 1 << ") to (" << tox + 1 << "," << toy + 1 << ")" << endl;
	}
};

class CBoard
{
public:
	CBoard() {
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				runningBoard[row][col] = 0;
			}
		}
		for (int col = 0; col < 8; col++) {
			runningBoard[6][col] = new CPawn('B');
		}
		runningBoard[7][0] = new CRook('B');
		runningBoard[7][1] = new CKnight('B');
		runningBoard[7][2] = new CBishop('B');
		runningBoard[7][3] = new CQueen('B');
		runningBoard[7][4] = new CKing('B');
		runningBoard[7][5] = new CBishop('B');
		runningBoard[7][6] = new CKnight('B');
		runningBoard[7][7] = new CRook('B');
		for (int col = 0; col < 8; col++) {
			runningBoard[1][col] = new CPawn('W');
		}
		runningBoard[0][0] = new CRook('W');
		runningBoard[0][1] = new CKnight('W');
		runningBoard[0][2] = new CBishop('W');
		runningBoard[0][3] = new CQueen('W');
		runningBoard[0][4] = new CKing('W');
		runningBoard[0][5] = new CBishop('W');
		runningBoard[0][6] = new CKnight('W');
		runningBoard[0][7] = new CRook('W');
	}
	CBoard(const CBoard& n) {
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				runningBoard[i][j] = n.runningBoard[i][j];
			}
		}
		availmoves = n.availmoves;
	}
	~CBoard() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				delete runningBoard[row][col];
				runningBoard[row][col] = 0;
			}
		}
	}

	void CTest1() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				delete runningBoard[row][col];
				runningBoard[row][col] = 0;
			}
		}
		runningBoard[0][7] = new CKing('W');
		runningBoard[0][6] = new CBishop('W');
		runningBoard[0][5] = new CKing('B');

		runningBoard[1][7] = new CPawn('W');
		runningBoard[1][6] = new CPawn('W');

		runningBoard[2][6] = new CPawn('B');

		runningBoard[7][7] = new CRook('B');


	}

	void CTest2() {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				delete runningBoard[row][col];
				runningBoard[row][col] = 0;
			}
		}
		runningBoard[0][2] = new CBishop('B');
		runningBoard[2][7] = new CKing('B');

		runningBoard[4][7] = new CKing('W');
		runningBoard[4][6] = new CPawn('W');
		runningBoard[4][5] = new CPawn('W');

		runningBoard[5][0] = new CRook('B');

		runningBoard[7][6] = new CBishop('B');



	}


	void Print() {
		const int squareWidth = 4;
		const int squareHeight = 3;
		for (int row = 0; row < 8 * squareHeight; ++row) {
			int squareRow = row / squareHeight;
			if (row % 3 == 1) {
				cout << '-' << (char)('1' + 7 - squareRow) << '-';
			}
			else {
				cout << "---";
			}
			for (int col = 0; col < 8 * squareWidth; ++col) {
				int squareCol = col / squareWidth;
				if (((row % 3) == 1) && ((col % 4) == 1 || (col % 4) == 2) && runningBoard[7 - squareRow][squareCol] != 0) {
					if ((col % 4) == 1) {
						cout << runningBoard[7 - squareRow][squareCol]->getColor();
					}
					else {
						cout << runningBoard[7 - squareRow][squareCol]->getPiece();
					}
				}
				else {
					if ((squareRow + squareCol) % 2 == 1) {
						cout << '*';
					}
					else {
						cout << ' ';
					}
				}
			}
			if (row == 0) {
				cout << "\tB  = Hitam";
			}
			if (row == 1) {
				cout << "\tW  = Putih";
			}
			if (row == 2) {
				cout << "\tK  = Raja";
			}
			if (row == 3) {
				cout << "\tQ  = Ratu";
			}
			if (row == 4) {
				cout << "\t_B = Mentri";
			}
			if (row == 5) {
				cout << "\tN  = Kuda";
			}
			if (row == 6) {
				cout << "\tR  = Benteng";
			}
			if (row == 7) {
				cout << "\tP  = Pion";
			}
			cout << endl;
		}
		for (int row = 0; row < squareHeight; ++row) {
			if (row % 3 == 1) {
				cout << "---";
				for (int col = 0; col < 8 * squareWidth; ++col) {
					int iSquareCol = col / squareWidth;
					if ((col % 4) == 1) {
						cout << (iSquareCol + 1);
					}
					else {
						cout << '-';
					}
				}
				cout << endl;
			}
			else {
				for (int col = 1; col < 9 * squareWidth; ++col) {
					cout << '-';
				}
				cout << endl;
			}
		}
	}

	bool isInCheck(char color) {
		int kingRow;
		int kingCol;
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (runningBoard[row][col] != 0) {
					if (runningBoard[row][col]->getColor() == color) {
						if (runningBoard[row][col]->getPiece() == 'K') {
							kingRow = row;
							kingCol = col;
						}
					}
				}
			}
		}
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (runningBoard[row][col] != 0) {
					if (runningBoard[row][col]->getColor() != color) {
						if (runningBoard[row][col]->IsLegalMove(row, col, kingRow, kingCol, runningBoard)) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool CanMove(char color) {
		bool moveable = false;
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (runningBoard[row][col] != 0) {
					if (runningBoard[row][col]->getColor() == color) {
						for (int destRow = 0; destRow < 8; destRow++) {
							for (int destCol = 0; destCol < 8; destCol++) {
								if (runningBoard[row][col]->IsLegalMove(row, col, destRow, destCol, runningBoard)) {
									CAPiece* tempPiece = runningBoard[destRow][destCol];
									runningBoard[destRow][destCol] = runningBoard[row][col];
									runningBoard[row][col] = 0;
									bool bCanMove = !isInCheck(color);
									runningBoard[row][col] = runningBoard[destRow][destCol];
									runningBoard[destRow][destCol] = tempPiece;
									if (bCanMove) {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
		return false;
	}
	void checkallavailmove(char color) {
		//bedanya ini dengan diatas adalah, ini untuk melist setiap pergerakan yang bisa berjalan dan dimasukan ke vector availmoves
		availmoves.clear();
		bool moveable = false;
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				if (runningBoard[row][col] != 0) {
					if (runningBoard[row][col]->getColor() == color) {
						for (int destRow = 0; destRow < 8; destRow++) {
							for (int destCol = 0; destCol < 8; destCol++) {
								if (runningBoard[row][col]->IsLegalMove(row, col, destRow, destCol, runningBoard)) {
									cekjalan tempcek;
									tempcek.fromx = row;
									tempcek.fromy = col;
									tempcek.tox = destRow;
									tempcek.toy = destCol;
									CAPiece* tempPiece = runningBoard[destRow][destCol];
									runningBoard[destRow][destCol] = runningBoard[row][col];
									runningBoard[row][col] = 0;
									bool bCanMove = !isInCheck(color);
									runningBoard[row][col] = runningBoard[destRow][destCol];
									runningBoard[destRow][destCol] = tempPiece;
									if (bCanMove) {
										availmoves.push_back(tempcek);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//king=90,queen=9,benteng=5,kuda=3,mentri=3,pion=1
	int boardFitness() {
		int whiteFitness = 0;
		int blackFitness = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (runningBoard[i][j] != 0) {
					if (runningBoard[i][j]->getPiece() == 'K') {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 90;
						}
						else {
							blackFitness +=  90;
						}
					}
					else if (runningBoard[i][j]->getPiece() == 'Q') {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 9;
						}
						else {
							blackFitness += 9;
						}
					}
					else if (runningBoard[i][j]->getPiece() == 'R') {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 5;
						}
						else {
							blackFitness += 5;
						}
					}
					else if (runningBoard[i][j]->getPiece() == 'B') {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 3;
						}
						else {
							blackFitness += 3;
						}
					}
					else if (runningBoard[i][j]->getPiece() == 'N') {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 3;
						}
						else {
							blackFitness += 3;
						}
					}
					else {
						if (runningBoard[i][j]->getColor() == 'W') {
							whiteFitness += 1;
						}
						else {
							blackFitness += 1;
						}
					}
				}
			}
		}
		return blackFitness - whiteFitness;
	}




	void printallavailmoves() {
		for (auto e : availmoves) {
			e.print(runningBoard);
		}
	}
	CAPiece* runningBoard[8][8];
	vector<cekjalan>availmoves;
};

class CChess
{
public:

	CChess() : moveTurn('W') {}
	~CChess() {}

	cekjalan aimove(int difficulty) {
		cekjalan bestMove;
		alphabetaMax(-999, 999, difficulty, bestMove, difficulty);
		return bestMove;
	}

	int alphabetaMax(int alpha, int beta, int depth, cekjalan& bestMove, int startingDepth) {
		if (depth == 0) { return Board.boardFitness(); }
		Board.checkallavailmove('B');
		vector<cekjalan>tempjalan = Board.availmoves;
		for (auto e : tempjalan) {
			//moving
			CAPiece* tempPiece = Board.runningBoard[e.tox][e.toy];
			Board.runningBoard[e.tox][e.toy] = Board.runningBoard[e.fromx][e.fromy];
			Board.runningBoard[e.fromx][e.fromy] = 0;
			AlternateTurn();
			int hasil = alphabetaMin(alpha, beta, depth - 1, bestMove, startingDepth);
			AlternateTurn();
			//rollback
			Board.runningBoard[e.fromx][e.fromy] = Board.runningBoard[e.tox][e.toy];
			Board.runningBoard[e.tox][e.toy] = tempPiece;
			if (hasil > alpha) {
				alpha = hasil;
				if (depth == startingDepth) {
					bestMove = e;
				}
			}
			if (alpha >= beta) {
				return alpha;
			}

		}
		return alpha;
	}
	int alphabetaMin(int alpha, int beta, int depth, cekjalan& bestMove, int startingDepth) {
		if (depth == 0) { return Board.boardFitness(); }
		Board.checkallavailmove('W');
		vector<cekjalan>tempjalan = Board.availmoves;
		for (auto e : tempjalan) {
			//moving
			CAPiece* tempPiece = Board.runningBoard[e.tox][e.toy];
			Board.runningBoard[e.tox][e.toy] = Board.runningBoard[e.fromx][e.fromy];
			Board.runningBoard[e.fromx][e.fromy] = 0;
			AlternateTurn();
			int hasil = alphabetaMax(alpha, beta, depth - 1, bestMove, startingDepth);
			AlternateTurn();
			//rollback
			Board.runningBoard[e.fromx][e.fromy] = Board.runningBoard[e.tox][e.toy];
			Board.runningBoard[e.tox][e.toy] = tempPiece;

			if (hasil < beta) {
				beta = hasil;
			}
			if (alpha >= beta) {
				return beta;
			}


		}
		return beta;
	}
	void testSatu() {
		Board.CTest1();
		moveTurn = 'B';
	}
	void testDua() {
		Board.CTest2();
		moveTurn = 'B';
	}
	void Start(int difficult) {
		//untuk test = https://www.chess.com/blog/ThePawnSlayer/checkmate-in-two-puzzles-test-very-hard 
		//ketika ngetest, kita jadi yang hitam DI WEB, sedangkan AI nya jadi yang putih DI WEB(pergerakan AI nya bisa di cek dengan cara di samakan dengan hint di web tsb)
		//testSatu = puzzle 1
		//testDua  = puzzle 8
		//hilangkan salah satu comment dibawah untuk start test
		//testSatu();
		//testDua();

		switch (difficult) {
		case 1:
			difficulty = 4; break;
		case 2:
			difficulty = 5; break;
		case 3:
			difficulty = 6; break;
		}
		do {
			Board.checkallavailmove(moveTurn);
			getNextMove(Board.runningBoard);
			AlternateTurn();
		} while (!isGameOver());
		


	}

	void getNextMove(CAPiece* currentBoard[8][8]) {
		using namespace std;
		bool isMoveValid = false;
		do {
			Board.Print();
			cout << lastmove.str() << endl;

			int startRow;
			int startCol;
			int endRow;
			int endCol;
			if (moveTurn == 'B') {
				cekjalan hasil = aimove(difficulty);
				startRow = hasil.fromx;
				startCol = hasil.fromy;
				endRow = hasil.tox;
				endCol = hasil.toy;

			}
			else {
				cout << moveTurn << "'s Move: \n";
				cout << "Starting Position(X):"; cin >> startCol;
				cout << "Starting Position(Y):"; cin >> startRow;
				cout << "Destination Position(X):"; cin >> endCol;
				cout << "Destination Position(Y):"; cin >> endRow;
				startRow -= 1;
				startCol -= 1;
				endRow -= 1;
				endCol -= 1;
			}


			//validasi kotak di papan catur
			if ((startRow >= 0 && startRow <= 7) &&
				(startCol >= 0 && startCol <= 7) &&
				(endRow >= 0 && endRow <= 7) &&
				(endCol >= 0 && endCol <= 7)) {
				CAPiece* currentPiece = currentBoard[startRow][startCol];
				//cek warna
				if ((currentPiece != 0) && (currentPiece->getColor() == moveTurn)) {
					//validasi tujuan dari pergerakan yang dilakukan
					if (currentPiece->IsLegalMove(startRow, startCol, endRow, endCol, currentBoard)) {
						//gerak
						CAPiece* tempPiece = currentBoard[endRow][endCol]; //temp digunakan ketika checkmate terjadi sehingga gerakan tersebut di undo
						currentBoard[endRow][endCol] = currentBoard[startRow][startCol];
						currentBoard[startRow][startCol] = 0;
						//cek untuk checkmate
						if (Board.isInCheck(moveTurn)) {
							currentBoard[startRow][startCol] = currentBoard[endRow][endCol];
							currentBoard[endRow][endCol] = tempPiece;
						}
						else{
							delete tempPiece;
							isMoveValid = true;
						}
					}
				}
			}
			if (!isMoveValid) {
				cout << "Invalid Move!" << endl;
			}
			else {
				lastmove.str("");
				lastmove.clear();
				lastmove << "Player " << moveTurn << " Moved " << currentBoard[endRow][endCol]->getPieceName() << "(" << startCol + 1 << "," << startRow + 1 << ") to (" << endCol + 1 << "," << endRow + 1 << ")";
			}
		} while (!isMoveValid);
	}

	void AlternateTurn() {
		moveTurn = (moveTurn == 'W') ? 'B' : 'W';
	}

	bool isGameOver() {
		bool Moveable = false;
		Moveable = Board.CanMove(moveTurn);
		if (!Moveable) {
			if (Board.isInCheck(moveTurn)) {
				AlternateTurn();
				Board.Print();
				cout << lastmove.str() << endl;
				cout << "Checkmate, " << moveTurn << " Wins!" << endl;
			}
			else {
				cout << "Stalemate!" << endl;
			}
		}
		return !Moveable;
	}
private:
	CBoard Board;
	char moveTurn;
	int difficulty = 3;
	stringstream lastmove;
};

int main() {
	CChess Game;
	int chc = 0;
	do {
		system("cls");
		cout << "Difficulty: \n1. Easy\n2. Medium\n3. Hard\nChoice: "; cin >> chc;
		if (chc < 1 || chc>3) {
			cout << "Difficulty doesn't Exist, Try Again!\n";
		}
	} while (chc < 1 || chc>3);
	Game.Start(chc);
	return 0;
}