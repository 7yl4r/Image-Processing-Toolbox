#include "fourier.h"

/*-----------------------------------------------------------------------**/
void fourier::filter(){

    	char srcname[MAXLEN];
	char tgtname[MAXLEN];
	int threshhold;
	image src;
	image tgt;
	strcpy(srcname,"test.pgm");
	strcpy(tgtname,"testout.pgm");
	src.read(srcname);
	tgt.resize(src);

	int M=src.getNumberOfRows();
	int N=src.getNumberOfColumns();

	fftw_real a[M][2*(N/2+1)], b[M][2*(N/2+1)], c[M][N];
	fftw_complex *A, *B, C[M][N/2+1],D[M][N];
	rfftwnd_plan p, pinv;
	fftw_real scale = 1.0 / (M * N);
	int i, j;
	// create plan for FFT; 
	p    = rfftw2d_create_plan(M, N, FFTW_REAL_TO_COMPLEX,
							FFTW_ESTIMATE | FFTW_IN_PLACE);
	// create plan for IFFT; 
	pinv = rfftw2d_create_plan(M, N, FFTW_COMPLEX_TO_REAL,
							FFTW_ESTIMATE);

    // aliases for accessing complex transform outputs:
    	A = (fftw_complex*) &a[0][0];
	B = (fftw_complex*) &b[0][0];


}
