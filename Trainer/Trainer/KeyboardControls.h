#pragma once
class KeyboardControls
{
public:

	KeyboardControls();

	static void SetUpKey(bool);
	static void SetDownKey(bool);
	static void SetLeftKey(bool);
	static void SetRightKey(bool);

	static bool GetUpKey(bool);
	static bool GetDownKey(bool);
	static bool GetLeftKey(bool);
	static bool GetRightKey(bool);

	
	~KeyboardControls();

private:
	static bool upKey;
	static bool downKey;
	static bool leftKey;
	static bool rightKey;
};

