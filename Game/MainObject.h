#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_
//Xử lý nhân vật/ đối tượng

#include "Common_Function.h"
#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 100
#define HEIGHT_MAIN_OBJECT 100

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events, Mix_Chunk* amo_sound[2]);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void MakeAmo(SDL_Surface* des); // tạo đạn nhân vật
	void RemoveAmo(const int& idx); //xóa đạn nv

private: //Khi ko có lớp nào kế thừa lớp này
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;
};

#endif 