#include "UI.hpp"

UI::UI()
	:font(32, Typeface::Bold)
	,time(0)
	,personHelp(0)
	,hp(3)
	,emojiHart(U"🦖"_emoji)
{
}

void UI::Update()
{
	if (time < 999)
	{
		time += 1 * Scene::DeltaTime();
	}
	else
	{
		time = 999;
	}
	txtTime = U"Time {}"_fmt(static_cast<int32>(time));

	txtPersonHelp = U"助けた人数{}/{}"_fmt(personHelp, 5);

	txtHP =  U"HP{}"_fmt(hp);
}

void UI::Draw() const
{
	font(txtTime).draw(10, 10);
	font(txtPersonHelp).draw(500, 10);
	font(txtHP).draw(1200, 10);
	//for (int i = 0; i < hp; ++i)
	//{
	//	emojiHart.draw(700 + i * 20, 10);
	//}
}
