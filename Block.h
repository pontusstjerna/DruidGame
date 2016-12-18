#pragma once
class Block
{
	public:
		Block(int x, int y, int width, int height, char* texture);
		~Block();

		int GetX();
		int GetY();
		int GetWidth();
		int GetHeight();
		char* GetTexture();

		const int MIN_WIDTH = 10;
		const int MIN_HEIGHT = 10;

	private:
		char* Texture;
		int X, Y, W, H;
};