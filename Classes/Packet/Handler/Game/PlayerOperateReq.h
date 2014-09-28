HANDLER_CLASS(PlayerOperateReq, 0x14)
{
	View::_table.askMyOperate(pkt.Opcode(), pkt.Currentchips());
}
HANDLER_END(PlayerOperateReq)
