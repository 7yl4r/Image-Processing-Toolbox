#include "utility.h"

//int->string
std::string utility::intToString(int number){
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

//checks file name for common image extensions, returns true if recognized format
bool utility::isImage(char fName[]){
	//note: pgm && ppm excluded from this list
	static int nExten = 11;	//number of extensions
	char extensions[11][10] = {".jpeg","jpg",".jfif",".exif",".tiff",".raw",".gif",".bmp",".png",".pbm",".pnm"};
	for(int i = 0; i < nExten ; i++){
		if(strstr(fName,extensions[i])!='\0') return 1;
	} //if none found
	return 0;
}

//checks file name for common video file extensions, returns true if recognized format
bool utility::isVideo(char fName[]){
	static int nExten = 12;	//number of extensions
	char extensions[12][10] = {".flv",".avi",".mov",".mp4",".mpg",".mpeg",".wmv",".3gp",".asf",".rm",".swf","m1v"};
	for(int i = 0; i < nExten ; i++){
		if(strstr(fName,extensions[i])!='\0') return 1;
	} //if none found
	return 0;
}
