#ifndef __Board_h_
#define __Board_h_
#include <iostream>
#include <string>

class Board {
public:
	//construction, assignment operators, and destructor
	Board(const std::string& play1, const std::string& play2, const std::string& blank);
	Board(const Board& bd) { copy(bd); } //the copy constructor
	~Board(); //destuctor
	Board& operator=(const Board& bd);


	//accessors
	unsigned int numRows() const;
	unsigned int numColumns() const;
	int numTokensInRow(unsigned int row_num) const;
	int numTokensInColumn(unsigned int column_num) const;

	//modifiers
	std::string insert(unsigned int col, bool p1);
	void clear(); //to clean that sucker up

	//other
	const std::string winner_check() const;
	const std::string print_board() const; //to help my operator<< function

private:
	//vairables
	std::string** m_data;
	std::string blank_;
	std::string player1_;
	std::string player2_;
	unsigned int rows, columns;

	//private functions that only I can use
	void add_column();
	void add_row();
	void copy(const Board& bd); 
	const std::string& get_data(unsigned int i, unsigned int j) const {return m_data[i][j];} //still a one-liner!
};

std::ostream& operator<<(std::ostream& os, const Board& bd);

#endif