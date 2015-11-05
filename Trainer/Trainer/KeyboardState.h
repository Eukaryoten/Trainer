#pragma once
class KeyboardState
{
public:

	static void SetUpKey(bool);
	static void SetDownKey(bool);
	static void SetLeftKey(bool);
	static void SetRightKey(bool);

	static void SetWKey(bool);
	static void SetAKey(bool);
	static void SetSKey(bool);
	static void SetDKey(bool);

	static bool GetUpKey();
	static bool GetDownKey();
	static bool GetLeftKey();
	static bool GetRightKey();

	static bool GetWKey();
	static bool GetAKey();
	static bool GetSKey();
	static bool GetDKey();

private:

	static bool upKey;
	static bool downKey;
	static bool leftKey;
	static bool rightKey;

	static bool wKey;
	static bool aKey;
	static bool sKey;
	static bool dKey;
};

