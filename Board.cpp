#include <iostream>
#include <string>


#include "Board.h"

	Board::Board(const std::string& play1, const std::string& play2, const std::string& blank){
		player1_ = play1;
		player2_ = play2;
		blank_ = blank;
		rows = 5;
		columns = 4;
		//initialize board
		m_data = new std::string*[columns];
		for (unsigned int i = 0; i < columns; ++i){
			m_data[i] = new std::string[rows];
			for (unsigned int j = 0; j < rows; ++j){
				m_data[i][j] = blank_;
			}
		}

	}

	Board::~Board(){
		for (unsigned int i = 0; i < columns; ++i){
			delete [] m_data[i];
		}
		delete [] m_data;
	}

	void Board::copy(const Board& bd) {
		this->rows = bd.numRows();
		this->columns = bd.numColumns();
		this->m_data = new std::string*[this->columns];
		for (unsigned int i = 0; i < this->columns; ++i){
			this->m_data[i] = new std::string[this->rows];
		}
		for (unsigned int i = 0; i < this->columns; ++i){
			for (unsigned int j = 0; j < this->rows; ++j){
				this->m_data[i][j] = bd.get_data(i,j);// get_data returns a const string that we can assign to m_data values
			}
		}
	}

	Board& Board::operator=(const Board& bd) {
		if (this != &bd) {
			for (unsigned int i = 0; i < columns; ++i){
				delete [] m_data[i];
			}
			delete [] m_data;
			this -> copy(bd);
		}
		return *this;
	}

	void Board::clear(){
		unsigned int old_col = columns;
		columns = 4;
		rows = 5;
		std::string** new_data;
		new_data = new std::string*[columns];
		for (unsigned int i = 0; i < columns; ++i){
			new_data[i] = new std::string[rows];
			for (unsigned int j = 0; j < rows; ++j){
				new_data[i][j] = blank_;
			}
		}
		for (unsigned int i = 0; i < old_col; ++i){ //delete m_data and make it point at the reset board
			delete [] m_data[i];
		}
		delete [] m_data;
		m_data = new_data; 
	}


	unsigned int Board::numRows() const {
		return rows; 
	}
	unsigned int Board::numColumns() const {
		return columns;
	}


	int Board::numTokensInRow(unsigned int row_num) const {
		//row is the j value in m_data
		if (row_num >= rows || row_num < 0){
			return -1;
		}
		int num_toks = 0;
		for (unsigned int i = 0; i < columns; ++i){ 
		//for all columns -i- check this row -row_num- and count if there is a token there.
			if (m_data[i][row_num] != blank_){
				num_toks++;
			}
		}
 		return num_toks;
	}

	int Board::numTokensInColumn(unsigned int column_num) const {
		//column is i value in m_data
		if (column_num >= columns || column_num < 0){
			return -1;
		}
		int num_toks = 0;
		for (unsigned int j = 0; j < rows; ++j){
		//for all rows -j- check this column -column_num- and count if a token is there
			if (m_data[column_num][j] != blank_){ 
				num_toks++;
			}
		}
		return num_toks;
	}


	std::string Board::insert(unsigned int col, bool p1){ //apply winner_check ~after~ placing the piece

		if (col >= columns){ //if we have to add a column to the board.
			int temp = columns; //so the variable isnt changing as we add columns
			for (unsigned int i = 0; i < ((col-temp)+1); ++i) {
				this->add_column();
			}
			// adds however many columns we need to the board
		}

		// put it in the right column, for m_data[col], see if a peice is in the spot, if not, add the new one.
		unsigned int row_check = 0;
		for (unsigned int i = 0; i < rows; ++i){
			if (m_data[col][i] == blank_){
				if (p1){
					m_data[col][i] = player1_;
					break;
				} else {
					m_data[col][i] = player2_;
					break;
				}
			} else {
				row_check++;
			}
		}
		if (row_check == rows) { //if the column is full (could've also done if numtokensincolumn(col) == rows) but hey, just as efficient.
			this->add_row();
			if (p1){
				m_data[col][rows-1] = player1_;
			} else {
				m_data[col][rows-1] = player2_;
			}
		}

		std::string value = this->winner_check(); //see if there is a winner, return the winners piece or the blank peice.
		return value;
	}

	const std::string Board::winner_check() const { // for iterators, check_winner takes in place value (pointer?) and then checks the surrounding itr+1 itr+2
		for (unsigned int i = 0; i < columns; ++i){
			if (this->numTokensInColumn(i) == 0){
				continue;
			}
			for (unsigned int j = 0; j < rows; j++){
				if (this->numTokensInRow(j) == 0)
					continue;

				if (m_data[i][j] != blank_){
					int four_in_a_row = 1;
					bool p_1 = true;
					if (m_data[i][j] == player2_){
						p_1 = false;
					}
					unsigned int k = j;
					while (m_data[i][k] == m_data[i][j] && k < (rows-1)){ //check going up the column
						if (four_in_a_row == 4){
							if (p_1)
								return player1_;
							else
								return player2_;
						}
						four_in_a_row++;
						k++;
					}
					four_in_a_row = 1; //reset ctr
					k = i;
					while (m_data[k][j] == m_data[i][j] && k < (columns-1)){ //check row
						if (four_in_a_row == 4){
							if (p_1)
								return player1_;
							else
								return player2_;
						}
						four_in_a_row++;
						k++;
					}
					four_in_a_row = 1; //reset ctr
					int diag = 0;
					while (i < (columns-3) && j < (rows-3) && m_data[i][j] == m_data[i+diag][j+diag]){ //check y=x diag
						if (four_in_a_row == 4){
							if (p_1)
								return player1_;
							else
								return player2_;
						}
						four_in_a_row++;
						diag++;
					}
					four_in_a_row = 1; //reset ctr
					diag = 0;
					while (i < (columns-3) && j > 2 && m_data[i][j] == m_data[i+diag][j-diag]){ //check y=-x diag
						if (four_in_a_row == 4){
							if (p_1)
								return player1_;
							else
								return player2_;
						}
						four_in_a_row++;
						diag++;
					}
				}
			}
		}
		return blank_; // if no one wins
	}


	void Board::add_column(){ //make a new board that is the copy of m_data with one more empty column to the right
		std::string** new_data = NULL;
		new_data = new std::string*[columns+1];
		for (unsigned int i = 0; i < columns; ++i){
			new_data[i] = new std::string[rows];
			for (unsigned int j = 0; j < rows; ++j){
				new_data[i][j] = m_data[i][j];
			}
		}
		new_data[columns] = new std::string[rows];
		for (unsigned int i = 0; i < rows; ++i){
			new_data[columns][i] = blank_;
		}
		for (unsigned int i = 0; i < columns; ++i){ //delete m_data and make it point at the new board
			delete [] m_data[i];
		}
		delete [] m_data;
		m_data = new_data;
		columns++; 
	}

	void Board::add_row(){ //make a new board that is a copy of m_data with one more empty row on top
		std::string** new_data;
		new_data = new std::string*[columns];
		for (unsigned int i = 0; i < columns; ++i){
			new_data[i] = new std::string[rows+1];
			for (unsigned int j = 0; j < rows; ++j){
				new_data[i][j] = m_data[i][j];
			}
		}
		for (unsigned int i = 0; i < columns; ++i){
			new_data[i][rows] = blank_;
		}
		for (unsigned int i = 0; i < columns; ++i){
			delete [] m_data[i];
		}
		delete [] m_data;
		rows++;
		m_data = new_data; //make m_data point to the new board
	}


//print functions

	const std::string Board::print_board() const { 
		std::string prints;
		for (int i = rows-1; i > -1; --i){ //start i high so it'll print the right way.
			for (unsigned int j = 0; j < columns; ++j){
				if (j == columns-1)
					prints = prints + m_data[j][i];
				else
					prints = prints + m_data[j][i] + " "; 
			}
			prints = prints + "\n";
		}
		return prints;
	}


	std::ostream& operator<<(std::ostream& os, const Board& bd){
		os << bd.print_board();
		return os;
	}