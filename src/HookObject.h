#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
class GoldenManEngine;
class HookObject :
	public DisplayableObject
{
public:
	void Draw();
	void DoUpdate(int iCurrentTime);
	HookObject(GoldenManEngine* pEngine, int loc_x, int loc_y);
	~HookObject();
	int angle;
	int move_direc;
	int hook_len1;
	int hook_len2;
	int mode;
	int root_x;
	int root_y;
	float rota_length;
	float hook_left_sx;
	float hook_left_sy;
	float hook_right_sx;
	float hook_right_sy;
	int drop_angle;
	void HookDraw(int t_angle);
	void getGold();
	int getAngle();
	int x_ini_speed;
	int y_ini_speed;
	int x_speed;
	int y_speed;
	void Rotation();
	void Drop();
	void HookBack(int condition);
	GoldenManEngine* m_pMainEngine;
	int mloc_x;
	int mloc_y;
	int time;
	int t_value;
	int explode;
	static int load;
	int explode_x;
	int explode_y;
private: ImageData rotation;
		 ImageData up;
		 ImageData down;

};

