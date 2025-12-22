#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include <string>

class Animation
{
	float animDelay{};
	float numFrames{};
	std::string name{ "" };
	

public: 
	Animation();
	~Animation();
};

#endif