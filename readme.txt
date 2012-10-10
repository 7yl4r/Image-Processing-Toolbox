### Software Demo ###
To demonstrate the software capabilities run the included script iptoolsdemo.sh from a terminal in the 'project' directory. Images in the images_for_demo directory will be used and results will be saved to the 'project' directory.



### Additional Notes to the TA regarding dependencies ###
In place of ffmpeg, avconv was used, since ffmpeg was breaking my software and displaying a 'software depreciated' message suggesting the use of avconv.


### Software architecture ###
iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	video- This folder hosts the files that define an video.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.
	
** To compile this software enter the project directory and run make **



### ROI Files ###
Region of Intrest (ROI) must be specified in 1 of 3 ways. 

The ROI may be specified directly by providing the leftX, upperY, xSize, and ySize directly.
example:
"	iptool <inputFile> <outputFile> <X1> <Y1> <sX> <sY> <functionName> <func-params...>"

The ROI may be specified as the entire image by using 'ALL' as the roi argument.
"	iptool <inputFile> <outputFile> ALL <functionName> <func-params...>"

Otherwise, the program assumes that the ROI given is in the form of an ROI file. The first line of the ROI file is the number of regions specified. Each following line of the ROI file describes one ROI in this manner:
<leftX> <upperY> <xSize> <ySize>

The ROI file may contain any number of regions.

Example:
3
20 30 100 100
100 10 20 100
200 120 1 3



### FOI FILES ###
These files are nearly identical to the ROI file specified above, except that the file must include the start frame and size of frames window to describe the subsequence of interest for the processing of video files.
 
The first line of the ROI file is the number of regions specified.

Each following line of the ROI file describes one ROI in this manner:
<centerX> <centerY> <xSize> <ySize> <startFrame> <numberOfFrames>

The FOI file may contain any number of regions.



### scripting ###
A simple bash script is the simplest way of allowing for the quick processing of multiple images. An example bash script is provided which demonstrates the capabilities of this software.



### USAGE ###
All functions can be executed by running the iptool binary from the command line using a script or by specifying all parameters in the command line. 

To execute one operation, all arguments can be passed to iptool via the command line. To do this, the ROI must be given in the form of a ROI file, the command "ALL" to process the whole image, or the x,y co-ords of the upper left pixel and the x,y size of the region. Following the ROI information, the function must be specified by name, followed by all arguments required by the function. In general, these commands are of the form:
	"iptool <inputFile> <outputFile> <ROIfile||ALL||<X1> <Y1> <sX> <sY>> <functionName> <func-params...>"

 Since the syntax varies for each function; a guide to all available functions is below:

****** Add ******
"add": This simple add increases the value of pixels in the ROI by the specified amount.

usage:
	<srcfile> <target file> <ROI> add <threshold>
example:
	inFile.pgm outFile.pgm ROI.txt add 183

****** Gray Threshold/Binarize ******
"GrayThresh" applies simple thresholding on a grayscale image (pgm), comparing the pixel value to the specified threshold.

alternate names: 
	"Binarize", "GreyThresh"
usage:
	<srcfile> <target file> <ROI> GrayThresh <threshold>
example:
	inFile.pgm outFile.pgm ROI.txt greyThresh 183

****** Color Thresholding ******
"ColorThresh" : applies thresholding of color images by comparing all color values to given color in 3D color space.

usage:
	<srcfile> <target file> <ROI file> ColorThresh <threshold> <Red> <Green> <Blue> 

example:
	infile.ppm outfile.ppm roi.txt colorthresh 50 123 9 40

****** Adaptive Thresholding ******
"AdaptiveThresh" : This function computes the mean of window of specified (odd) size and highlights pixels which are a given amount above that mean.

alternate names: "weightedThresh"

usage:
	<srcfile> <target file> <ROI> WeightedThresh <winsize> <thresh above mean>

example:
	<infile.pgm outfile.pgm roi.txt weightedthresh 5 50 

****** Scale *******
"scale": this allows for the image to be increased or decreased in size by a factor of 2 or 4. The sizing parameter is specified as a percent of the original size, thus acceptable values are: 25, 50, 200, 400.

For this function the ROI must be specified, but it unused. It is most coherent in this case to specify the entire image as the ROI using 'ALL'.

usage:
	<srcfile> <target file> ALL scale <%of original>
		
example:
	infile.pgm outfile.pgm ALL scale 200

****** Smoothing *******
"Smooth2D" and "smooth1d" both have the same output, but are implemented differently. Smooth2D computes an average over a 2D window of specified size as would be expected. However, this function is mathmatically separable, allowing us to compute the result more efficiently by computing an average in one direction and then the other. This is the method used by 'smooth1d', reducing the complexity from n^2 to 2n.

usage:
	<srcfile> <target file>	<ROI> smooth1d <winsize>
	-OR-
	<srcfile> <target file> <ROI> smooth2d <winsize>

example:
	infile.pgm outfile.pgm roi.txt smooth1d 5

