HANDLER_CLASS(PlayerCommonCards, 0x13)
{
	std::vector<CCard> cards;
	for (size_t i = 0; i < pkt.CardsSize(); ++i)
	{
		CCard c;
		c.m_nValue = pkt.Cards(i).Cardvalue();
		c.m_nColor = pkt.Cards(i).Cardcolor();
		cards.push_back(c);
	}
	View::_table.onCommonCards(pkt.Step(), cards);
}
HANDLER_END(PlayerCommonCards)
