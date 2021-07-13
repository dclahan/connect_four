#include <string>
#include <cassert>
#include "Board.h"


int main(){
	
	Board b("R","Y",".");
	bool p1_turn = true;
	std::string result = ".";
	std::string whose_turn;

	std::cout << "Player 1 is RED (R) and Player 2 is YELLOW (Y)" << std::endl;
	while (result == "."){
		std::cout << "board:" << std::endl << b << std::endl;
		if (p1_turn)
			whose_turn = "player 1 ";
		else
			whose_turn = "player 2 ";
		std::cout << whose_turn << std::endl << "pick a column 0 -> " << std::endl;
		int turn;
		std::cin >> turn;
		result = b.insert(turn,p1_turn);
		p1_turn = !p1_turn;
	}
	std::cout << "board:" << std::endl << b << std::endl;
	std::cout << "CONGRATS " << whose_turn << " YOU WON!" << std::endl;

	return 0;
}

