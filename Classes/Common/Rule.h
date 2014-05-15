#pragma once

enum RULE
{
	DANZHANG			= 1 << 0,	//单张
	RULE2				= 1 << 1,	//对子
	RULE3				= 1 << 2,	//三张
	RULE31				= 1 << 3,	//31
	RULE32				= 1 << 4,	//32
	RULE3311			= 1 << 5,	//3311
	RULE3322			= 1 << 6,	//3322
	RULE333111			= 1 << 7,	//333111
	RULE333222			= 1 << 8,	//
	RULE33331111		= 1 << 9,	//33331111
	RULE4				= 1 << 10,	//炸弹
	RULE411				= 1 << 11,	//41
	RULE422				= 1 << 12,	//422
    RULEDOUBLESERIES	= 1 << 13,	//双顺
	RULESERIES			= 1 << 14,	//顺子
	RULETHREESERIES 	= 1 << 15,	//三顺
};

