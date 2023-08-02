#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

class Board {
	public:
		int board[9][9];
		vector<vector<int>> Possible;
		Board() {
			Possible.resize(81);
		}
		void loadboard() {
			// 0 for empty spaces each number separeted by a space
			ifstream data("sudoku.txt");
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					data >> board[i][j];
				}
			}
			data.close();
		}
		void display() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << board[i][j] << " ";
				}
				cout<<endl;
			}
			cout << endl;
		}
		void solve() {
			
		}
		void makeposib() {
			for (int i = 0; i < 9; i++) {
				row(i);
				collumn(i);
				square(i);
			}
			for (int i = 0; i < 81; i++) {
				sort(Possible[i].begin(), Possible[i].end());
				unique(Possible[i].begin(), Possible[i].end());
			}
			for (int i = 0; i < 81; i++) {
				if (board[i / 9][i % 9] > 0) {
					Possible[i].clear();
				}
			}
			
		}
		void row(int R) {
			vector<int> row;
			vector<int> rowposs;
			for (int i = 0; i < 9; i++) {
				row.push_back(board[R][i]);
			}
			sort(row.begin(), row.end());
			unique(row.begin(), row.end());
			if (row[0] == 0) {
				row.erase(row.begin());
			}
			for (int i = 1; i < 10; i++) {
				bool T = true;
				for (int j = 0; j < row.size(); j++) {
					if (i == row[j]) T = false;
				}
				if (T) {
					rowposs.push_back(i);
				}
			}
			for (int i = 9 * R; i < 9 * (R + 1); i++) {
				for (int j = 0; j < rowposs.size(); j++) {
					Possible[i].push_back(rowposs[j]);
				}
			}
		}

		void collumn(int C) {
			vector<int> collumn;
			vector<int> collumnposs;
			for (int i = 0; i < 9; i++) {
				collumn.push_back(board[i][C]);
			}
			sort(collumn.begin(), collumn.end());
			unique(collumn.begin(), collumn.end());
			if (collumn[0] == 0) {
				collumn.erase(collumn.begin());
			}
			for (int i = 1; i < 10; i++) {
				bool T = true;
				for (int j = 0; j < collumn.size(); j++) {
					if (i == collumn[j]) T = false;
				}
				if (T) {
					collumnposs.push_back(i);
				}
			}
			for (int i =C; i < 81; i=i+9) {
				for (int j = 0; j < collumnposs.size(); j++) {
					Possible[i].push_back(collumnposs[j]);
				}
			}
		}

		void square(int S) {
			vector<int> square;
			vector<int> squareposs;
			for (int i = (S % 3) * 3; i < ((S % 3) * 3) + 3; i++) {
				for (int j = (S / 3) * 3; j < ((S / 3) * 3) + 3; j++) {
					square.push_back(board[i][j]);
				}
			}
			sort(square.begin(), square.end());
			unique(square.begin(), square.end());
			if (square[0] == 0) {
				square.erase(square.begin());
			}
			for (int i = 1; i < 10; i++) {
				bool T = true;
				for (int j = 0; j < square.size(); j++) {
					if (i == square[j]) T = false;
				}
				if (T) {
					squareposs.push_back(i);
				}
			}
			int value=0;
			switch (S) {
			case 0:
				value = 0;
				break;
			case 1:
				value = 3;
				break;
			case 2:
				value = 6;
				break;
			case 3:
				value = 27;
				break;
			case 4:
				value = 30;
				break;
			case 5:
				value = 33;
				break;
			case 6:
				value = 54;
				break;
			case 7:
				value = 57;
				break;
			case 8:
				value = 60;
				break;
			}
			for (int x = 0; x < 3; x++) {
				for (int i = value + (9 * x); i < value + (9 * x) + 3; i++) {
					for (int j = 0; j < squareposs.size(); j++) {
						Possible[i].push_back(squareposs[j]);
					}
				}
			}
		}
};

int main() {
	Board Sudoku;
	Sudoku.loadboard();
	Sudoku.makeposib();
	for (int i = 0; i < 81; i++) {
		for (int j = 0; j < Sudoku.Possible[i].size(); i++) {
			cout << Sudoku.Possible[i][j] << " ";
		}
		cout << endl;
	}
}