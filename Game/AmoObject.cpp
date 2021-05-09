#include "AmoObject.h"
//xây dựng đạn
AmoObject::AmoObject()
{
	rect_.x = 0;
	rect_.y = 0;

	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false; // Chưa xuất hiện đạn
	amo_type_ = NONE; //đạn ko có dạng gì 
}

AmoObject::~AmoObject()
{

}

void AmoObject::HandleMove(const int& x_border, const int& y_border) //nhân vật
{
	rect_.x += x_val_; //quỹ đạo bắn thẳng 1 đoạn x_val_ đvi
	if (rect_.x > x_border)
	{
		is_move_ = false;
	}
}

void AmoObject::HandleMoveRightToLeft() //địch bắn
{
	rect_.x -= x_val_; //đạn di chuyển x_val_ đvi
	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}

void AmoObject::HandleInputAction(SDL_Event events)
{
	;
}