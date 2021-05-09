#ifndef PLAYER_POWER_H_
#define PLAY_POWER_H_
#include "BaseObject.h"
#include <vector>

class PlayerPower : public BaseObject
{
public:
	PlayerPower();
	~PlayerPower();
	void SetNumber(const int& num) {number_ = num;}
	void AddPos(const int& xpos);
	void Render(SDL_Surface* des); //hiển thị 3 trái tim
	void Init(); //khởi tạo ban đầu
	void Decrease(); //giảm mạng


private:
	int number_; //số mạng nv
	std::vector <int> pos_list_; //vị trí các hình trái tim


};


#endif