#pragma once
#include "Block.h"
#include "GameObject.h"
#include "../view/AnimatedPlayer.h"

class Model 
{

	public:
		virtual char* GetBackground() = 0;

		virtual int getNumberBlocks() = 0;
		virtual Block** getBlocks() = 0;
		virtual int GetNumberofObjects() = 0;
		virtual GameObject** GetObjects() = 0;
        virtual AnimatedPlayer* getPlayer() = 0;
};

