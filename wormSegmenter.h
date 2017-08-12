#ifndef wormSegmenter_h
#define wormSegmenter_h
class wormSegmenter{

public:
	struct Arguments {
    std::string project;
    std::string input;
    std::string output;
    int padding;
    int frames;
    std::string extension;
    int width;
    int height;
    int area_min;
    int area_max;
    int search_win_size;
    int blur_radius;
    int threshold_win_size;
    float threshold_ratio;
    std::string log;
    bool verbose;
} ;
public :
	static int wormSegmenterF(int fileNumber,int x,int y);
	static int findCentroidFromImage(Arguments &cla,cv::Mat src, int *pX, int *pY, int *pArea);
	static std::string intToFileName(std::string fileNameFormat, int fileNumber);
    static std::string NumberToString(int pNumber);
};
#endif