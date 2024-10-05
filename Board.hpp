class Board;
#pragma once
#include <iostream>

class Board {
public:
	Board(uint8_t width, uint8_t height);
	~Board();
	uint8_t getNoOfCols() const;
	uint8_t getNoOfRows() const;

private:
	uint8_t _cols;
	uint8_t _rows;
};