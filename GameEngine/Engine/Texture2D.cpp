#pragma once
#include <Texture2D.h>
namespace GameEngine
{
	//2D贴图
	Texture2D::Texture2D()
	{
		D3DXMatrixTransformation2D(&matx2D, NULL, 0.0f, NULL, NULL, 0.0f, NULL);
	}
	void Texture2D::Transform(D3DXVECTOR2* scaling, D3DXVECTOR2* rotationCenter, float rotation, D3DXVECTOR2* translation = new D3DXVECTOR2(0, 0))
	{
		//得到２Ｄ坐标转换矩阵
		D3DXMatrixTransformation2D(&matx2D,
			NULL,//缩放中心向量。如果参数为NULL，Msc 矩阵为单位矩阵
			0.0f, //指向缩放系数。
			scaling, //缩放向量。如果参数为NULL，Ms矩阵为单位矩阵。
			rotationCenter, //旋转向量。如果参数为NULL，Mrc矩阵为单位矩阵。
			rotation, //旋转角度
			translation);//平移向量。如果参数为NULL，Mt矩阵为单位矩阵。
	}
	Texture2D::~Texture2D()
	{
	}
}
