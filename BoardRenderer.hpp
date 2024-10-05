class BoardRenderer;
#pragma once
#include <SDL2/SDL.h>
#include "Board.hpp"
class BoardRenderer {
	public:
		BoardRenderer(SDL_Renderer* renderer, Board &board, int width, int height);
		~BoardRenderer();
		void render() const;
		SDL_Texture		*_boardTexture;//encapsulates the board texture

	private:
		SDL_Renderer	*_renderer;
		int				_cols;
		int				_rows;
		int				_cellWidth;
		int				_cellHeight;
		bool			_grid;
		SDL_Color		_gridColor;
		SDL_Color		_backgroundColor;

		void _setCellSize(int width, int height);
		void _renderGrid() const;
		
};