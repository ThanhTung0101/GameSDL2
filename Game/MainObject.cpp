#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_ = 0;
	y_val_ = 0;
}

MainObject::~MainObject()
{
	;
}

void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* amo_sound[2])
{
	//bắt sự kiện bàn phím
	if (events.type == SDL_KEYDOWN) //Nhấn phím xuống
	{
		switch (events.key.keysym.sym)
		{
		//----------------------------- Phím lên
		case SDLK_UP:
			y_val_ -= HEIGHT_MAIN_OBJECT/4; // Mỗi lần dịch chuyển lên 1/4 bề dài đối tượng
			break;
		//----------------------------- Phím xuống
		case SDLK_DOWN:
			y_val_ += HEIGHT_MAIN_OBJECT/4; // Mỗi lần dịch chuyển xuống 1/4 bề dài đối tượng
			break;
		//----------------------------- Phím Phải
		case SDLK_RIGHT:
			x_val_ += WIDTH_MAIN_OBJECT/4; // Mỗi lần dịch chuyển sang phải 1/4 bề rộng đối tượng
			break;
		//----------------------------- Phím Trái
		case SDLK_LEFT:
			x_val_ -= WIDTH_MAIN_OBJECT/4; // Mỗi lần dịch chuyển sang trái 1/4 bề rộng đối tượng
			break;
		//-----------------------------
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP) //Thả phím ra
	{
		// trừ/cộng lượng đã cộng/trừ khi còn nhấn phím
		switch (events.key.keysym.sym)
		{
		case SDLK_UP: y_val_ += HEIGHT_MAIN_OBJECT/4; break;
		case SDLK_DOWN: y_val_ -= HEIGHT_MAIN_OBJECT/4; break;
		case SDLK_RIGHT: x_val_ -= WIDTH_MAIN_OBJECT/4; break;
		case SDLK_LEFT: x_val_ += WIDTH_MAIN_OBJECT/4; break;
		}

	}
	//Bắt sự kiện chuột
	else if (events.type == SDL_MOUSEBUTTONDOWN) //chuột nhấn xuống
	{
		AmoObject* p_amo = new AmoObject();
		//Tạo đối tượng đạn
		if (events.button.button == SDL_BUTTON_LEFT) // Bấm chuột trái
		{
			p_amo->SetWidthHeight(WIDTH_LASER, HEIGHT_LASER);
			p_amo->LoadImg("laser.png"); //load ảnh đạn
			p_amo->set_type(AmoObject::LASER);
			Mix_PlayChannel(-1, amo_sound[0], 0);
		}
		else if (events.button.button == SDL_BUTTON_RIGHT) //bấm chuột phải
		{
			p_amo->SetWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
			p_amo->LoadImg("laser.png"); // load ảnh đạn
			//p_amo->set_type(AmoObject::SPHERE);
			p_amo->set_type(AmoObject::LASER);
			Mix_PlayChannel(-1, amo_sound[1], 0);
		}
		//vị trí đạn gán với vị trí nhân vật
		p_amo->SetRect(this->rect_.x + this->rect_.w - 5, this->rect_.y + this->rect_.h*0.4); // vị trí đạn bắn ra sát mét máy bay (rect_ tại góc trái trên)
		p_amo->set_is_move(true); //đạn đc bấm
		p_amo->set_x_val(20); // setup đạn di chuyển x_val_ đvi
		p_amo_list_.push_back(p_amo);

	}
	else if (events.type == SDL_MOUSEBUTTONUP) //Thả chuột ra
	{

	}
	else //Sự kiện khác
	{
		;
	}
}

void MainObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < p_amo_list_.size(); i++) //kiểm tra xem có đạn ko
		{
			AmoObject* p_amo = p_amo_list_.at(i); //lấy viên đạn
			if (p_amo != NULL) // có đạn
			{
				if (p_amo->get_is_move())
				{
					p_amo->Show(des); //hiển thị đạn
					p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				}
				else 
				{
					if (p_amo != NULL) //đạn chạm đến giới hạn
					{
						p_amo_list_.erase(p_amo_list_.begin() + i); // xóa khỏi vector
						delete p_amo; // xóa đối tượng đạn
						p_amo = NULL;
					}
				}
			}
		}
}

void MainObject::HandleMove() // Vị trí dịch chuyển mới
{
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) 
		//Lùi quá màn hình hoặc tiến quá (điểm rect_.x tại đỉnh trái trên đối tượng)
	{
		rect_.x -= x_val_; // trả lại x_val ko để lùi hoặc tiến ko quá biên
	}

	rect_.y += y_val_;
	if (rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100)
		//  giới hạn dưới máy bay ko cho hạ quá thấp 
	{
		rect_.y -= y_val_;	
	}
}

void MainObject::RemoveAmo(const int& idx) //xóa đạn
{
	for (int i = 0; i < p_amo_list_.size(); i++)
	{
		if (idx < p_amo_list_.size())
		{
			AmoObject* p_amo = p_amo_list_.at(idx);
			p_amo_list_.erase(p_amo_list_.begin() + idx); //xóa viên đạn thứ idx
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}		
	}
}