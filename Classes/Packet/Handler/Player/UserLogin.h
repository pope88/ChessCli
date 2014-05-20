inline UInt8 hextov(char s)
{
	if(s >= '0' && s <= '9')
		return s - '0';
	if(s >= 'a' && s <= 'f')
		return s - ('a' - 10);
	if(s >= 'A' && s <= 'F')
		return s - ('A' - 10);
	return 0;
}

HANDLER_CLASS_INIT(UserLogin, 0x02)
{
	int yy = 0;
}
HANDLER_END(UserLogin)
