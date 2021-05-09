#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H
// các biến hàm chung toàn cục
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


const int WIDTH_BACKGROUND = 8000;
const int HEIGHT_BACKGROUND = 600;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//static -> tạo biến tĩnh dùng cho toàn bộ project
static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_img_menu = NULL;
static SDL_Surface* g_img_menu_level = NULL;
static SDL_Surface* g_img_game_over = NULL;
static SDL_Event g_even;

//biến quản lý âm thanh
static Mix_Chunk* g_sound_amo[2];
static Mix_Chunk* g_sound_exp[2];
static Mix_Chunk* music_die;

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	int ShowMenuLevel(SDL_Surface* des, TTF_Font* font);
	int ShowGameOver(SDL_Surface* des, TTF_Font* font, std::string MT, std::string MT_Time, std::string MT_Mark);
	bool CheckfocusWithRect(const int& x, const int& y, const SDL_Rect& rect);
}

#endif