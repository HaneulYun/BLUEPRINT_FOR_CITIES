#pragma once
class CheckBox
{
public:
	CheckBox();
	~CheckBox();
	void initialize();
	void update();
	void render();
	void release();

	bool check;
	float x;
	float y;
};

