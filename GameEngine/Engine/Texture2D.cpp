#pragma once
#include <Texture2D.h>
namespace GameEngine
{
	//2D��ͼ
	Texture2D::Texture2D()
	{
		D3DXMatrixTransformation2D(&matx2D, NULL, 0.0f, NULL, NULL, 0.0f, NULL);
	}
	void Texture2D::Transform(D3DXVECTOR2* scaling, D3DXVECTOR2* rotationCenter, float rotation, D3DXVECTOR2* translation = new D3DXVECTOR2(0, 0))
	{
		//�õ���������ת������
		D3DXMatrixTransformation2D(&matx2D,
			NULL,//���������������������ΪNULL��Msc ����Ϊ��λ����
			0.0f, //ָ������ϵ����
			scaling, //�����������������ΪNULL��Ms����Ϊ��λ����
			rotationCenter, //��ת�������������ΪNULL��Mrc����Ϊ��λ����
			rotation, //��ת�Ƕ�
			translation);//ƽ���������������ΪNULL��Mt����Ϊ��λ����
	}
	Texture2D::~Texture2D()
	{
	}
}
