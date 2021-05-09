#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Common_Function.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject(); //Hàm hủy mặc định
	void Show(SDL_Surface* des); //Đích cần truyền vào
	bool LoadImg(const char* file_name);

	void SetRect(const int& x,const int& y) {rect_.x = x, rect_.y = y;}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Surface* GetObject() {return p_object_;}
protected: // Dùng để có 1 lớp khác có thể kế thừa lớp baseObject này
	SDL_Rect rect_;
	SDL_Surface* p_object_;
};

#endif