#pragma once
class KeyboardControls
{
public:

	KeyboardControls();

	static void SetUpKey(bool);
	static void SetDownKey(bool);
	static void SetLeftKey(bool);
	static void SetRightKey(bool);

	static bool GetUpKey();
	static bool GetDownKey();
	static bool GetLeftKey();
	static bool GetRightKey();

	
	~KeyboardControls();

private:
	static bool upKey;
	static bool downKey;
	static bool leftKey;
	static bool rightKey;
};

