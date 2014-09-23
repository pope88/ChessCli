#ifndef _PRECONFIG_H_
#define _PRECONFIG_H_

#define LS_PRE(p) __ls_##p
#define LS_PROPERTY_RETAIN(varType, varName, funName)\
	CC_SYNTHESIZE_RETAIN(varType, LS_PRE(varName), funName);

// ��ʼ�����ͷŰ�װ�꣬��ҪΪ�˷�װǰ׺��ʼ����ͳһ
#define LS_P_INIT(p) LS_PRE(p) = 0
#define LS_P_RELEASE(p) CC_SAFE_RELEASE_NULL(LS_PRE(p))

#define CREATE_FUNC2(__TYPE__, TYPE0, TYPE1) \
	static __TYPE__* create(TYPE0 T1, TYPE1 T2) \
{ \
	__TYPE__ *pRet = new __TYPE__(T1, T2); \
	if (pRet && pRet->init()) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}

#endif