#ifndef UTILITY_H
#define UTILITY_H

#include "../image/image.h"
#include "../roi/roi.h"
#include <sstream>

class utility
{
	public:	
		utility();
		virtual ~utility();
		static std::string intToString(int number);
		static bool isVideo(char fName[]);
		static bool isImage(char fName[]);
};

#endif

