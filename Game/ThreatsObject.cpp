#include "ThreatsObject.h"

//vị trí ban đầu địch
ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT*0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject() //xóa các biến đạn, địch
{
	if (p_amo_list_.size() > 0)
	{
		for (int i = 0; i < p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo) //nạp đạn từ bên ngoài vào
{
	if (p_amo)
	{
		bool ret = p_amo->LoadImg("amo_corona1.png"); //đạn
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->set_type(AmoObject::SPHERE);
			p_amo->SetRect(rect_.x,rect_.y + rect_.h*0.5);
			p_amo-> set_x_val(8); //đạn di chuyển 
			p_amo_list_.push_back(p_amo);
		}
	}
}

//làm đạn cho địch
void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveRightToLeft(); //đạn bắn từ phải qua trái
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			}
		}
	}
}

void ThreatObject::HandleMove(const int& x_bordr, const int& y_border)
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = SCREEN_WIDTH;
		//kẻ địch xuất hiện ở vị trí khác nhau
		int rand_y = rand()%400;
		if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
		{
			rand_y = SCREEN_HEIGHT *0.3;
		}
		rect_.y = rand_y;
	}
}

void ThreatObject::HandleInputAction(SDL_Event events)
{

}

void ThreatObject::Reset(const int& xboder) // địch quay về vị trí ban đầu sau va chạm
{
	rect_.x = xboder;
	//kẻ địch xuất hiện ở vị trí khác nhau
	int rand_y = rand()%400;
	if (rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
	{
		rand_y = SCREEN_HEIGHT *0.3;
	}
	rect_.y = rand_y;

	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if (p_amo)
		{
			ResetAmo(p_amo);
		}
	}
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x,rect_.y + rect_.h*0.5);
}