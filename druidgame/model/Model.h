#pragma once
#include "Block.h"
#include "GameObject.h"

class Model 
{

	public:
		virtual char* GetBackground() = 0;

		virtual int GetNumberofBlocks() = 0;
		virtual Block** GetBlocks() = 0;
		virtual int GetNumberofObjects() = 0;
		virtual GameObject** GetObjects() = 0;
};

