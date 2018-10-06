#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <unordered_map>
#include <string>
#include <assert.h>

class TextureUtils
{
private:
	TextureUtils() = delete;
	~TextureUtils() = delete;

	static std::unordered_map<std::string, cv::Mat> textureCache;

public:
	static const cv::Mat LoadImageFromPath(std::string relativepath);
};

