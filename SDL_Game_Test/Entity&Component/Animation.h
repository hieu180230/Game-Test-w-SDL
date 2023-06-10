#pragma once

/*this file is to make things animate
it takes index row from the character file and times the size of the character
frames determines how many frames does the animation need to work and times the size of the character
and the speed is to control the speed of the animation*/
struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {};
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}


};