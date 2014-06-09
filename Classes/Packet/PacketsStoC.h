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

}
}
}
}

#endif // _SSU_PACKETSSTOC_H_
