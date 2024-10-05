#include "BoardRenderer.hpp"


BoardRenderer::BoardRenderer(SDL_Renderer* renderer, Board &board, int width, int height) :
	_renderer(renderer),
	_cols(board.getNoOfCols()),
	_rows(board.getNoOfRows()),
	_grid(true),
	_gridColor({ 0x5f, 0x5f, 0x5f, 0x5f}),
	_backgroundColor({ 0x00, 0x00, 0x00, 0xff }) {

	_setCellSize(width, height);
	_boardTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		_cellWidth * _cols,
		_cellHeight * _rows
	);
	std::cout << "Cols * CellWidth = " << _cellWidth * _cols << std::endl;
}

BoardRenderer::~BoardRenderer() {
	SDL_DestroyTexture(_boardTexture);
}

void BoardRenderer::_setCellSize(int width, int height) {
	_cellWidth = width / _cols;
	_cellHeight = height / _rows;
}

void BoardRenderer::render() const {
	SDL_SetRenderTarget(_renderer, _boardTexture);
	SDL_SetRenderDrawColor(_renderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a);
	SDL_RenderClear(_renderer);
	if (_grid) {
		_renderGrid();
	}
	SDL_SetRenderTarget(_renderer, NULL);
}

void BoardRenderer::_renderGrid() const {
	SDL_SetRenderDrawColor(_renderer, _gridColor.r, _gridColor.g, _gridColor.b, _gridColor.a);

	SDL_Rect rect = {0, 0, _cellWidth * _cols, _cellHeight * _rows};
	SDL_RenderDrawRect(_renderer, &rect);
	for (int y = 0; y < _rows; y++) {
		SDL_Rect rect = {0, y * _cellHeight, _cols * _cellWidth, 1};
		SDL_RenderDrawRect(_renderer, &rect);
	}
	for (int x = 0; x < _cols; x++) {
		SDL_Rect rect = {x * _cellWidth, 0, 1, _rows * _cellHeight};
		SDL_RenderDrawRect(_renderer, &rect);
	}
}