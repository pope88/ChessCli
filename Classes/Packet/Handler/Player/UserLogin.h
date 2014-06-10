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

HANDLER_CLASS(UserLogin, 0x02)
{
 printf("on server user login ");

}
HANDLER_END(UserLogin)
