#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
const int Size = 9;

int board[9][9];

void PrintBoard(int board[9][9])
{
	for (int row = 0; row < Size; row++)
	{
		
		
		if (row==3||row==6)
		{
			std::cout << "-----------------------\n";
			

		}
		for (int clmn = 0; clmn < Size; clmn++)
		{

			std::cout << board[row][clmn]<<" ";
			if (clmn == 2 || clmn == 5)
			{
				std::cout << " | ";
				
			}

		}
		std::cout << "\n";
	};

}


bool isValid(int board[Size][Size], int row, int col, int num) {
	// Sat�rda kontrol
	for (int x = 0; x < Size; x++) {
		if (board[row][x] == num)
			return false;
	}

	// S�tunda kontrol
	for (int x = 0; x < Size; x++) {
		if (board[x][col] == num)
			return false;
	}

	// 3x3 blok kontrol
	int startRow = row - row % 3;
	int startCol = col - col % 3;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[startRow + i][startCol + j] == num)
				return false;
		}
	}

	return true;
}
bool SolveSudoku(int board[Size][Size]) {
	for (int row = 0; row < Size; row++) {
		for (int col = 0; col < Size; col++) {
			if (board[row][col] == 0) {
				for (int num = 1; num <= 9; num++) {
					if (isValid(board, row, col, num)) {
						board[row][col] = num; // yerle�tir

						if (SolveSudoku(board)) {
							return true; // ��z�m bulundu
						}

						board[row][col] = 0; // geri al (backtrack)
					}
				}

				return false; // hi�bir say� uygun de�ilse
			}
		}
	}
	
	return true; // t�m h�creler doluysa
	
}

bool ReadBoardFromFile(const std::string& filename, int board[9][9]) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Dosya a��lamad�: " << filename << std::endl;
		return false;
	}

	std::string line;
	int row = 0;
	while (std::getline(file, line) && row < 9) {
		std::stringstream ss;
		for (char c : line) {
			if (std::isdigit(c) || c == ' ') ss << c; // Sadece say�lar ve bo�luklar� al
		}
		for (int col = 0; col < 9; ++col) {
			if (!(ss >> board[row][col])) {
				std::cerr << "Dosya format�nda hata! " << row << ". sat�r, " << col << ". s�tun okunamad�.\n";
				return false;
			}
		}
		row++;
	}

	return true;
}
bool WriteBoardToFile(const std::string& filename, int board[9][9]) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cerr << "Dosya yazma hatas�: " << filename << std::endl;
		return false;
	}

	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			outFile << board[row][col] << " ";
		}
		outFile << "\n";
	}

	outFile.close();
	return true;
}

int main()
{


	
	if (!ReadBoardFromFile("sudoku.txt", board)) {
		std::cout << "dosya okunmad�.";
	}





	std::cout << "--------------SUDOKU TAHTASI-------------------\n";
	
	
	PrintBoard(board);
	if (SolveSudoku(board)) {
		std::cout << "\ncozum:\n";
		PrintBoard(board);
		WriteBoardToFile("cozum.txt", board);
	}
	else {
		std::cout << "\n��z�m bulunamad�!\n";
	}



	
	std::cin.get();
	


	std::cin.get();







}