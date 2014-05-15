#ifndef _SSU_PACKETSCTOS_H_
#define _SSU_PACKETSCTOS_H_

#include <stdint.h>
#include "SsuObject.h"

namespace game {
namespace net {
namespace data {
namespace CtoS {

enum cmd_cli
 {  cmd_userregister_cli = 1,
  cmd_userlogin_cli = 2,
  cmd_userinfo_cli = 3,
  cmd_heroinfo_cli = 255,
};

enum cmd_system
 {  cmd_userlogout = 65535,
};

class HeadPack: public ::ssu::Object {
 public:
  inline HeadPack(): _cmdtype(0), _cmdlength(0), _cliid(0), _svrid(0) { }

  virtual ~HeadPack() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline int Cmdtype() const { return _cmdtype; }
  inline void SetCmdtype(int val__) { _cmdtype = val__; }

  inline int Cmdlength() const { return _cmdlength; }
  inline void SetCmdlength(int val__) { _cmdlength = val__; }

  inline int Cliid() const { return _cliid; }
  inline void SetCliid(int val__) { _cliid = val__; }

  inline int Svrid() const { return _svrid; }
  inline void SetSvrid(int val__) { _svrid = val__; }

 protected:
  int _cmdtype;
  int _cmdlength;
  int _cliid;
  int _svrid;

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

class CSNewHero_0x04: public ::ssu::Object {
 public:
  inline CSNewHero_0x04(): _ismale(false), _job(0) { }

  virtual ~CSNewHero_0x04() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline bool Ismale() const { return _ismale; }
  inline void SetIsmale(bool val__) { _ismale = val__; }

  inline const std::string& Name() const { return _name; }
  inline void SetName(const std::string& val__) { _name = val__; }
  inline std::string& MutableName() { return _name; }

  inline uint32_t Job() const { return _job; }
  inline void SetJob(uint32_t val__) { _job = val__; }

 protected:
  bool _ismale;
  std::string _name;
  uint32_t _job;

};

class CSHeroLoad_0x05: public ::ssu::Object {
 public:
  inline CSHeroLoad_0x05(): _heroid(0) { }

  virtual ~CSHeroLoad_0x05() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Heroid() const { return _heroid; }
  inline void SetHeroid(uint32_t val__) { _heroid = val__; }

 protected:
  uint32_t _heroid;

};

class CSHeroInfos_0x06: public ::ssu::Object {
 public:
  inline CSHeroInfos_0x06(): _noid(0) { }

  virtual ~CSHeroInfos_0x06() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Noid() const { return _noid; }
  inline void SetNoid(uint32_t val__) { _noid = val__; }

 protected:
  uint32_t _noid;

};

class CSAskItemsInfo_0x08: public ::ssu::Object {
 public:
  virtual ~CSAskItemsInfo_0x08() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSEquipAttribute: public ::ssu::Object {
 public:
  inline CSEquipAttribute(): _equipId(0), _position(0), _isBand(false)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~CSEquipAttribute() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t EquipId() const { return _equipId; }
  inline void SetEquipId(uint32_t val__) { _equipId = val__; }

  inline uint32_t Position() const { return _position; }
  inline void SetPosition(uint32_t val__) { _position = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasPosition() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline bool IsBand() const { return _isBand; }
  inline void SetIsBand(bool val__) { _isBand = val__; _isSetFlag[0] |= 0x02; }
  inline bool HasIsBand() const { return (_isSetFlag[0] & 0x02) > 0; }

 protected:
  uint32_t _equipId;
  uint32_t _position;
  bool _isBand;

  uint32_t _isSetFlag[1];

};

class CSItem: public ::ssu::Object {
 public:
  inline CSItem(): _itemId(0), _icount(0), _isBand(false)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~CSItem() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t ItemId() const { return _itemId; }
  inline void SetItemId(uint32_t val__) { _itemId = val__; }

  inline uint32_t Icount() const { return _icount; }
  inline void SetIcount(uint32_t val__) { _icount = val__; }

  inline bool IsBand() const { return _isBand; }
  inline void SetIsBand(bool val__) { _isBand = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasIsBand() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  uint32_t _itemId;
  uint32_t _icount;
  bool _isBand;

  uint32_t _isSetFlag[1];

};

class CSUseItem_0x09: public ::ssu::Object {
 public:
  inline CSUseItem_0x09(): _heroId(0) { }

  virtual ~CSUseItem_0x09();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const CSItem& Items(size_t index__) const { return *_items[index__]; }
  inline CSItem * NewItems() { return new(std::nothrow) CSItem; }
  inline CSItem * AddItems() { CSItem * val__ = new(std::nothrow) CSItem; if(val__ == NULL) return NULL; _items.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<CSItem *>& MutableItems() { return _items; }
  inline size_t ItemsSize() const { return _items.Size(); }
  inline void ClearItems() { for(::ssu::RepeatedObject<CSItem *>::iterator iter = _items.begin(); iter != _items.end(); ++ iter) { delete *iter; } _items.Clear(); }
  inline void ReserveItems(size_t size__) { if(_items.Size() < size__) _items.Reserve(size__); }

  inline uint32_t HeroId() const { return _heroId; }
  inline void SetHeroId(uint32_t val__) { _heroId = val__; }

 protected:
  ::ssu::RepeatedObject<CSItem *> _items;
  uint32_t _heroId;

};

class dlitems: public ::ssu::Object {
 public:
  inline dlitems(): _itemid(0), _num(0) { }

  virtual ~dlitems() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Itemid() const { return _itemid; }
  inline void SetItemid(uint32_t val__) { _itemid = val__; }

  inline uint32_t Num() const { return _num; }
  inline void SetNum(uint32_t val__) { _num = val__; }

 protected:
  uint32_t _itemid;
  uint32_t _num;

};

class CSDeleteItems_0x10: public ::ssu::Object {
 public:
  virtual ~CSDeleteItems_0x10();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const dlitems& Ditems(size_t index__) const { return *_ditems[index__]; }
  inline dlitems * NewDitems() { return new(std::nothrow) dlitems; }
  inline dlitems * AddDitems() { dlitems * val__ = new(std::nothrow) dlitems; if(val__ == NULL) return NULL; _ditems.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<dlitems *>& MutableDitems() { return _ditems; }
  inline size_t DitemsSize() const { return _ditems.Size(); }
  inline void ClearDitems() { for(::ssu::RepeatedObject<dlitems *>::iterator iter = _ditems.begin(); iter != _ditems.end(); ++ iter) { delete *iter; } _ditems.Clear(); }
  inline void ReserveDitems(size_t size__) { if(_ditems.Size() < size__) _ditems.Reserve(size__); }

 protected:
  ::ssu::RepeatedObject<dlitems *> _ditems;

};

class CSPutOnEquip_0x13: public ::ssu::Object {
 public:
  virtual ~CSPutOnEquip_0x13() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Key() const { return _key; }
  inline void SetKey(const std::string& val__) { _key = val__; }
  inline std::string& MutableKey() { return _key; }

 protected:
  std::string _key;

};

class CSPutOffEquip_0x14: public ::ssu::Object {
 public:
  inline CSPutOffEquip_0x14(): _pos(0) { }

  virtual ~CSPutOffEquip_0x14() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Key() const { return _key; }
  inline void SetKey(const std::string& val__) { _key = val__; }
  inline std::string& MutableKey() { return _key; }

  inline uint32_t Pos() const { return _pos; }
  inline void SetPos(uint32_t val__) { _pos = val__; }

 protected:
  std::string _key;
  uint32_t _pos;

};

class CSAcceptTask_0x15: public ::ssu::Object {
 public:
  inline CSAcceptTask_0x15(): _taskid(0) { }

  virtual ~CSAcceptTask_0x15() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Taskid() const { return _taskid; }
  inline void SetTaskid(uint32_t val__) { _taskid = val__; }

 protected:
  uint32_t _taskid;

};

class CSSubmitTask_0x16: public ::ssu::Object {
 public:
  inline CSSubmitTask_0x16(): _taskid(0) { }

  virtual ~CSSubmitTask_0x16() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Taskid() const { return _taskid; }
  inline void SetTaskid(uint32_t val__) { _taskid = val__; }

 protected:
  uint32_t _taskid;

};

class CSUpdateTask_0x17: public ::ssu::Object {
 public:
  inline CSUpdateTask_0x17(): _taskid(0), _fval(0), _fva2(0), _fva3(0), _fva4(0), _fva5(0) { }

  virtual ~CSUpdateTask_0x17() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Taskid() const { return _taskid; }
  inline void SetTaskid(uint32_t val__) { _taskid = val__; }

  inline uint32_t Fval() const { return _fval; }
  inline void SetFval(uint32_t val__) { _fval = val__; }

  inline uint32_t Fva2() const { return _fva2; }
  inline void SetFva2(uint32_t val__) { _fva2 = val__; }

  inline uint32_t Fva3() const { return _fva3; }
  inline void SetFva3(uint32_t val__) { _fva3 = val__; }

  inline uint32_t Fva4() const { return _fva4; }
  inline void SetFva4(uint32_t val__) { _fva4 = val__; }

  inline uint32_t Fva5() const { return _fva5; }
  inline void SetFva5(uint32_t val__) { _fva5 = val__; }

 protected:
  uint32_t _taskid;
  uint32_t _fval;
  uint32_t _fva2;
  uint32_t _fva3;
  uint32_t _fva4;
  uint32_t _fva5;

};

class CSHeroProp_0x18: public ::ssu::Object {
 public:
  inline CSHeroProp_0x18(): _heroid(0) { }

  virtual ~CSHeroProp_0x18() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Heroid() const { return _heroid; }
  inline void SetHeroid(uint32_t val__) { _heroid = val__; }

 protected:
  uint32_t _heroid;

};

class CSExtendPack_0x19: public ::ssu::Object {
 public:
  virtual ~CSExtendPack_0x19() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;


};

class CSMaterialMerge_0x20: public ::ssu::Object {
 public:
  inline CSMaterialMerge_0x20(): _itemId(0) { }

  virtual ~CSMaterialMerge_0x20() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t ItemId() const { return _itemId; }
  inline void SetItemId(uint32_t val__) { _itemId = val__; }

 protected:
  uint32_t _itemId;

};

class CSEquipMerge_0x21: public ::ssu::Object {
 public:
  inline CSEquipMerge_0x21(): _equipId(0) { }

  virtual ~CSEquipMerge_0x21() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t EquipId() const { return _equipId; }
  inline void SetEquipId(uint32_t val__) { _equipId = val__; }

 protected:
  uint32_t _equipId;

};

class CSTalk_0x22: public ::ssu::Object {
 public:
  inline CSTalk_0x22(): _mtype(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~CSTalk_0x22() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Mtype() const { return _mtype; }
  inline void SetMtype(uint32_t val__) { _mtype = val__; }

  inline const std::string& Msg() const { return _msg; }
  inline void SetMsg(const std::string& val__) { _msg = val__; }
  inline std::string& MutableMsg() { return _msg; }

  inline const std::string& Heroid() const { return _heroid; }
  inline void SetHeroid(const std::string& val__) { _heroid = val__; _isSetFlag[0] |= 0x01; }
  inline std::string& MutableHeroid() { _isSetFlag[0] |= 0x01; return _heroid; }
  inline bool HasHeroid() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline const std::string& Heroname() const { return _heroname; }
  inline void SetHeroname(const std::string& val__) { _heroname = val__; _isSetFlag[0] |= 0x02; }
  inline std::string& MutableHeroname() { _isSetFlag[0] |= 0x02; return _heroname; }
  inline bool HasHeroname() const { return (_isSetFlag[0] & 0x02) > 0; }

 protected:
  uint32_t _mtype;
  std::string _msg;
  std::string _heroid;
  std::string _heroname;

  uint32_t _isSetFlag[1];

};

class CSSendMail_0x23: public ::ssu::Object {
 public:
  virtual ~CSSendMail_0x23() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Recname() const { return _recname; }
  inline void SetRecname(const std::string& val__) { _recname = val__; }
  inline std::string& MutableRecname() { return _recname; }

  inline const std::string& Title() const { return _title; }
  inline void SetTitle(const std::string& val__) { _title = val__; }
  inline std::string& MutableTitle() { return _title; }

  inline const std::string& Content() const { return _content; }
  inline void SetContent(const std::string& val__) { _content = val__; }
  inline std::string& MutableContent() { return _content; }

 protected:
  std::string _recname;
  std::string _title;
  std::string _content;

};

class CSReadMail_0x24: public ::ssu::Object {
 public:
  inline CSReadMail_0x24(): _mailid(0) { }

  virtual ~CSReadMail_0x24() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Mailid() const { return _mailid; }
  inline void SetMailid(uint32_t val__) { _mailid = val__; }

 protected:
  uint32_t _mailid;

};

class CSReadMail_0x25: public ::ssu::Object {
 public:
  inline CSReadMail_0x25(): _mailid(0) { }

  virtual ~CSReadMail_0x25() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Mailid() const { return _mailid; }
  inline void SetMailid(uint32_t val__) { _mailid = val__; }

 protected:
  uint32_t _mailid;

};

class CSGetMailList_0x26: public ::ssu::Object {
 public:
  virtual ~CSGetMailList_0x26() { }

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
