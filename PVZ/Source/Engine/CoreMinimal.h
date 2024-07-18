

/***************************
 *      核心代码文件 
 ***************************/


#pragma once


#include"Core/Macro.h"
#include"Core/Struct.h"
#include"Core/Object.h"
#include<set>
#include<unordered_set>
#include<vector>


//类型转换
template<typename T, typename F>
inline T * Cast(F * pBase)
{
	if(pBase)return dynamic_cast<T*>(pBase);

#ifdef _DEBUG
	std::cout << "Cast Error!" << std::endl;
#endif
	return nullptr;
}
