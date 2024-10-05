#include "Board.hpp"

Board::Board(uint8_t cols, uint8_t rows) : _cols(cols), _rows(rows) {
	// TODO
}

Board::~Board() {
	// TODO
}	

uint8_t	Board::getNoOfCols() const {
	return _cols;
}

uint8_t Board::getNoOfRows() const {
	return _rows;
}