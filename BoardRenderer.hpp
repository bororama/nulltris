class BoardRenderer;
#pragma once
#include <SDL2/SDL.h>
#include "Board.hpp"


struct BoardRendererBuilder {
	SDL_Renderer	*renderer;
	Board 			&board;
	int 			width;
	int 			height;
	BoardRendererBuilder(SDL_Renderer* renderer, Board &board, int max_width, int max_height) :
		board(board),
		width(0),
		height(0),
		renderer(renderer) {

		if (max_width > max_height) {
			height = max_height;
			width = max_height * board.getNoOfCols() / board.getNoOfRows();
		}
		
		else {
			width = max_width;
			height = max_width * board.getNoOfRows() / board.getNoOfCols();
		}
	}
};

class BoardRenderer {
	public:
		BoardRenderer(SDL_Renderer* renderer, Board &board, int width, int height);
		BoardRenderer(const BoardRendererBuilder &builder);
		~BoardRenderer();

		void 		render() const;
		int 		getWidth() const;
		int 		getHeight() const;
		SDL_Texture	*getTexture() const;	
		

	private:
		Board			&_board;
		SDL_Renderer	*_renderer;
		SDL_Texture		*_boardTexture;
		int				_cols;
		int				_rows;
		int				_width;
		int				_height;
		int				_cellWidth;
		int				_cellHeight;
		bool			_grid;
		SDL_Color		_gridColor;
		SDL_Color		_backgroundColor;

		void _init(int width, int height);
		void _setCellSize(int width, int height);
		void _renderGrid() const;
		
};