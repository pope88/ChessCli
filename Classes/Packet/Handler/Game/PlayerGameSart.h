
HANDLER_CLASS(PlayerGameSart, 0x09)
{
	View::_table.onPokerStart(pkt.Basechips(), pkt.Bigblindpos(), pkt.Smallblindpos());
}
HANDLER_END(PlayerGameSart)
