#pragma once
#pragma once
//标准库
#include <vector>
#include <list>
#include <algorithm>//vc++数学库
#include <string>
#include <tchar.h>
#include <stdlib.h>

//JSON
#include <rapidjson\document.h>
#include <rapidjson\stringbuffer.h>
#include <rapidjson\writer.h>

//xml
#include <TinyXml\tinyxml2.h>

//DX
#include <d3d9.h>
#include <d3dx9tex.h>
#include <dinput.h>

using namespace std;
using namespace rapidjson;//rapidjson API
using namespace tinyxml2;//tinyXml API

//宏定义
#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}	//释放COM引用的宏

//结构定义

//事件类型
namespace GameEngine
{
	enum EventType
	{
		//输入事件
		MouseClickEvent = 1,
		MouseDoubleClick = 2,
		MouseMoveEvent = 3,
		//定时事件
		TimerEvent = 4,
	};
}

//事件参数类
class EventArgs
{
public:
	long X = 0;
	long Y = 0;
	long Z = 0;
	long ButtomId = 0;
	EventArgs();
	EventArgs(long x, long y, long id, long z=0);
private:
};
//Size重定义
class Size
{
public:
	long width;
	long height;
	Size();
	Size(long width, long height);
	//s能包含s2
	bool operator>(Size s2);
};

class Point
{
public:
	long X;
	long Y;
	Point();
	Point(long x, long y);
	bool operator==(Point p);
private:
};
class GridMap
{
public:
	//单位网格大小
	Size unitGrid = Size(8, 8);
	//网格大小
	Size gridSize = Size(0, 0);
	long gridDataLen = 0;
	//真实地图大小
	Size mapSize;
	//网格数据空间
	byte* gridData;
	GridMap();
	int CreateGridMap(Size map);
	int GetPointValue(Point p);
	Point PointToGridPoint(Point p);
};

//T转化为char*
template<typename T>
char* ToChar(T inVar);
//T转化为WCHAR*
template<typename T>
WCHAR* ToWchar(T inVar);
//函数定义
WCHAR* CharToWchar(const char * str);
char* ConstCharToChar(const char* ccp);
int ByteToInt(byte* bytes, int size);
char* ByteToChar(byte* b);
char* IntToChar(int i);
char* LongToChar(long l);
char* FloatToChar(float f);
char* DoubleToChar(double d);
//int atoi(const char *nptr);
//long atol(const char *nptr);
//long long atoll(const char *nptr);
//long long atoq(const char *nptr);
int CharToInt(const char* s);
char* CharAdd(char* s1, char* s2);

RECT* Rect(int x1, int y1, int x2, int y2);
RECT GetRECT(int x1, int y1, int x2, int y2);
POINT GetPOINT(long x, long y);
int MessageBox(char* s);
int GetPointsDirection(Point p1, Point p2);

float GetPointDis(Point p1, Point p2);
/*
返回0，则bPath为路径
返回1，则不移动
返回-1,表示尝试反调（start与target交换）
P，S型，X型存在问题
*/
int FindBestPath(Point start, Point target, GridMap* gridMap, vector<Point>* path);
bool IsPointInRECT(Point p, RECT rect);