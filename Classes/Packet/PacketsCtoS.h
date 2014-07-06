#ifndef _SSU_PACKETSCTOS_H_
#define _SSU_PACKETSCTOS_H_

#include <stdint.h>
#include "SsuObject.h"

namespace game {
namespace net {
namespace data {
namespace CtoS {

class HeadPack: public ::ssu::Object {
 public:
  inline HeadPack(): _cmdtype(0), _cmdlen(0) { }

  virtual ~HeadPack() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline int Cmdtype() const { return _cmdtype; }
  inline void SetCmdtype(int val__) { _cmdtype = val__; }

  inline int Cmdlen() const { return _cmdlen; }
  inline void SetCmdlen(int val__) { _cmdlen = val__; }

 protected:
  int _cmdtype;
  int _cmdlen;

};

class CSUserLogout_0xFFFF: public ::ssu::Object {
 public:
  virtual ~CSUserLogout_0xFFFF() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSUserRegister_0x01: public ::ssu::Object {
 public:
  virtual ~CSUserRegister_0x01() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Username() const { return _username; }
  inline void SetUsername(const std::string& val__) { _username = val__; }
  inline std::string& MutableUsername() { return _username; }

  inline const std::string& Pwd() const { return _pwd; }
  inline void SetPwd(const std::string& val__) { _pwd = val__; }
  inline std::string& MutablePwd() { return _pwd; }

 protected:
  std::string _username;
  std::string _pwd;

};

class CSUserLogin_0x02: public ::ssu::Object {
 public:
  inline CSUserLogin_0x02(): _wallow(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~CSUserLogin_0x02() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Username() const { return _username; }
  inline void SetUsername(const std::string& val__) { _username = val__; }
  inline std::string& MutableUsername() { return _username; }

  inline const std::string& Pwd() const { return _pwd; }
  inline void SetPwd(const std::string& val__) { _pwd = val__; _isSetFlag[0] |= 0x01; }
  inline std::string& MutablePwd() { _isSetFlag[0] |= 0x01; return _pwd; }
  inline bool HasPwd() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline uint32_t Wallow() const { return _wallow; }
  inline void SetWallow(uint32_t val__) { _wallow = val__; _isSetFlag[0] |= 0x02; }
  inline bool HasWallow() const { return (_isSetFlag[0] & 0x02) > 0; }

 protected:
  std::string _username;
  std::string _pwd;
  uint32_t _wallow;

  uint32_t _isSetFlag[1];

};

class CSUserInfo_0x03: public ::ssu::Object {
 public:
  virtual ~CSUserInfo_0x03() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSUserRoomList_0x04: public ::ssu::Object {
 public:
  virtual ~CSUserRoomList_0x04() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSUserRoomInfo_0x05: public ::ssu::Object {
 public:
  virtual ~CSUserRoomInfo_0x05() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSUserEnterRoom_0x06: public ::ssu::Object {
 public:
  inline CSUserEnterRoom_0x06(): _roomid(0) { }

  virtual ~CSUserEnterRoom_0x06() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Roomid() const { return _roomid; }
  inline void SetRoomid(uint32_t val__) { _roomid = val__; }

 protected:
  uint32_t _roomid;

};

class CSUserEnterTable_0x07: public ::ssu::Object {
 public:
  inline CSUserEnterTable_0x07(): _tableno(0) { }

  virtual ~CSUserEnterTable_0x07() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Tableno() const { return _tableno; }
  inline void SetTableno(uint32_t val__) { _tableno = val__; }

 protected:
  uint32_t _tableno;

};

class CSUserPlayNow_0x08: public ::ssu::Object {
 public:
  virtual ~CSUserPlayNow_0x08() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

}
}
}
}

#endif // _SSU_PACKETSCTOS_H_
