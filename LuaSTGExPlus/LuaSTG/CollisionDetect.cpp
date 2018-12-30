#include "CollisionDetect.h"

using namespace std;
using namespace LuaSTGPlus;

bool LuaSTGPlus::OBBHitTest(fcyVec2 P1, fcyVec2 Size1, float Angle1,
							fcyVec2 P2, fcyVec2 Size2, float Angle2)
{
	// ��������ε�4������
	fcyVec2 tFinalPos[2][4] =
	{
		{
			fcyVec2(-Size1.x, -Size1.y),
			fcyVec2(Size1.x, -Size1.y),
			fcyVec2(Size1.x, Size1.y),
			fcyVec2(-Size1.x, Size1.y)
		},
		{
			fcyVec2(-Size2.x, -Size2.y),
			fcyVec2(Size2.x, -Size2.y),
			fcyVec2(Size2.x, Size2.y),
			fcyVec2(-Size2.x, Size2.y)
		}
	};

	float tSin, tCos;
	{
		/*
		tSin = sin(Angle1);
		tCos = cos(Angle1);
		*/
		SinCos(Angle1, tSin, tCos);

		for (int i = 0; i<4; i++)
		{
			tFinalPos[0][i].RotationSC(tSin, tCos);
			tFinalPos[0][i] += P1;
		}
	}
	{
		/*
		tSin = sin(Angle2);
		tCos = cos(Angle2);
		*/
		SinCos(Angle2, tSin, tCos);

		for (int i = 0; i<4; i++)
		{
			tFinalPos[1][i].RotationSC(tSin, tCos);
			tFinalPos[1][i] += P2;
		}
	}

	// �����������ε�������
	for (int i = 0; i<2; i++)
	{
		fcyVec2 tAxis[2] =
		{
			tFinalPos[i][1] - tFinalPos[i][0],
			tFinalPos[i][2] - tFinalPos[i][1]
		};

		// ��λ������
		tAxis[0].Normalize();
		tAxis[1].Normalize();

		// ���ͶӰ�߶�
		fcyVec2 tAxisLine[2] =
		{
			fcyVec2(tFinalPos[i][0] * tAxis[0], tFinalPos[i][1] * tAxis[0]),
			fcyVec2(tFinalPos[i][1] * tAxis[1], tFinalPos[i][2] * tAxis[1])
		};

		// ��ÿһ������
		for (int j = 0; j<2; j++)
		{
			// ������һ���������ϵ�ͶӰ�������߶�
			fcyVec2 tProjLine(tFinalPos[1 - i][0] * tAxis[j], tFinalPos[1 - i][1] * tAxis[j]);
			if (tProjLine.y < tProjLine.x)
				std::swap(tProjLine.x, tProjLine.y);
			for (int k = 2; k<4; k++)
			{
				float v = tFinalPos[1 - i][k] * tAxis[j];
				if (v < tProjLine.x)
					tProjLine.x = v;
				if (v > tProjLine.y)
					tProjLine.y = v;
			}

			// ���и��ǲ���
			if (!OverlapTest(tAxisLine[j], tProjLine))
			{
				// �����ᶨ�ɣ�����һ�����ͶӰ���ཻ������ײ
				return false;
			}
		}
	}
	return true;
}

bool LuaSTGPlus::OBBCircleHitTest(	fcyVec2 P1, fcyVec2 Size, float Angle,
									fcyVec2 P2, float R)
{
	// ��������ε�4������
	fcyVec2 tFinalPos[4] =
	{
		fcyVec2(-Size.x, -Size.y),
		fcyVec2(Size.x, -Size.y),
		fcyVec2(Size.x, Size.y),
		fcyVec2(-Size.x, Size.y)
	};

	// float tSin = sin(Angle), tCos = cos(Angle);
	float tSin, tCos;
	SinCos(Angle, tSin, tCos);

	// �任
	for (int i = 0; i<4; i++)
	{
		tFinalPos[i].RotationSC(tSin, tCos);
		tFinalPos[i] += P1;
	}

	// ������������
	fcyVec2 tAxis[2] =
	{
		tFinalPos[1] - tFinalPos[0],
		tFinalPos[2] - tFinalPos[1]
	};

	// �᳤��
	float tAxisLen[2] =
	{
		tAxis[0].Length(),
		tAxis[1].Length(),
	};

	// ��λ������
	if (tAxisLen[0] != 0.f)
		tAxis[0] /= tAxisLen[0];
	if (tAxisLen[1] != 0.f)
		tAxis[1] /= tAxisLen[1];

	// ����������Ĳο����������ϵ�ͶӰ
	float tProjValue[2] =
	{
		((tFinalPos[1] + tFinalPos[0]) / 2.f) * tAxis[0],
		((tFinalPos[2] + tFinalPos[1]) / 2.f) * tAxis[1]
	};

	// ����Բ�����ϵ�ͶӰ
	float tCircleCenterProjValue[2] =
	{
		P2 * tAxis[0],
		P2 * tAxis[1]
	};

	// ������ײ
	if (fabs(tCircleCenterProjValue[0] - tProjValue[0]) < tAxisLen[0] / 2.f)
	{
		if (fabs(tCircleCenterProjValue[1] - tProjValue[1]) < tAxisLen[1] / 2.f + R)
			return true;
		else
			return false;
	}
	else if (fabs(tCircleCenterProjValue[1] - tProjValue[1]) < tAxisLen[1] / 2.f)
	{
		if (fabs(tCircleCenterProjValue[0] - tProjValue[0]) < tAxisLen[0] / 2.f + R)
			return true;
		else
			return false;
	}

	// ����ĸ���
	float tDist2 = R;
	tDist2 *= tDist2;
	for (int i = 0; i < 4; i++)
	{
		if ((tFinalPos[i] - P2).Length2() < tDist2)
			return true;
	}

	return false;
}

bool LuaSTGPlus::OBBAABBHitTest(fcyVec2 P, fcyVec2 Size, float Angle, fcyRect Rect)
{
	// �����OBB���ε�4������
	fcyVec2 tFinalPos[2][4] =
	{
		{
			fcyVec2(-Size.x, -Size.y),
			fcyVec2(Size.x, -Size.y),
			fcyVec2(Size.x, Size.y),
			fcyVec2(-Size.x, Size.y)
		},
		{
			Rect.a,
			fcyVec2(Rect.b.x, Rect.a.y),
			Rect.b,
			fcyVec2(Rect.a.x, Rect.b.y)
		}
	};

	float tSin, tCos;
	{
		/*
		tSin = sin(Angle);
		tCos = cos(Angle);
		*/
		SinCos(Angle, tSin, tCos);

		for (int i = 0; i<4; i++)
		{
			tFinalPos[0][i].RotationSC(tSin, tCos);
			tFinalPos[0][i] += P;
		}
	}

	// �����������ε�������
	for (int i = 0; i<2; i++)
	{
		fcyVec2 tAxis[2] =
		{
			tFinalPos[i][1] - tFinalPos[i][0],
			tFinalPos[i][2] - tFinalPos[i][1]
		};

		// ��λ������
		tAxis[0].Normalize();
		tAxis[1].Normalize();

		// ���ͶӰ�߶�
		fcyVec2 tAxisLine[2] =
		{
			fcyVec2(tFinalPos[i][0] * tAxis[0], tFinalPos[i][1] * tAxis[0]),
			fcyVec2(tFinalPos[i][1] * tAxis[1], tFinalPos[i][2] * tAxis[1])
		};

		// ��ÿһ������
		for (int j = 0; j<2; j++)
		{
			// ������һ���������ϵ�ͶӰ�������߶�
			fcyVec2 tProjLine(tFinalPos[1 - i][0] * tAxis[j], tFinalPos[1 - i][1] * tAxis[j]);
			if (tProjLine.y < tProjLine.x)
				std::swap(tProjLine.x, tProjLine.y);
			for (int k = 2; k<4; k++)
			{
				float v = tFinalPos[1 - i][k] * tAxis[j];
				if (v < tProjLine.x)
					tProjLine.x = v;
				if (v > tProjLine.y)
					tProjLine.y = v;
			}

			// ���и��ǲ���
			if (!OverlapTest(tAxisLine[j], tProjLine))
			{
				// �����ᶨ�ɣ�����һ�����ͶӰ���ཻ������ײ
				return false;
			}
		}
	}
	return true;
}

bool LuaSTGPlus::ElliTestPoint(fcyVec2 P1, float a1, float b1, float rot1, fcyVec2 P2)
{
	if (a1 == b1){
		return (P1 - P2).Length2() < a1*a1;
	}
	fcyVec2 P12 = (P2 - P1);
	P12.Rotation(-rot1);
	P12.x /= a1;
	P12.y /= b1;
	return P12.Length2() < 1;
}

bool LuaSTGPlus::ElliTest(fcyVec2 P1, float a1, float b1, float rot1, fcyVec2 P2, float a2, float b2, float rot2)
{
	if (a1 == b1){
		if (a2 == b2){
			return CircleHitTest(P1, a1, P2, a2);
		}
		//���Ҳ�ǽ����㷨���������ᶼ����r
		return ElliTestPoint(P2, a2 + a1, b2 + a1, rot2, P1);
	}
	if (a2 == b2){
		return ElliTestPoint(P1, a1 + a2, b1 + a2, rot1, P2);
	}
	//�����㷨
	float a1b1 = b1 / a1;

	fcyVec2 A2(a2, 0);
	A2.Rotation(rot2 - rot1);
	A2.x = A2.x / a1b1;

	fcyVec2 B2(b2, 0);
	B2.Rotation(rot2 + LPI_HALF - rot1);
	B2.x = B2.x / a1b1;

	fcyVec2 P12 = (P2 - P1);
	P12.Rotation(-rot1);
	P12.x = P12.x / a1b1;

	fcyVec2 P0(0, 0);
	//���Ǽ���任��Ļ��ǳ�����
	return ElliTestPoint(P12, A2.Length() + b1, B2.Length() + b1, A2.CalcuAngle(), P0);
}
