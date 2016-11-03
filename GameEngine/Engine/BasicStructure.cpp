#pragma once
#include <BasicStructure.h>

//事件参数类
EventArgs::EventArgs()
{

}
EventArgs::EventArgs(long x, long y, long id, long z)
{
	X = x;
	Y = y;
	Z = z;
	ButtomId = id;
}

//Size重定义
Size::Size()
{
	width = 0;
	height = 0;
}
Size::Size(long width, long height)
{
	Size::width = width;
	Size::height = height;
}
//s能包含s2
bool Size::operator>(Size s2)
{
	if (width > s2.width && height > s2.height)
	{
		return true;
	}
	return false;
}
//Point 重定义
Point::Point()
{
	X = 0;
	Y = 0;
}
Point::Point(long x, long y)
{
	X = x;
	Y = y;
}
bool Point::operator==(Point p)
{
	if (X == p.X && Y == p.Y)
	{
		return true;
	}
	return false;
}

//网格地图
GridMap::GridMap()
{
}
int GridMap::CreateGridMap(Size map)
{
	mapSize = map;
	if (map > unitGrid)
	{
		gridSize.width = map.width / unitGrid.width;
		gridSize.height = map.height / unitGrid.height;
		gridDataLen = gridSize.width*gridSize.height;
		gridData = new byte[gridDataLen];
		ZeroMemory(gridData, gridDataLen);
	}
	return 0;
}
int GridMap::GetPointValue(Point p)
{
	if (p.X < gridSize.width && p.X >= 0 && p.Y < gridSize.height && p.Y >= 0 && gridDataLen>0)
	{
		if (gridData[p.Y*gridSize.width + p.X] == 1)
		{
			return 1;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
Point GridMap::PointToGridPoint(Point p)
{
	//修正坐标
	Point newP = Point(p.X / unitGrid.width, p.Y / unitGrid.height);
	return newP;
}

//T转化为char*
template<typename T>
char* ToChar(T inVar)
{
	if (0 == strcmp("int", typeid(inVar).name()))
	{
		return IntToChar(inVar);
	}
	if (0 == strcmp("long", typeid(inVar).name()))
	{
		return LongToChar(inVar);
	}
	if (0 == strcmp("float", typeid(inVar).name()))
	{
		return FloatToChar(inVar);
	}
	if (0 == strcmp("double", typeid(inVar).name()))
	{
		return DoubleToChar(inVar);
	}
	return "undef";
}
//T转化为WCHAR*
template<typename T>
WCHAR* ToWchar(T inVar)
{
	return CharToWchar(ToChar(inVar));
}
//函数定义
WCHAR* CharToWchar(const char * str)
{
	int nlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	WCHAR * wBuf = new WCHAR[nlen];
	MultiByteToWideChar(CP_ACP, 0, str, -1, wBuf, nlen);
	return wBuf;
}
char* ConstCharToChar(const char* ccp)
{
	if (ccp)
	{
		char *buf = new char[strlen(ccp) + 1];
		strcpy_s(buf, strlen(ccp) + 1, ccp);
		return buf;
	}
	else
	{
		return NULL;
	}
}
int ByteToInt(byte* bytes, int size = 4)
{
	int addr = bytes[0] & 0xFF;
	addr |= ((bytes[1] << 8) & 0xFF00);
	addr |= ((bytes[2] << 16) & 0xFF0000);
	addr |= ((bytes[3] << 24) & 0xFF000000);
	return addr;
}
char* ByteToChar(byte* b)
{
	int i = ByteToInt(b);
	char *buf = new char[30];
	sprintf_s(buf, 30, "%d", i);
	return buf;
}
char* IntToChar(int i)
{
	char *buf = new char[30];
	sprintf_s(buf, 30, "%d", i);
	return buf;
}
char* LongToChar(long l)
{
	char *buf = new char[30];
	sprintf_s(buf, 30, "%d", l);
	return buf;
}
char* FloatToChar(float f)
{
	char *buf = new char[30];
	sprintf_s(buf, 30, "%.4f", f);
	return buf;
}
char* DoubleToChar(double d)
{
	char *buf = new char[30];
	sprintf_s(buf, 30, "%.4lf", d);
	return buf;
}
//int atoi(const char *nptr);
//long atol(const char *nptr);
//long long atoll(const char *nptr);
//long long atoq(const char *nptr);
int CharToInt(const char* s)
{
	return atoi(s);
}
char* CharAdd(char* s1, char* s2)
{
	int s1len = strlen(s1);
	int s2len = strlen(s2);
	if (s1len > 0 && s2len > 0)
	{
		char* buf = new char[s1len + s2len + 1];
		sprintf_s(buf, s1len + s2len + 1, "%s%s", s1, s2);
		return buf;
	}
	return NULL;
}

RECT* Rect(int x1, int y1, int x2, int y2)
{
	RECT* rect = new RECT();
	SetRect(rect, x1, y1, x2, y2);
	return rect;
}
RECT GetRECT(int x1, int y1, int x2, int y2)
{
	RECT rect;
	SetRect(&rect, x1, y1, x2, y2);
	return rect;
}
POINT GetPOINT(long x, long y)
{
	POINT p = { x,y };
	return p;
}
int MessageBox(char* s)
{
	MessageBox(NULL, CharToWchar(s), L"Test", NULL);
	return 1;
}
int GetPointsDirection(Point p1, Point p2)
{
	if (p2.X > p1.X && p2.Y <= p1.Y)
	{
		return 1;
	}
	if (p2.X <= p1.X && p2.Y < p1.Y)
	{
		return 2;
	}
	if (p2.X < p1.X && p2.Y >= p1.Y)
	{
		return 3;
	}
	if (p2.X >= p1.X && p2.Y > p1.Y)
	{
		return 4;
	}
}

float GetPointDis(Point p1, Point p2)
{
	return sqrtf((p2.X - p1.X)*(p2.X - p1.X) + (p2.Y - p1.Y)*(p2.Y - p1.Y));
}
/*
返回0，则bPath为路径
返回1，则不移动
返回-1,表示尝试反调（start与target交换）
P，S型，X型存在问题
*/
int FindBestPath(Point start, Point target, GridMap* gridMap, vector<Point>* path)
{
	path->clear();
	Point p = Point();
	bool flag = true;
	float disToTarget = 0.0f;
	float disToStart = 0.0f;
	if (!gridMap->GetPointValue(start))
	{
		return 1;//当前位置不合法
	}
	if (!gridMap->GetPointValue(target))
	{
		return 2;//目标位置不合法
	}
	path->push_back(start);
	while (!(target == path->back()))
	{
		p = path->back();
		disToStart = GetPointDis(p, start);
		Point p1[8];
		p1[0].X = p.X + 1;p1[0].Y = p.Y;
		p1[1].X = p.X + 1;p1[1].Y = p.Y - 1;
		p1[2].X = p.X;p1[2].Y = p.Y - 1;
		p1[3].X = p.X - 1;p1[3].Y = p.Y - 1;
		p1[4].X = p.X - 1;p1[4].Y = p.Y;
		p1[5].X = p.X - 1;p1[5].Y = p.Y + 1;
		p1[6].X = p.X;p1[6].Y = p.Y + 1;
		p1[7].X = p.X + 1;p1[7].Y = p.Y + 1;
		int index = -1;
		//disToStart= sqrtf((target.X - p.X)*(target.X - p.X) + (target.Y - p.Y)*(target.Y - p.Y));
		float dis = 0;
		float minDis = GetPointDis(start, target);
		for (int i = 0;i < 8;i++)
		{
			if (gridMap->GetPointValue(p1[i]))
			{
				dis = GetPointDis(p1[i], target);
				if (dis < minDis)
				{
					minDis = dis;
					index = i;
				}
			}
		}
		if (minDis == GetPointDis(start, target))
		{
			//说明没下一点，bug
			path->clear();
			return 3;
		}
		if (disToStart > GetPointDis(p1[index], start))
		{
			path->clear();
			return -1;//反调
		}
		path->push_back(p1[index]);
	}
	return 0;
}
bool IsPointInRECT(Point p, RECT rect)
{
	if (p.X > rect.left && p.X<rect.right && p.Y>rect.top && p.Y < rect.bottom)
	{
		return true;
	}
	return false;
}