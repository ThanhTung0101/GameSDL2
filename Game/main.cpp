#include "Common_Function.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "PlayerPower.h"
#include "TextObject.h"
#include <string>


TTF_Font* g_font_text = NULL;
TTF_Font* g_font_menu = NULL;

bool Init() //Khởi tạo các thuộc tính ban đầu
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen == NULL)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("ACaslonPro.ttf", 20); //kích thước 20
	g_font_menu = TTF_OpenFont("Lobster-Regular.ttf", 50);
	if (g_font_text == NULL || g_font_menu == NULL)
	{
		return false;
	}

	//âm thanh
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;
	//đọc file âm thanh
	g_sound_amo[0] = Mix_LoadWAV("audio_amo.wav");
	g_sound_amo[1] = Mix_LoadWAV("audio_amo.wav");
	g_sound_exp[0] = Mix_LoadWAV("audio_corona_die.wav"); //địch die
	g_sound_exp[1] = Mix_LoadWAV("Ho.wav"); //nv die
	music_die = Mix_LoadWAV("game_over.wav");

	if (music_die == NULL || g_sound_exp[0] == NULL || g_sound_exp[1] == NULL || g_sound_amo[0] == NULL || g_sound_amo[1] == NULL)
	{
		return false;
	}

	return true;
}

unsigned int muc_tieu = 1;
unsigned int time_key = 40;
unsigned int mark_key = 50;
unsigned int plus_time_key = 2;
unsigned int plus_mark_key = 2;
unsigned int plus_time_key_nhan = 2;
unsigned int plus_mark_key_nhan = 2;
TextObject time_game_key;
TextObject mark_game_key;
TextObject MucTieu_game;
ThreatObject* p_threats;
int  NUM_THREAT;

int Level(int Num_threat, std::string name_threat, int muc_tieu_, int time_key_, 
		  int mark_key_, int plus_time_key_, int plus_mark_key_, int plus_time_key_nhan_, int plus_mark_key_nhan_)
{
	NUM_THREAT = Num_threat; //số lượng kẻ địch

	//tạo kẻ địch
	p_threats = new ThreatObject[NUM_THREAT];
	bool ret;
	for (int t = 0; t < NUM_THREAT; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if (p_threat) //kiểm tra khác NULL
		{
			ret = p_threat->LoadImg(name_threat.c_str());
			if (ret == false)
			{
				return 0;
			}
			//tạo vị trí xuất hiện lần đầu random
			int rand_y = rand()%400;
			if (rand_y > SCREEN_HEIGHT - 200)
			{
				rand_y = SCREEN_HEIGHT *0.3;
			}
			p_threat->SetRect(SCREEN_WIDTH + t*400, rand_y); //time xuất hiện kẻ địch khác thời điểm
			p_threat->set_x_val(3); //tốc độ địch di chuyển

			AmoObject* p_amo = new AmoObject();
			p_threat->InitAmo(p_amo);
		}
		
	}
	//------------------------------------------------------------------------------------
	//Mục tiêu
	muc_tieu = muc_tieu_;
	time_key = time_key_;
	mark_key = mark_key_;
	plus_time_key = plus_time_key_;
	plus_mark_key = plus_mark_key_;
	time_game_key.SetColor(TextObject::WHITE_TEXT);
	mark_game_key.SetColor(TextObject::WHITE_TEXT);
	MucTieu_game.SetColor(TextObject::WHITE_TEXT);
	plus_time_key_nhan = plus_time_key_nhan_;
	plus_mark_key_nhan = plus_mark_key_nhan_;
}

int main(int arc, char*argv[])
{
	bool is_run_screen = true; //kiểm tra chạy màn hình
	int bkg_x = 0;
	bool is_quit = false;
	if (Init() == false) return 0;
	//-------------------------------------------------------------------------

	g_bkground = SDLCommonFunc::LoadImage("bg8000.png");
	//g_bkground = SDLCommonFunc::LoadImage("Menu.png");
	if (g_bkground == NULL)
	{
		return 0;
	}
	//-------------------------------------------------------------------------

	//tạo trái tim mạng
	PlayerPower player_power;
	player_power.Init();

	//time
	TextObject time_game;
	time_game.SetColor(TextObject::RED_TEXT);

	//điểm số
	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	//------------------------------------------------------------------------

	// Tạo nhân vật
	MainObject human_object; //nhân vật
	human_object.SetRect(100, 200); // vị trí xuất hiện
	bool ret = human_object.LoadImg("doctor1.png");
	if (!ret) 
	{
		return 0;
	}
	//-------------------------------------------------------------------------

	//tạo vụ va chạm
	ExplosionObject exp_main; // nhân vật die
	ExplosionObject exp_threat; //địch die
	ret = exp_main.LoadImg("doctor_die.png"); 
	ret = exp_threat.LoadImg("corona_die.png");
	exp_main.set_clip();
	exp_threat.set_clip();
	if (ret == false) return 0; 
	//---------------------------------------------------------------------------

	unsigned int die_number = 0; //quản lý mạng sống
	unsigned int mark_value = 0; //điểm

	//------------------------------------------------------------------------------------
	
	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_menu);
	if (ret_menu == 0) {int check_level = Level(3,"corona1.png",1,30,40,2,2,6,9); is_quit = false;}
	if (ret_menu == 2) is_quit = true;
	if (ret_menu == 1) 
	{
		int ret_menu_level = SDLCommonFunc::ShowMenuLevel(g_screen, g_font_menu);
		int check_level;
		if (ret_menu_level == 4) is_quit = true; 
		else if (ret_menu_level == 0) {check_level = Level(3,"corona1.png",1,30,40,2,2,6,9); is_quit = false;}  //level 1
		else if (ret_menu_level == 1) {check_level = Level(4,"corona2.png",1,30,45,2,2,5,10); is_quit = false;} //level 2
		else if (ret_menu_level == 2) {check_level = Level(6,"corona3.png",1,30,60,3,3,4,12); is_quit = false;} //level 3
		else if (ret_menu_level == 3) {check_level = Level(7,"corona4.png",1,30,70,3,3,4,13); is_quit = false;} //level 4
		if (check_level == 0) return 0;
	}

	//------------------------------------------------------------------------------------
	int time_never_die = 0;
	int muc_tieu_over = 0;
	int time_key_over = 0;
	int mark_key_over = 0;

	while (!is_quit) 
	{
		//Mix_PlayChannel(-1, music_die, 0); //nhạc nền
		while (SDL_PollEvent(&g_even)) 
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			human_object.HandleInputAction(g_even, g_sound_amo);
		}
		
		//Tạo background dịch chuyển sử dụng 1 ảnh ngắn
		/*bkg_x -= 2; // dịch chuyển màn hình 
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x, 0); // vẽ lại màn hình
		SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x + SCREEN_WIDTH, 0); // nạp lại ảnh
		if (bkg_x <= -SCREEN_WIDTH)
		{
			bkg_x = 0;
		}*/

		if (is_run_screen == true)
		{
			bkg_x -= 2;
			if (bkg_x <= -(WIDTH_BACKGROUND - SCREEN_WIDTH)) //giữ lại màn hình cuối
			{
				is_run_screen = true; bkg_x = 0;
			} else SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x, 0);
		} 
		else
		{
			SDLCommonFunc::ApplySurface(g_bkground, g_screen, bkg_x, 0);
		}
		//=======================================================================================

		//hiển thị trái tim mạng
		player_power.Render(g_screen);

		//tạo nhân vật
		human_object.HandleMove(); // cập nhật vị trí điều khiển
		human_object.Show(g_screen); // hiển thị vị trí mới của đối tượng
		human_object.MakeAmo(g_screen); //tạo đạn
		//========================================================================================

		//hiển thị time
		std::string str_time = "Time: ";
		Uint32 time_val = SDL_GetTicks()/1000; //hàm lấy time
		std::string str_val = std::to_string(time_val);
		str_time += str_val;

		time_game.Settext(str_time);
		time_game.SetRect(SCREEN_WIDTH - 200, 10);
		time_game.CreateGameText(g_font_text, g_screen);

		//----------------------------------------------------------------
		std::string str_MucTieu = "Target ";
		std::string str_MucTieu_ = std::to_string(muc_tieu);
		str_MucTieu += str_MucTieu_ + ":";

		MucTieu_game.Settext(str_MucTieu);
		MucTieu_game.SetRect(25, 40);
		MucTieu_game.CreateGameText(g_font_text, g_screen);
		//-----------------------------------------------------------------
		std::string str_time_key = "Time: ";
		std::string str_time_key_ = std::to_string(time_key);
		str_time_key += str_time_key_ + " |";

		time_game_key.Settext(str_time_key);
		time_game_key.SetRect(110, 40);
		time_game_key.CreateGameText(g_font_text, g_screen);
		//-----------------------------------------------------------------
		std::string str_mark_key = "Mark: ";
		std::string str_mark_key_ = std::to_string(mark_key);
		str_mark_key += str_mark_key_;

		mark_game_key.Settext(str_mark_key);
		mark_game_key.SetRect(210, 40);
		mark_game_key.CreateGameText(g_font_text, g_screen);
		//------------------------------------------------------------------

		
		//Run kẻ địch
		for (int tt = 0; tt < NUM_THREAT; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if (p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);
				p_threat->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				//Cập nhật màn hình
				if ( SDL_Flip(g_screen) == -1)
				return 0;

				//kiểm tra va chạm giữa nv và địch
				bool is_col = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_threat->GetRect());
				if (is_col)
				{
					if (time_never_die != 0 && time_never_die + 3 >= time_val); else //Bất tử sau khi chết 3s
					{
						//vụ nổ trước khi kết thúc
						for (int ex = 0; ex < 4; ex++)
						{
							//vị trí vụ nổ
							int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH*0.5; 
							int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

							exp_main.set_frame(ex);
							exp_main.SetRect(x_pos, y_pos);
							exp_main.ShowEx(g_screen);
							SDL_Delay(100);
							//Cập nhật màn hình
							if ( SDL_Flip(g_screen) == -1)
							return 0;
						}

						//âm thanh nv die
						Mix_PlayChannel(-1, g_sound_exp[1], 0);

					

						die_number++;
						time_never_die = time_val;
						if (die_number <= 2)
						{
							SDL_Delay(1000);
							human_object.SetRect(100, 200); //về vị trí ban đầu
							player_power.Decrease(); //bớt 1 mạng
							player_power.Render(g_screen); //vẽ lại tim
							if (SDL_Flip(g_screen) == -1)
							{
								delete [] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 0;
							}
						} 
						else
						{
							Mix_PlayChannel(-1, music_die, 0);
							int ret_menu_over = SDLCommonFunc::ShowGameOver(g_screen, g_font_menu, std::to_string(muc_tieu_over), std::to_string(time_key_over), std::to_string(mark_key_over));
							if (ret_menu_over == 0) return 1;
							//va chạm
							if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK) == IDOK) //hiện hộp thông báo
							{
								delete [] p_threats; // xóa trong ThreatsObject
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return 1;
							}
						}
					}
				}
				//kiểm tra va chạm giữa đạn nv và địch
				std::vector<AmoObject*> amo_list = human_object.GetAmoList();
				for (int im = 0; im < amo_list.size(); im++)
				{
					AmoObject* p_amo = amo_list.at(im);
					if (p_amo != NULL)
					{
						bool ret_col = SDLCommonFunc::CheckCollision(p_amo->GetRect(), p_threat->GetRect());
						if (ret_col)
						{
							mark_value ++; //điểm
							//vụ nổ trước khi kết thúc
							for (int ex_amo = 0; ex_amo < 4; ex_amo++)
							{
								//vị trí vụ nổ
								int x_pos = (p_threat->GetRect().x + p_threat->GetRect().w*0.5) - EXP_WIDTH*0.5; 
								int y_pos = (p_threat->GetRect().y + p_threat->GetRect().h*0.5) - EXP_HEIGHT*0.5;

								exp_threat.set_frame(ex_amo);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.ShowEx(g_screen);
								//SDL_Delay(10);

								//Cập nhật màn hình
								if ( SDL_Flip(g_screen) == -1)
								return 0;
							}

							//va chạm
							p_threat->Reset(SCREEN_WIDTH + tt*400); //địch quay về vị trí ban đầu sau va chạm
							human_object.RemoveAmo(im); //xóa đạn của nv khi va chạm
							Mix_PlayChannel(-1, g_sound_exp[0], 0);
						}
					}
				}

				// kiểm tra va chạm giữa nv và đạn địch
				std::vector<AmoObject*> threats_amo_list = p_threat->GetAmoList();
				for (int imp = 0; imp < threats_amo_list.size(); imp++)
				{
					AmoObject* p_amo = threats_amo_list.at(imp);
					if (p_amo != NULL)
					{
						bool threats_ret_col = SDLCommonFunc::CheckCollision(human_object.GetRect(), p_amo->GetRect());
						if (threats_ret_col)
						{
							if (time_never_die != 0 && time_never_die + 3 >= time_val); else
							{
								//vụ nổ trước khi kết thúc
								for (int ex = 0; ex < 4; ex++)
								{
									//vị trí vụ nổ
									int x_pos = (human_object.GetRect().x + human_object.GetRect().w*0.5) - EXP_WIDTH*0.5; 
									int y_pos = (human_object.GetRect().y + human_object.GetRect().h*0.5) - EXP_HEIGHT*0.5;

									exp_main.set_frame(ex);
									exp_main.SetRect(x_pos, y_pos);
									exp_main.ShowEx(g_screen);
									SDL_Delay(100);
									//Cập nhật màn hình
									if ( SDL_Flip(g_screen) == -1)
									return 0;
								}

								//âm thanh nv die
								Mix_PlayChannel(-1, g_sound_exp[1], 0);

							
								 
								die_number++; 
								time_never_die = time_val;
								//time_never_die_key = time_val;
								if (die_number <= 2)
								{
									SDL_Delay(1000);
									human_object.SetRect(100, 200); //về vị trí ban đầu
									player_power.Decrease(); //bớt 1 mạng
									player_power.Render(g_screen); //vẽ lại tim
									if (SDL_Flip(g_screen) == -1)
									{
										delete [] p_threats;
										SDLCommonFunc::CleanUp();
										SDL_Quit();
										return 0;
									}
								} 
								else
								{
									Mix_PlayChannel(-1, music_die, 0);
									int ret_menu_over = SDLCommonFunc::ShowGameOver(g_screen, g_font_menu, std::to_string(muc_tieu_over), std::to_string(time_key_over), std::to_string(mark_key_over));
							if (ret_menu_over == 0) return 1;
									//va chạm
									if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK) == IDOK) //hiện hộp thông báo
									{
										delete [] p_threats; // xóa trong ThreatsObject
										SDLCommonFunc::CleanUp();
										SDL_Quit();
										return 1;
									}
								}
							}
						}
					}
				}
			}
		}

		

		//Hiển thị mục tiêu

		if (time_val == time_key)
		{
			if (mark_value < mark_key) 
			{
				Mix_PlayChannel(-1, music_die, 0);
				int ret_menu_over = SDLCommonFunc::ShowGameOver(g_screen, g_font_menu, std::to_string(muc_tieu_over), std::to_string(time_key_over), std::to_string(mark_key_over));
				if (ret_menu_over == 0) return 1;
				if (MessageBox(NULL, L"Sorry, You have not yet reached the target!", L"Info", MB_OK) == IDOK) //hiện hộp thông báo
				{
					SDLCommonFunc::CleanUp();
					SDL_Quit();
					return 1;
				}
			}
			muc_tieu_over = muc_tieu;
			time_key_over = time_key;
			mark_key_over = mark_key;
			muc_tieu++;
			time_key += plus_time_key * plus_time_key_nhan;
			mark_key += plus_mark_key * plus_mark_key_nhan;
			plus_mark_key++; plus_time_key++;
		}
		
		
		//hiển thị điểm
		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.Settext(strMark);
		mark_game.CreateGameText(g_font_text, g_screen);

		//Cập nhật màn hình
		if (SDL_Flip(g_screen) == -1)
		{
			delete [] p_threats; // xóa trong ThreatsObject
			SDLCommonFunc::CleanUp();
			SDL_Quit();
			return 0;
		}
	}

	delete [] p_threats; // xóa trong ThreatsObject

	SDLCommonFunc::CleanUp();
	SDL_Quit();
	return 1;
}