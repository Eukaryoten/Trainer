#pragma once
class KeyboardObject
{
public:

	void SetUpKey(bool);
	void SetDownKey(bool);
	void SetLeftKey(bool);
	void SetRightKey(bool);

	void SetWKey(bool);
	void SetAKey(bool);
	void SetSKey(bool);
	void SetDKey(bool);

	bool GetUpKey();
	bool GetDownKey();
	bool GetLeftKey();
	bool GetRightKey();

	bool GetWKey();
	bool GetAKey();
	bool GetSKey();
	bool GetDKey();

protected:

	static KeyboardObject* instance;

	bool upKey;
	bool downKey;
	bool leftKey;
	bool rightKey;

	bool wKey;
	bool aKey;
	bool sKey;
	bool dKey;

};

