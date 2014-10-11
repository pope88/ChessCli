HANDLER_CLASS(UserTimerStart, 0x17)
{
	if (pkt.HasChairid())
	{
		View::_table.startTimer(pkt.Timer(), pkt.Chairid());
	}
	else
	{
		View::_table.startTimer(pkt.Timer());
	}
	//View::_table.startTimer(pkt)
}
HANDLER_END(UserTimerStart)
