#include "Common_Function.h"
#include "TextObject.h"

bool SDLCommonFunc::CheckfocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
	if (x >= rect.x && x <= rect.x + rect.w &&
		y >= rect.y && y <= rect.y + rect.h)
	{
		return true;
	}
	return false;
}

int SDLCommonFunc::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
	g_img_menu = LoadImage("start_img.png");
	if (g_img_menu == NULL)
	{
		return 1;
	} 

	const int kMenuItemNum = 3; //số lượng mục chọn hiện ở menu
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 45;
	pos_arr[0].y = 200;

	pos_arr[1].x = 45;
	pos_arr[1].y = 280;

	pos_arr[2].x = 45;
	pos_arr[2].y = 360;

	TextObject text_menu[kMenuItemNum];

	text_menu[0].Settext("Play Game");
	text_menu[0].SetColor(TextObject::BLACK_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].Settext("Level");
	text_menu[1].SetColor(TextObject::BLACK_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].Settext("Exit");
	text_menu[2].SetColor(TextObject::BLACK_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	bool selected[kMenuItemNum] = {0, 0};
	//tọa độ chuột
	int xm = 0; 
	int ym = 0;
	//SDL_Delay(1000);
	
	SDL_Event m_event; //sự kiện chuột di chuyển vào vùng chọn
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_img_menu, des, 0, 0);
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 1;
			case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							if (selected[i] == false)
							{
								selected[i] = 1;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else
						{
							if (selected[i] == true)
							{
								selected[i] = 0;
								text_menu[i].SetColor(TextObject::BLACK_TEXT);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 2;
				}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	
	return 2;
}

int SDLCommonFunc::ShowMenuLevel(SDL_Surface* des, TTF_Font* font)
{
	g_img_menu_level = LoadImage("bg_level.png");
	if (g_img_menu_level == NULL)
	{
		return 1;
	} 

	const int kMenuItemNum = 5; //số lượng mục chọn hiện ở menu
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 200;
	pos_arr[0].y = 150;

	pos_arr[1].x = 200;
	pos_arr[1].y = 300;

	pos_arr[2].x = 700;
	pos_arr[2].y = 150;

	pos_arr[3].x = 700;
	pos_arr[3].y = 300;

	pos_arr[4].x = 470;
	pos_arr[4].y = 500;

	TextObject text_menu[kMenuItemNum];

	text_menu[0].Settext("Level 1");
	text_menu[0].SetColor(TextObject::YELLOW_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	text_menu[1].Settext("Level 2");
	text_menu[1].SetColor(TextObject::YELLOW_TEXT);
	text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

	text_menu[2].Settext("Level 3");
	text_menu[2].SetColor(TextObject::YELLOW_TEXT);
	text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

	text_menu[3].Settext("Level 4");
	text_menu[3].SetColor(TextObject::YELLOW_TEXT);
	text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

	text_menu[4].Settext("Exit");
	text_menu[4].SetColor(TextObject::YELLOW_TEXT);
	text_menu[4].SetRect(pos_arr[4].x, pos_arr[4].y);

	bool selected[kMenuItemNum] = {0, 0};
	//tọa độ chuột
	int xm = 0; 
	int ym = 0;
	//SDL_Delay(1000);
	
	SDL_Event m_event; //sự kiện chuột di chuyển vào vùng chọn
	while (true)
	{
		SDLCommonFunc::ApplySurface(g_img_menu_level, des, 0, 0);
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 1;
			case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							if (selected[i] == false)
							{
								selected[i] = 1;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else
						{
							if (selected[i] == true)
							{
								selected[i] = 0;
								text_menu[i].SetColor(TextObject::YELLOW_TEXT);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 4;
				}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	
	return 4;
}

TTF_Font* g_font_menu_over = NULL;
TTF_Font* g_font_game_over = NULL;

int SDLCommonFunc::ShowGameOver(SDL_Surface* des, TTF_Font* font, std::string MT, std::string MT_Time, std::string MT_Mark)
{
	g_img_game_over = LoadImage("bg_level.png");
	if (g_img_game_over == NULL)
	{
		return 0;
	} 

	

	const int kMenuItemNum = 1; //số lượng mục chọn hiện ở menu
	SDL_Rect pos_arr[kMenuItemNum];
	pos_arr[0].x = 500;
	pos_arr[0].y = 400;

	TextObject time_game_over;
	TextObject mark_game_over;
	TextObject MucTieu_game_over;
	TextObject Game_Over;
	TextObject text_menu[kMenuItemNum];

	text_menu[0].Settext("Exit");
	text_menu[0].SetColor(TextObject::WHITE_TEXT);
	text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

	bool selected[kMenuItemNum] = {0};
	//tọa độ chuột
	int xm = 0; 
	int ym = 0;
	//SDL_Delay(1000);
	
	SDL_Event m_event; //sự kiện chuột di chuyển vào vùng chọn
	while (true)
	{
		/*g_font_menu_over = TTF_OpenFont("Lobster-Regular.ttf", 50);
		g_font_game_over = TTF_OpenFont("OrelegaOne-Regular.ttf", 50);
		if (g_font_menu_over == NULL || g_font_game_over == NULL)
		{
			return 0;
		}*/
		
		SDLCommonFunc::ApplySurface(g_img_game_over, des, 0, 0);

		std::string Game_Over_ = "GAME OVER";
		Game_Over.Settext(Game_Over_);
		Game_Over.SetColor(TextObject::WHITE_TEXT);
		Game_Over.SetRect(400, 40);
		Game_Over.CreateGameText(font, des);

		Game_Over.Settext("You Accomplished");
		Game_Over.SetColor(TextObject::WHITE_TEXT);
		Game_Over.SetRect(350, 150);
		Game_Over.CreateGameText(font, des);

		std::string str_MucTieu_Over = "Target ";
		str_MucTieu_Over = str_MucTieu_Over + MT + ":";
		MucTieu_game_over.Settext(str_MucTieu_Over);
		MucTieu_game_over.SetColor(TextObject::WHITE_TEXT);
		MucTieu_game_over.SetRect(100, 300);
		MucTieu_game_over.CreateGameText(font, des);
		
		std::string str_time_over = "Time: ";
		str_time_over = str_time_over + MT_Time;
		time_game_over.Settext(str_time_over);
		time_game_over.SetColor(TextObject::WHITE_TEXT);
		time_game_over.SetRect(400, 300);
		time_game_over.CreateGameText(font, des);

		std::string str_mark_over = "Mark: ";
		str_mark_over = str_mark_over + MT_Mark;
		mark_game_over.Settext(str_mark_over);
		mark_game_over.SetColor(TextObject::WHITE_TEXT);
		mark_game_over.SetRect(700, 300);
		mark_game_over.CreateGameText(font, des);

		
		for (int i = 0; i < kMenuItemNum; ++i)
		{
			text_menu[i].CreateGameText(font, des);
		}

		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT: return 1;
			case SDL_MOUSEMOTION:
				{
					xm = m_event.motion.x;
					ym = m_event.motion.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							if (selected[i] == false)
							{
								selected[i] = 1;
								text_menu[i].SetColor(TextObject::RED_TEXT);
							}
						}
						else
						{
							if (selected[i] == true)
							{
								selected[i] = 0;
								text_menu[i].SetColor(TextObject::WHITE_TEXT);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					
					for (int i = 0; i < kMenuItemNum; i++)
					{
						if (CheckfocusWithRect(xm, ym, text_menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if (m_event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 0;
				}
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	
	return 0;
}

SDL_Surface* SDLCommonFunc::LoadImage(std::string file_path) //load các ảnh
{
	SDL_Surface * load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
    {
		optimize_image= SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);

		 if (optimize_image != NULL)  // Xóa màu nền của ảnh nhân vật
		 {
			 UINT32 color_key = SDL_MapRGB(optimize_image->format, 0, 0xFF, 0xFF); // màu nền ứng với mã hex
			 SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		 }
	}
	return optimize_image;
}

SDL_Rect SDLCommonFunc::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y) //load ảnh vào screen
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	return offset;
}

void SDLCommonFunc::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2) //kiểm tra va chạm giữa 2 đối tượng
{
	  int left_a = object1.x;
	  int right_a = object1.x + object1.w - 15;
	  int top_a = object1.y;
	  int bottom_a = object1.y + object1.h;
 
	  int left_b = object2.x;
	  int right_b = object2.x + object2.w;
	  int top_b = object2.y;
	  int bottom_b = object2.y + object2.h;
 
	  // trường hợp 1: size object 1 < size object 2
	  if (left_a > left_b && left_a < right_b)
	  {
		if (top_a > top_b && top_a < bottom_b)
		{
		  return true;
		}
	  }
 
	  if (left_a > left_b && left_a < right_b)
	  {
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
		  return true;
		}
	  }
 
	  if (right_a > left_b && right_a < right_b)
	  {
		if (top_a > top_b && top_a < bottom_b)
		{
		  return true;
		}
	  }
 
	  if (right_a > left_b && right_a < right_b)
	  {
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
		  return true;
		}
	  }
  
	  // trường hợp 2: size object 1 > size object 2
	  if (left_b > left_a && left_b < right_a)
	  {
		if (top_b > top_a && top_b < bottom_a)
		{
		  return true;
		}
	  }
 
	  if (left_b > left_a && left_b < right_a)
	  {
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
		  return true;
		}
	  }
 
	  if (right_b > left_a && right_b < right_a)
	  {
		if (top_b > top_a && top_b < bottom_a)
		{
		  return true;
		}
	  }
 
	  if (right_b > left_a && right_b < right_a)
	  {
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
		  return true;
		}
	  }
 
	   // trường hợp 3: size object 1 = size object 2
	  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	  {
		return true;
	  }
 
	  return false;
}

void SDLCommonFunc::CleanUp() // Giải phóng các biến 
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}