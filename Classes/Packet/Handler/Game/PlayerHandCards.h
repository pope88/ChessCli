HANDLER_CLASS(PlayerHandCards, 0x12)
{
	View::_table.dealingCard();
	std::vector<CCard> cards;
	for (size_t i = 0; i < pkt.CardsSize(); ++i)
	{
		cards.push_back(CCard(pkt.Cards(i).Cardvalue(), pkt.Cards(i).Cardcolor()));
	}
	View::_table.renderCardByPos(0, cards);
}
HANDLER_END(PlayerHandCards)
