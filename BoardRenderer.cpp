#include "BoardRenderer.hpp"

BoardRenderer::BoardRenderer(SDL_Renderer* renderer, Board &board, int width, int height) :
	_board(board),
	_renderer(renderer),
	_cols(board.getNoOfCols()),
	_rows(board.getNoOfRows()),
	_grid(true),
	_gridColor({ 0x5f, 0x5f, 0x5f, 0x5f}),
	_backgroundColor({ 0x00, 0x00, 0x00, 0xff }),
	_width(width),
	_height(height) {
		_init(width, height);
}

BoardRenderer::BoardRenderer(const BoardRendererBuilder &b):
	_board(b.board)
	_renderer(b.renderer),
	_cols(b.board.getNoOfCols()),
	_rows(b.board.getNoOfRows()),
	_grid(true),
	_gridColor({ 0x5f, 0x5f, 0x5f, 0x5f}),
	_backgroundColor({ 0x00, 0x00, 0x00, 0xff }),
	_width(b.width),
	_height(b.height) {
		_init(b.width, b.height);
}

BoardRenderer::~BoardRenderer() {
	SDL_DestroyTexture(_boardTexture);
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

int BoardRenderer::getWidth() const {
	return _width;
}


int BoardRenderer::getHeight() const {
	return _height;
}

SDL_Texture* BoardRenderer::getTexture() const {
	return _boardTexture;	
}

void BoardRenderer::_init(int width, int height) {
	_setCellSize(width, height);
	_boardTexture = SDL_CreateTexture(
		_renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		_cellWidth * _cols,
		_cellHeight * _rows
	);
}

void BoardRenderer::_setCellSize(int width, int height) {
	_cellWidth = width / _cols;
	_cellHeight = height / _rows;
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