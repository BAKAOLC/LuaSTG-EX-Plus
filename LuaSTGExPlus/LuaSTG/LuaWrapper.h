/// @file LuaWrapper.h
/// @brief lua��װ�� ���ڵ���C++��������
#pragma once
#include "Global.h"

namespace LuaSTGPlus
{
	/// @brief ��ɫ��װ
	class ColorWrapper
	{
	public:
		/// @brief ��luaע���װ��
		static void Register(lua_State* L)LNOEXCEPT;
		/// @brief ����һ����ɫ�ಢ�����ջ
		static fcyColor* CreateAndPush(lua_State* L);
	};

	/// @brief �������������װ
	class RandomizerWrapper
	{
	public:
		/// @brief ��luaע���װ��
		static void Register(lua_State* L)LNOEXCEPT;
		/// @brief ����һ����ɫ�ಢ�����ջ
		static fcyRandomWELL512* CreateAndPush(lua_State* L);
	};

	class GameObjectBentLaser;

	/// @brief ���߼����װ
	class BentLaserDataWrapper
	{
	private:
		struct Wrapper
		{
			GameObjectBentLaser* handle;
		};
	public:
		/// @brief ��luaע���װ��
		static void Register(lua_State* L)LNOEXCEPT;
		/// @brief ����һ�����߼����ಢ�����ջ
		static GameObjectBentLaser* CreateAndPush(lua_State* L);
	};
	
	/// @brief f2d�߾������뼶ͣ��
	class Fancy2dStopWatchWrapper
	{
	public:
		/// @brief ��luaע���װ��
		static void Register(lua_State* L)LNOEXCEPT;
		/// @brief ����һ���߾������뼶ͣ���ಢ�����ջ
		static fcyStopWatch* CreateAndPush(lua_State* L);
	};

	/// @brief �ڽ�������װ
	class BuiltInFunctionWrapper
	{
	public:
		/// @brief ��luaע���װ��
		static void Register(lua_State* L)LNOEXCEPT;
	};
}