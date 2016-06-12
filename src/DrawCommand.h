#pragma once

class DrawCommand
{
	
public:
	DrawCommand(Render::Texture* a_tex, float a_size, float a_angle, FPoint a_position) : tex(a_tex), size(a_size), angle(a_angle), position(a_position){}
	float size;
	float angle;
	Render::Texture* tex;
	FPoint position;
};