#include "TextureUtils.h"

std::unordered_map<std::string, cv::Mat> TextureUtils::textureCache;

const cv::Mat TextureUtils::LoadImageFromPath(std::string relativepath) {
	std::cout << "Loading image from: " << relativepath << std::endl;
	cv::Mat imageData = cv::imread(relativepath , CV_LOAD_IMAGE_UNCHANGED);
	TextureUtils::textureCache.insert({ relativepath, imageData });
	return imageData;
}
