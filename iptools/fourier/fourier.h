#ifndef FOURIER_H
#define FOURIER_H

#include "../image/image.h"
#include "../roi/roi.h"
#include "../add/add.h"
#include <rfftw.h>

//global varialbles;
#define WIDTH  256
#define HEIGHT 256

#define MAXLEN 256

class fourier{
	public:	
		fourier();
		virtual ~fourier();
		static void filter();

};

#endif

