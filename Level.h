#pragma once

class Level
{
	public:
		Level(char* json);
		~Level();

		char* GetBackground();
		char* GetForeground();
};