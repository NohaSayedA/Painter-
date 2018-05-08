#pragma once
class Command
{
	int wparam;
public:
	Command(int wParam);
	void Draw();
	~Command();
};

