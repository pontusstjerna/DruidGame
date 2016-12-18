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

		const int MIN_WIDTH = 20;
		const int MIN_HEIGHT = 20;

	private:
		char* Texture;
		int X, Y, W, H;
};