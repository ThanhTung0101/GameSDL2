#include "PlayerPower.h"

PlayerPower::PlayerPower()
{

}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xpos)
{
	pos_list_.push_back(xpos);
}

void PlayerPower::Render(SDL_Surface* des) //hiển thị 3 trái tim ở 3 vị trí
{
	if (number_ == pos_list_.size())
	{
		for (int i = 0; i < pos_list_.size(); i++)
		{
			rect_.x = pos_list_.at(i);
			Show(des);
		}
	}
}

void PlayerPower::Init()
{
	LoadImg("traitim.png");
	number_ = 3; //số mạng
	if (pos_list_.size() > 0)
	{
		pos_list_.clear();
	}

	AddPos(20);
	AddPos(70);
	AddPos(120); // vị trí trái tim
}

void PlayerPower::Decrease()
{
	number_ --;
	pos_list_.pop_back();
}