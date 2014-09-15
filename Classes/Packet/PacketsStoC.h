#ifndef _SSU_PACKETSSTOC_H_
#define _SSU_PACKETSSTOC_H_

#include <stdint.h>
#include "SsuObject.h"

namespace game {
namespace net {
namespace data {
namespace StoC {

class SCUserRegister_0x01: public ::ssu::Object {
 public:
  inline SCUserRegister_0x01(): _result(0), _userId(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCUserRegister_0x01() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

  inline uint32_t UserId() const { return _userId; }
  inline void SetUserId(uint32_t val__) { _userId = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasUserId() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  uint32_t _result;
  uint32_t _userId;

  uint32_t _isSetFlag[1];

};

class SCUserLogin_0x02: public ::ssu::Object {
 public:
  inline SCUserLogin_0x02(): _result(0), _userId(0), _vipLevel(0), _banTime(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCUserLogin_0x02() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

  inline uint32_t UserId() const { return _userId; }
  inline void SetUserId(uint32_t val__) { _userId = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasUserId() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline const std::string& UserName() const { return _userName; }
  inline void SetUserName(const std::string& val__) { _userName = val__; _isSetFlag[0] |= 0x02; }
  inline std::string& MutableUserName() { _isSetFlag[0] |= 0x02; return _userName; }
  inline bool HasUserName() const { return (_isSetFlag[0] & 0x02) > 0; }

  inline uint32_t VipLevel() const { return _vipLevel; }
  inline void SetVipLevel(uint32_t val__) { _vipLevel = val__; _isSetFlag[0] |= 0x04; }
  inline bool HasVipLevel() const { return (_isSetFlag[0] & 0x04) > 0; }

  inline uint32_t BanTime() const { return _banTime; }
  inline void SetBanTime(uint32_t val__) { _banTime = val__; _isSetFlag[0] |= 0x08; }
  inline bool HasBanTime() const { return (_isSetFlag[0] & 0x08) > 0; }

  inline uint32_t Steps(size_t index__) const { return _steps[index__]; }
  inline void AddSteps(uint32_t val__) { _steps.Add(val__); }
  inline void SetSteps(size_t index__, uint32_t val__) { _steps[index__] = val__; }
  inline ::ssu::RepeatedObject<uint32_t>& MutableSteps() { return _steps; }
  inline size_t StepsSize() const { return _steps.Size(); }
  inline void ClearSteps() { _steps.Clear(); }
  inline void ReserveSteps(size_t size__) { if(_steps.Size() < size__) _steps.Reserve(size__); }

 protected:
  uint32_t _result;
  uint32_t _userId;
  std::string _userName;
  uint32_t _vipLevel;
  uint32_t _banTime;
  ::ssu::RepeatedObject<uint32_t> _steps;

  uint32_t _isSetFlag[1];

};

class SCUserInfo_0x03: public ::ssu::Object {
 public:
  inline SCUserInfo_0x03(): _gold(0), _totalTopup(0), _totalConsume(0) { }

  virtual ~SCUserInfo_0x03() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Gold() const { return _gold; }
  inline void SetGold(uint32_t val__) { _gold = val__; }

  inline uint32_t TotalTopup() const { return _totalTopup; }
  inline void SetTotalTopup(uint32_t val__) { _totalTopup = val__; }

  inline uint32_t TotalConsume() const { return _totalConsume; }
  inline void SetTotalConsume(uint32_t val__) { _totalConsume = val__; }

 protected:
  uint32_t _gold;
  uint32_t _totalTopup;
  uint32_t _totalConsume;

};

class RoomInfo: public ::ssu::Object {
 public:
  inline RoomInfo(): _roomId(0), _palyerNum(0) { }

  virtual ~RoomInfo() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t RoomId() const { return _roomId; }
  inline void SetRoomId(uint32_t val__) { _roomId = val__; }

  inline uint32_t PalyerNum() const { return _palyerNum; }
  inline void SetPalyerNum(uint32_t val__) { _palyerNum = val__; }

 protected:
  uint32_t _roomId;
  uint32_t _palyerNum;

};

class SCUserRoomList_0x04: public ::ssu::Object {
 public:
  virtual ~SCUserRoomList_0x04();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const RoomInfo& Rmlist(size_t index__) const { return *_rmlist[index__]; }
  inline RoomInfo * NewRmlist() { return new(std::nothrow) RoomInfo; }
  inline RoomInfo * AddRmlist() { RoomInfo * val__ = new(std::nothrow) RoomInfo; if(val__ == NULL) return NULL; _rmlist.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<RoomInfo *>& MutableRmlist() { return _rmlist; }
  inline size_t RmlistSize() const { return _rmlist.Size(); }
  inline void ClearRmlist() { for(::ssu::RepeatedObject<RoomInfo *>::iterator iter = _rmlist.begin(); iter != _rmlist.end(); ++ iter) { delete *iter; } _rmlist.Clear(); }
  inline void ReserveRmlist(size_t size__) { if(_rmlist.Size() < size__) _rmlist.Reserve(size__); }

 protected:
  ::ssu::RepeatedObject<RoomInfo *> _rmlist;

};

class SCUserRoomInfo_0x05: public ::ssu::Object {
 public:
  virtual ~SCUserRoomInfo_0x05() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class SCUserEnterRoom_0x06: public ::ssu::Object {
 public:
  inline SCUserEnterRoom_0x06(): _res(0) { }

  virtual ~SCUserEnterRoom_0x06() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Res() const { return _res; }
  inline void SetRes(uint32_t val__) { _res = val__; }

 protected:
  uint32_t _res;

};

class PlayerBaseInfo: public ::ssu::Object {
 public:
  inline PlayerBaseInfo(): _chairid(0), _allchips(0) { }

  virtual ~PlayerBaseInfo() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Chairid() const { return _chairid; }
  inline void SetChairid(uint32_t val__) { _chairid = val__; }

  inline const std::string& Nickname() const { return _nickname; }
  inline void SetNickname(const std::string& val__) { _nickname = val__; }
  inline std::string& MutableNickname() { return _nickname; }

  inline uint32_t Allchips() const { return _allchips; }
  inline void SetAllchips(uint32_t val__) { _allchips = val__; }

 protected:
  uint32_t _chairid;
  std::string _nickname;
  uint32_t _allchips;

};

class SCUserEnterTable_0x07: public ::ssu::Object {
 public:
  inline SCUserEnterTable_0x07(): _res(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCUserEnterTable_0x07();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Res() const { return _res; }
  inline void SetRes(uint32_t val__) { _res = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasRes() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline const PlayerBaseInfo& Playerinfos(size_t index__) const { return *_playerinfos[index__]; }
  inline PlayerBaseInfo * NewPlayerinfos() { return new(std::nothrow) PlayerBaseInfo; }
  inline PlayerBaseInfo * AddPlayerinfos() { PlayerBaseInfo * val__ = new(std::nothrow) PlayerBaseInfo; if(val__ == NULL) return NULL; _playerinfos.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<PlayerBaseInfo *>& MutablePlayerinfos() { return _playerinfos; }
  inline size_t PlayerinfosSize() const { return _playerinfos.Size(); }
  inline void ClearPlayerinfos() { for(::ssu::RepeatedObject<PlayerBaseInfo *>::iterator iter = _playerinfos.begin(); iter != _playerinfos.end(); ++ iter) { delete *iter; } _playerinfos.Clear(); }
  inline void ReservePlayerinfos(size_t size__) { if(_playerinfos.Size() < size__) _playerinfos.Reserve(size__); }

 protected:
  uint32_t _res;
  ::ssu::RepeatedObject<PlayerBaseInfo *> _playerinfos;

  uint32_t _isSetFlag[1];

};

class SCUserPlayerNow_0x08: public ::ssu::Object {
 public:
  inline SCUserPlayerNow_0x08(): _res(0), _basechips(0), _lowestchips(0) { }

  virtual ~SCUserPlayerNow_0x08() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Res() const { return _res; }
  inline void SetRes(uint32_t val__) { _res = val__; }

  inline uint32_t Basechips() const { return _basechips; }
  inline void SetBasechips(uint32_t val__) { _basechips = val__; }

  inline uint32_t Lowestchips() const { return _lowestchips; }
  inline void SetLowestchips(uint32_t val__) { _lowestchips = val__; }

 protected:
  uint32_t _res;
  uint32_t _basechips;
  uint32_t _lowestchips;

};

class PGStatus: public ::ssu::Object {
 public:
  inline PGStatus(): _chairid(0), _status(0) { }

  virtual ~PGStatus() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Chairid() const { return _chairid; }
  inline void SetChairid(uint32_t val__) { _chairid = val__; }

  inline uint32_t Status() const { return _status; }
  inline void SetStatus(uint32_t val__) { _status = val__; }

 protected:
  uint32_t _chairid;
  uint32_t _status;

};

class SCPlayerGameSart_0x09: public ::ssu::Object {
 public:
  inline SCPlayerGameSart_0x09(): _basechips(0), _lowestchips(0) { }

  virtual ~SCPlayerGameSart_0x09() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Basechips() const { return _basechips; }
  inline void SetBasechips(uint32_t val__) { _basechips = val__; }

  inline uint32_t Lowestchips() const { return _lowestchips; }
  inline void SetLowestchips(uint32_t val__) { _lowestchips = val__; }

 protected:
  uint32_t _basechips;
  uint32_t _lowestchips;

};

class SCPlayerGameStatus_0x10: public ::ssu::Object {
 public:
  virtual ~SCPlayerGameStatus_0x10();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const PGStatus& Playerstatus(size_t index__) const { return *_playerstatus[index__]; }
  inline PGStatus * NewPlayerstatus() { return new(std::nothrow) PGStatus; }
  inline PGStatus * AddPlayerstatus() { PGStatus * val__ = new(std::nothrow) PGStatus; if(val__ == NULL) return NULL; _playerstatus.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<PGStatus *>& MutablePlayerstatus() { return _playerstatus; }
  inline size_t PlayerstatusSize() const { return _playerstatus.Size(); }
  inline void ClearPlayerstatus() { for(::ssu::RepeatedObject<PGStatus *>::iterator iter = _playerstatus.begin(); iter != _playerstatus.end(); ++ iter) { delete *iter; } _playerstatus.Clear(); }
  inline void ReservePlayerstatus(size_t size__) { if(_playerstatus.Size() < size__) _playerstatus.Reserve(size__); }

 protected:
  ::ssu::RepeatedObject<PGStatus *> _playerstatus;

};

class SCPlayerBlindChips_0x11: public ::ssu::Object {
 public:
  class blindInfo: public ::ssu::Object {
   public:
    inline blindInfo(): _chairid(0), _chips(0), _remainchips(0) { }

    virtual ~blindInfo() { }

   public:
    virtual uint8_t * PackBuffer(uint8_t * buf);
    virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
    virtual size_t Size() const;

   public:
    inline uint32_t Chairid() const { return _chairid; }
    inline void SetChairid(uint32_t val__) { _chairid = val__; }

    inline uint32_t Chips() const { return _chips; }
    inline void SetChips(uint32_t val__) { _chips = val__; }

    inline uint32_t Remainchips() const { return _remainchips; }
    inline void SetRemainchips(uint32_t val__) { _remainchips = val__; }

   protected:
    uint32_t _chairid;
    uint32_t _chips;
    uint32_t _remainchips;

  };

 public:
  inline SCPlayerBlindChips_0x11(): _tableamount(0) { }

  virtual ~SCPlayerBlindChips_0x11();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Tableamount() const { return _tableamount; }
  inline void SetTableamount(uint32_t val__) { _tableamount = val__; }

  inline const blindInfo& Blindinfos(size_t index__) const { return *_blindinfos[index__]; }
  inline blindInfo * NewBlindinfos() { return new(std::nothrow) blindInfo; }
  inline blindInfo * AddBlindinfos() { blindInfo * val__ = new(std::nothrow) blindInfo; if(val__ == NULL) return NULL; _blindinfos.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<blindInfo *>& MutableBlindinfos() { return _blindinfos; }
  inline size_t BlindinfosSize() const { return _blindinfos.Size(); }
  inline void ClearBlindinfos() { for(::ssu::RepeatedObject<blindInfo *>::iterator iter = _blindinfos.begin(); iter != _blindinfos.end(); ++ iter) { delete *iter; } _blindinfos.Clear(); }
  inline void ReserveBlindinfos(size_t size__) { if(_blindinfos.Size() < size__) _blindinfos.Reserve(size__); }

 protected:
  uint32_t _tableamount;
  ::ssu::RepeatedObject<blindInfo *> _blindinfos;

};

class card: public ::ssu::Object {
 public:
  inline card(): _cardvalue(0), _cardcolor(0) { }

  virtual ~card() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Cardvalue() const { return _cardvalue; }
  inline void SetCardvalue(uint32_t val__) { _cardvalue = val__; }

  inline uint32_t Cardcolor() const { return _cardcolor; }
  inline void SetCardcolor(uint32_t val__) { _cardcolor = val__; }

 protected:
  uint32_t _cardvalue;
  uint32_t _cardcolor;

};

class SCPlayerHandCards_0x12: public ::ssu::Object {
 public:
  inline SCPlayerHandCards_0x12(): _pos(0) { }

  virtual ~SCPlayerHandCards_0x12();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Pos() const { return _pos; }
  inline void SetPos(uint32_t val__) { _pos = val__; }

  inline const card& Cards(size_t index__) const { return *_cards[index__]; }
  inline card * NewCards() { return new(std::nothrow) card; }
  inline card * AddCards() { card * val__ = new(std::nothrow) card; if(val__ == NULL) return NULL; _cards.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<card *>& MutableCards() { return _cards; }
  inline size_t CardsSize() const { return _cards.Size(); }
  inline void ClearCards() { for(::ssu::RepeatedObject<card *>::iterator iter = _cards.begin(); iter != _cards.end(); ++ iter) { delete *iter; } _cards.Clear(); }
  inline void ReserveCards(size_t size__) { if(_cards.Size() < size__) _cards.Reserve(size__); }

 protected:
  uint32_t _pos;
  ::ssu::RepeatedObject<card *> _cards;

};

class SCPlayerCommonCards_0x13: public ::ssu::Object {
 public:
  inline SCPlayerCommonCards_0x13(): _step(0) { }

  virtual ~SCPlayerCommonCards_0x13();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Step() const { return _step; }
  inline void SetStep(uint32_t val__) { _step = val__; }

  inline const card& Cards(size_t index__) const { return *_cards[index__]; }
  inline card * NewCards() { return new(std::nothrow) card; }
  inline card * AddCards() { card * val__ = new(std::nothrow) card; if(val__ == NULL) return NULL; _cards.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<card *>& MutableCards() { return _cards; }
  inline size_t CardsSize() const { return _cards.Size(); }
  inline void ClearCards() { for(::ssu::RepeatedObject<card *>::iterator iter = _cards.begin(); iter != _cards.end(); ++ iter) { delete *iter; } _cards.Clear(); }
  inline void ReserveCards(size_t size__) { if(_cards.Size() < size__) _cards.Reserve(size__); }

 protected:
  uint32_t _step;
  ::ssu::RepeatedObject<card *> _cards;

};

class SCPlayerOperateReq_0x14: public ::ssu::Object {
 public:
  inline SCPlayerOperateReq_0x14(): _opcode(0), _chairid(0), _basechips(0), _currentchips(0) { }

  virtual ~SCPlayerOperateReq_0x14() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Opcode() const { return _opcode; }
  inline void SetOpcode(uint32_t val__) { _opcode = val__; }

  inline uint32_t Chairid() const { return _chairid; }
  inline void SetChairid(uint32_t val__) { _chairid = val__; }

  inline uint32_t Basechips() const { return _basechips; }
  inline void SetBasechips(uint32_t val__) { _basechips = val__; }

  inline uint32_t Currentchips() const { return _currentchips; }
  inline void SetCurrentchips(uint32_t val__) { _currentchips = val__; }

 protected:
  uint32_t _opcode;
  uint32_t _chairid;
  uint32_t _basechips;
  uint32_t _currentchips;

};

class SCPlayerOperateNot_0x15: public ::ssu::Object {
 public:
  inline SCPlayerOperateNot_0x15(): _opcode(0), _chairid(0), _currentchips(0), _leavechips(0), _totalchips(0) { }

  virtual ~SCPlayerOperateNot_0x15() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Opcode() const { return _opcode; }
  inline void SetOpcode(uint32_t val__) { _opcode = val__; }

  inline uint32_t Chairid() const { return _chairid; }
  inline void SetChairid(uint32_t val__) { _chairid = val__; }

  inline uint32_t Currentchips() const { return _currentchips; }
  inline void SetCurrentchips(uint32_t val__) { _currentchips = val__; }

  inline uint32_t Leavechips() const { return _leavechips; }
  inline void SetLeavechips(uint32_t val__) { _leavechips = val__; }

  inline uint32_t Totalchips() const { return _totalchips; }
  inline void SetTotalchips(uint32_t val__) { _totalchips = val__; }

 protected:
  uint32_t _opcode;
  uint32_t _chairid;
  uint32_t _currentchips;
  uint32_t _leavechips;
  uint32_t _totalchips;

};

}
}
}
}

#endif // _SSU_PACKETSSTOC_H_
