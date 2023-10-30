#pragma once
#include <Siv3D.hpp>

class UI
{
private:

	const Font font;

	String txtTime;
	double time;

	String txtPersonHelp;
	int16 personHelp;

	String txtHP;
	const Texture emojiHart;
	int16 hp;

public:

	UI();

	void Update();

	void Draw() const;

	inline void PersonPurasu()
	{
		personHelp++;
	}

	inline int16 GetPersonHelp()
	{
		return personHelp;
	}
	inline void SetHp(int16 newHp)
	{
		hp = newHp;
	}
};
