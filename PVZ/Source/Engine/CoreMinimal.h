

/***************************
 *    ���Ĵ����ļ� 
 ***************************/


#pragma once


#include"Core/Macro.h"
#include"Core/Struct.h"
#include"Core/Object.h"
#include<set>
#include<unordered_set>
#include<vector>


//����ת��
template<typename T, typename F>
inline T * Cast(F * pBase)
{
	if(pBase)return dynamic_cast<T*>(pBase);
	std::cout << "Cast Error!" <<std::endl;
	return nullptr;
}
