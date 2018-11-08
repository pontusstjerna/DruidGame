#pragma once

class SolidObject
{
	public:
		virtual int GetX() = 0;
		virtual int GetY() = 0;
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual char* GetImg() = 0;
};