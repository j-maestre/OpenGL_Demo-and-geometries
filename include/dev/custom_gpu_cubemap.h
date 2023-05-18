#ifndef __CUSTOM_GPU_CUBE_MAP_H__
#define __CUSTOM_GPU_CUBE_MAP_H__ 1

#include <vector>
#include <string>

#include "EDK3/referenced.h"

class CustomGPUCubeMap : public EDK3::Referenced
{
public:
	CustomGPUCubeMap();

	~CustomGPUCubeMap();

	void init(std::vector<std::string> text);
	void bind(unsigned int textUnit) const;

private:
	unsigned int id_;
	int w_;
	int h_;
	int n_;
};

#endif //__CUSTOM_GPU_CUBE_MAP_H__