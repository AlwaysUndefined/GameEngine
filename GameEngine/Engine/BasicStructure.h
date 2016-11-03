#pragma once
#pragma once
//��׼��
#include <vector>
#include <list>
#include <algorithm>//vc++��ѧ��
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

//�궨��
#define SAFE_RELEASE(p){if(p){(p)->Release();(p)=NULL;}}	//�ͷ�COM���õĺ�

//�ṹ����

//�¼�����
namespace GameEngine
{
	enum EventType
	{
		//�����¼�
		MouseClickEvent = 1,
		MouseDoubleClick = 2,
		MouseMoveEvent = 3,
		//��ʱ�¼�
		TimerEvent = 4,
	};
}

//�¼�������
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
//Size�ض���
class Size
{
public:
	long width;
	long height;
	Size();
	Size(long width, long height);
	//s�ܰ���s2
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
	//��λ�����С
	Size unitGrid = Size(8, 8);
	//�����С
	Size gridSize = Size(0, 0);
	long gridDataLen = 0;
	//��ʵ��ͼ��С
	Size mapSize;
	//�������ݿռ�
	byte* gridData;
	GridMap();
	int CreateGridMap(Size map);
	int GetPointValue(Point p);
	Point PointToGridPoint(Point p);
};

//Tת��Ϊchar*
template<typename T>
char* ToChar(T inVar);
//Tת��ΪWCHAR*
template<typename T>
WCHAR* ToWchar(T inVar);
//��������
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
����0����bPathΪ·��
����1�����ƶ�
����-1,��ʾ���Է�����start��target������
P��S�ͣ�X�ʹ�������
*/
int FindBestPath(Point start, Point target, GridMap* gridMap, vector<Point>* path);
bool IsPointInRECT(Point p, RECT rect);