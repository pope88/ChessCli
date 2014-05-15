#ifndef _SSU_PACKETSSTOC_H_
#define _SSU_PACKETSSTOC_H_

#include <stdint.h>
#include "SsuObject.h"

namespace game {
namespace net {
namespace data {
namespace StoC {

enum cmd_svr
 {  cmd_register_svr = 1,
  cmd_userlogin_svr = 2,
  cmd_userinfo_svr = 3,
  cmd_newhero_svr = 4,
  cmd_heroload_svr = 5,
  cmd_heroinfo_svr = 6,
  cmd_userinfochange_svr = 7,
  cmd_itemlist_svr = 8,
  cmd_deleteitem_svr = 16,
  cmd_putonequip_svr = 19,
  cmd_putoffequip_svr = 20,
  cmd_accepttask_svr = 21,
  cmd_finishtask_svr = 22,
  cmd_updatetask_svr = 23,
  cmd_heroprop_svr = 24,
  cmd_extendpack_svr = 25,
  cmd_talk_svr = 34,
  cmd_sendmail_svr = 35,
  cmd_getmaillist_svr = 36,
};

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

 protected:
  uint32_t _result;
  uint32_t _userId;
  std::string _userName;
  uint32_t _vipLevel;
  uint32_t _banTime;

  uint32_t _isSetFlag[1];

};

class HeroInfo: public ::ssu::Object {
 public:
  inline HeroInfo(): _isMale(false), _level(0), _roleid(0), _job(0) { }

  virtual ~HeroInfo() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline bool IsMale() const { return _isMale; }
  inline void SetIsMale(bool val__) { _isMale = val__; }

  inline const std::string& Name() const { return _name; }
  inline void SetName(const std::string& val__) { _name = val__; }
  inline std::string& MutableName() { return _name; }

  inline uint32_t Level() const { return _level; }
  inline void SetLevel(uint32_t val__) { _level = val__; }

  inline uint32_t Roleid() const { return _roleid; }
  inline void SetRoleid(uint32_t val__) { _roleid = val__; }

  inline uint32_t Job() const { return _job; }
  inline void SetJob(uint32_t val__) { _job = val__; }

 protected:
  bool _isMale;
  std::string _name;
  uint32_t _level;
  uint32_t _roleid;
  uint32_t _job;

};

class SCUserInfo_0x03: public ::ssu::Object {
 public:
  inline SCUserInfo_0x03(): _gold(0), _totalTopup(0), _totalConsume(0) { }

  virtual ~SCUserInfo_0x03();
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

  inline const HeroInfo& Roles(size_t index__) const { return *_roles[index__]; }
  inline HeroInfo * NewRoles() { return new(std::nothrow) HeroInfo; }
  inline HeroInfo * AddRoles() { HeroInfo * val__ = new(std::nothrow) HeroInfo; if(val__ == NULL) return NULL; _roles.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<HeroInfo *>& MutableRoles() { return _roles; }
  inline size_t RolesSize() const { return _roles.Size(); }
  inline void ClearRoles() { for(::ssu::RepeatedObject<HeroInfo *>::iterator iter = _roles.begin(); iter != _roles.end(); ++ iter) { delete *iter; } _roles.Clear(); }
  inline void ReserveRoles(size_t size__) { if(_roles.Size() < size__) _roles.Reserve(size__); }

 protected:
  uint32_t _gold;
  uint32_t _totalTopup;
  uint32_t _totalConsume;
  ::ssu::RepeatedObject<HeroInfo *> _roles;

};

class SCNewHero_0x04: public ::ssu::Object {
 public:
  inline SCNewHero_0x04(): _result(0), _roleid(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCNewHero_0x04() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

  inline uint32_t Roleid() const { return _roleid; }
  inline void SetRoleid(uint32_t val__) { _roleid = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasRoleid() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  uint32_t _result;
  uint32_t _roleid;

  uint32_t _isSetFlag[1];

};

class SCHeroLoad_0x05: public ::ssu::Object {
 public:
  inline SCHeroLoad_0x05(): _result(0), _steps(0), _mapId(0), _mapX(0.0f), _mapY(0.0f)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCHeroLoad_0x05() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

  inline uint32_t Steps() const { return _steps; }
  inline void SetSteps(uint32_t val__) { _steps = val__; }

  inline uint32_t MapId() const { return _mapId; }
  inline void SetMapId(uint32_t val__) { _mapId = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasMapId() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline float MapX() const { return _mapX; }
  inline void SetMapX(float val__) { _mapX = val__; _isSetFlag[0] |= 0x02; }
  inline bool HasMapX() const { return (_isSetFlag[0] & 0x02) > 0; }

  inline float MapY() const { return _mapY; }
  inline void SetMapY(float val__) { _mapY = val__; _isSetFlag[0] |= 0x04; }
  inline bool HasMapY() const { return (_isSetFlag[0] & 0x04) > 0; }

 protected:
  uint32_t _result;
  uint32_t _steps;
  uint32_t _mapId;
  float _mapX;
  float _mapY;

  uint32_t _isSetFlag[1];

};

class SCHeroInfos_0x06: public ::ssu::Object {
 public:
  inline SCHeroInfos_0x06(): _goldB(0), _silver(0), _energy(0), _prestige(0), _level(0), _experience(0), _packSize(0), _pets(0), _wallow(0), _wallowTime(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCHeroInfos_0x06() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t GoldB() const { return _goldB; }
  inline void SetGoldB(uint32_t val__) { _goldB = val__; }

  inline uint32_t Silver() const { return _silver; }
  inline void SetSilver(uint32_t val__) { _silver = val__; }

  inline uint32_t Energy() const { return _energy; }
  inline void SetEnergy(uint32_t val__) { _energy = val__; }

  inline uint32_t Prestige() const { return _prestige; }
  inline void SetPrestige(uint32_t val__) { _prestige = val__; }

  inline uint32_t Level() const { return _level; }
  inline void SetLevel(uint32_t val__) { _level = val__; }

  inline uint32_t Experience() const { return _experience; }
  inline void SetExperience(uint32_t val__) { _experience = val__; }

  inline uint32_t PackSize() const { return _packSize; }
  inline void SetPackSize(uint32_t val__) { _packSize = val__; }

  inline uint32_t Pets() const { return _pets; }
  inline void SetPets(uint32_t val__) { _pets = val__; }

  inline uint32_t Wallow() const { return _wallow; }
  inline void SetWallow(uint32_t val__) { _wallow = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasWallow() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline uint32_t WallowTime() const { return _wallowTime; }
  inline void SetWallowTime(uint32_t val__) { _wallowTime = val__; _isSetFlag[0] |= 0x02; }
  inline bool HasWallowTime() const { return (_isSetFlag[0] & 0x02) > 0; }

 protected:
  uint32_t _goldB;
  uint32_t _silver;
  uint32_t _energy;
  uint32_t _prestige;
  uint32_t _level;
  uint32_t _experience;
  uint32_t _packSize;
  uint32_t _pets;
  uint32_t _wallow;
  uint32_t _wallowTime;

  uint32_t _isSetFlag[1];

};

class SCPlayerInfoChange_0x7: public ::ssu::Object {
 public:
  inline SCPlayerInfoChange_0x7(): _totalTopup(0), _totalConsume(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCPlayerInfoChange_0x7() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t TotalTopup() const { return _totalTopup; }
  inline void SetTotalTopup(uint32_t val__) { _totalTopup = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasTotalTopup() const { return (_isSetFlag[0] & 0x01) > 0; }

  inline uint32_t TotalConsume() const { return _totalConsume; }
  inline void SetTotalConsume(uint32_t val__) { _totalConsume = val__; _isSetFlag[0] |= 0x02; }
  inline bool HasTotalConsume() const { return (_isSetFlag[0] & 0x02) > 0; }

 protected:
  uint32_t _totalTopup;
  uint32_t _totalConsume;

  uint32_t _isSetFlag[1];

};

class SCEquipAttribute: public ::ssu::Object {
 public:
  inline SCEquipAttribute(): _equipId(0), _position(0), _isBand(false)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCEquipAttribute() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Keyid() const { return _keyid; }
  inline void SetKeyid(const std::string& val__) { _keyid = val__; }
  inline std::string& MutableKeyid() { return _keyid; }

  inline uint32_t EquipId() const { return _equipId; }
  inline void SetEquipId(uint32_t val__) { _equipId = val__; }

  inline uint32_t ExtraData(size_t index__) const { return _extraData[index__]; }
  inline void AddExtraData(uint32_t val__) { _extraData.Add(val__); }
  inline void SetExtraData(size_t index__, uint32_t val__) { _extraData[index__] = val__; }
  inline ::ssu::RepeatedObject<uint32_t>& MutableExtraData() { return _extraData; }
  inline size_t ExtraDataSize() const { return _extraData.Size(); }
  inline void ClearExtraData() { _extraData.Clear(); }
  inline void ReserveExtraData(size_t size__) { if(_extraData.Size() < size__) _extraData.Reserve(size__); }

  inline uint32_t Position() const { return _position; }
  inline void SetPosition(uint32_t val__) { _position = val__; }

  inline bool IsBand() const { return _isBand; }
  inline void SetIsBand(bool val__) { _isBand = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasIsBand() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  std::string _keyid;
  uint32_t _equipId;
  ::ssu::RepeatedObject<uint32_t> _extraData;
  uint32_t _position;
  bool _isBand;

  uint32_t _isSetFlag[1];

};

class SCItem: public ::ssu::Object {
 public:
  inline SCItem(): _itemId(0), _icount(0), _position(0), _isBand(false)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCItem() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Keyid() const { return _keyid; }
  inline void SetKeyid(const std::string& val__) { _keyid = val__; }
  inline std::string& MutableKeyid() { return _keyid; }

  inline uint32_t ItemId() const { return _itemId; }
  inline void SetItemId(uint32_t val__) { _itemId = val__; }

  inline uint32_t Icount() const { return _icount; }
  inline void SetIcount(uint32_t val__) { _icount = val__; }

  inline uint32_t Position() const { return _position; }
  inline void SetPosition(uint32_t val__) { _position = val__; }

  inline bool IsBand() const { return _isBand; }
  inline void SetIsBand(bool val__) { _isBand = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasIsBand() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  std::string _keyid;
  uint32_t _itemId;
  uint32_t _icount;
  uint32_t _position;
  bool _isBand;

  uint32_t _isSetFlag[1];

};

class SCItemList_0x08: public ::ssu::Object {
 public:
  inline SCItemList_0x08(): _listType(0), _hint(0) { }

  virtual ~SCItemList_0x08();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t ListType() const { return _listType; }
  inline void SetListType(uint32_t val__) { _listType = val__; }

  inline const SCItem& Items(size_t index__) const { return *_items[index__]; }
  inline SCItem * NewItems() { return new(std::nothrow) SCItem; }
  inline SCItem * AddItems() { SCItem * val__ = new(std::nothrow) SCItem; if(val__ == NULL) return NULL; _items.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<SCItem *>& MutableItems() { return _items; }
  inline size_t ItemsSize() const { return _items.Size(); }
  inline void ClearItems() { for(::ssu::RepeatedObject<SCItem *>::iterator iter = _items.begin(); iter != _items.end(); ++ iter) { delete *iter; } _items.Clear(); }
  inline void ReserveItems(size_t size__) { if(_items.Size() < size__) _items.Reserve(size__); }

  inline const SCEquipAttribute& Equipments(size_t index__) const { return *_equipments[index__]; }
  inline SCEquipAttribute * NewEquipments() { return new(std::nothrow) SCEquipAttribute; }
  inline SCEquipAttribute * AddEquipments() { SCEquipAttribute * val__ = new(std::nothrow) SCEquipAttribute; if(val__ == NULL) return NULL; _equipments.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<SCEquipAttribute *>& MutableEquipments() { return _equipments; }
  inline size_t EquipmentsSize() const { return _equipments.Size(); }
  inline void ClearEquipments() { for(::ssu::RepeatedObject<SCEquipAttribute *>::iterator iter = _equipments.begin(); iter != _equipments.end(); ++ iter) { delete *iter; } _equipments.Clear(); }
  inline void ReserveEquipments(size_t size__) { if(_equipments.Size() < size__) _equipments.Reserve(size__); }

  inline uint32_t Hint() const { return _hint; }
  inline void SetHint(uint32_t val__) { _hint = val__; }

 protected:
  uint32_t _listType;
  ::ssu::RepeatedObject<SCItem *> _items;
  ::ssu::RepeatedObject<SCEquipAttribute *> _equipments;
  uint32_t _hint;

};

class dlitems: public ::ssu::Object {
 public:
  inline dlitems(): _num(0) { }

  virtual ~dlitems() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Keyid() const { return _keyid; }
  inline void SetKeyid(const std::string& val__) { _keyid = val__; }
  inline std::string& MutableKeyid() { return _keyid; }

  inline uint32_t Num() const { return _num; }
  inline void SetNum(uint32_t val__) { _num = val__; }

 protected:
  std::string _keyid;
  uint32_t _num;

};

class SCDeleteItems_0x10: public ::ssu::Object {
 public:
  virtual ~SCDeleteItems_0x10();
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

class SCPutOnEquip_0x13: public ::ssu::Object {
 public:
  inline SCPutOnEquip_0x13(): _res(0) { }

  virtual ~SCPutOnEquip_0x13() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Res() const { return _res; }
  inline void SetRes(uint32_t val__) { _res = val__; }

  inline const std::string& Key() const { return _key; }
  inline void SetKey(const std::string& val__) { _key = val__; }
  inline std::string& MutableKey() { return _key; }

 protected:
  uint32_t _res;
  std::string _key;

};

class SCPutOffEquip_0x14: public ::ssu::Object {
 public:
  inline SCPutOffEquip_0x14(): _res(0) { }

  virtual ~SCPutOffEquip_0x14() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Res() const { return _res; }
  inline void SetRes(uint32_t val__) { _res = val__; }

  inline const std::string& Key() const { return _key; }
  inline void SetKey(const std::string& val__) { _key = val__; }
  inline std::string& MutableKey() { return _key; }

 protected:
  uint32_t _res;
  std::string _key;

};

class SCAcceptTask_0x15: public ::ssu::Object {
 public:
  inline SCAcceptTask_0x15(): _taskid(0) { }

  virtual ~SCAcceptTask_0x15() { }

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

class SCSubmitTask_0x16: public ::ssu::Object {
 public:
  inline SCSubmitTask_0x16(): _taskid(0) { }

  virtual ~SCSubmitTask_0x16() { }

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

class SCUpdateTask_0x17: public ::ssu::Object {
 public:
  inline SCUpdateTask_0x17(): _taskid(0), _fval(0), _fva2(0), _fva3(0), _fva4(0), _fva5(0) { }

  virtual ~SCUpdateTask_0x17() { }

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

class SCHeroProp_0x18: public ::ssu::Object {
 public:
  inline SCHeroProp_0x18(): _heroid(0), _maxHp(0), _attck(0), _strength(0), _agility(0) { }

  virtual ~SCHeroProp_0x18() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Heroid() const { return _heroid; }
  inline void SetHeroid(uint32_t val__) { _heroid = val__; }

  inline uint32_t MaxHp() const { return _maxHp; }
  inline void SetMaxHp(uint32_t val__) { _maxHp = val__; }

  inline uint32_t Attck() const { return _attck; }
  inline void SetAttck(uint32_t val__) { _attck = val__; }

  inline uint32_t Strength() const { return _strength; }
  inline void SetStrength(uint32_t val__) { _strength = val__; }

  inline uint32_t Agility() const { return _agility; }
  inline void SetAgility(uint32_t val__) { _agility = val__; }

 protected:
  uint32_t _heroid;
  uint32_t _maxHp;
  uint32_t _attck;
  uint32_t _strength;
  uint32_t _agility;

};

class SCExtendPack_0x19: public ::ssu::Object {
 public:
  inline SCExtendPack_0x19(): _extendRes(0) { }

  virtual ~SCExtendPack_0x19() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t ExtendRes() const { return _extendRes; }
  inline void SetExtendRes(uint32_t val__) { _extendRes = val__; }

 protected:
  uint32_t _extendRes;

};

class SCTalk_0x22: public ::ssu::Object {
 public:
  inline SCTalk_0x22(): _mtype(0), _server(0)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~SCTalk_0x22() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Mtype() const { return _mtype; }
  inline void SetMtype(uint32_t val__) { _mtype = val__; }

  inline const std::string& Sname() const { return _sname; }
  inline void SetSname(const std::string& val__) { _sname = val__; }
  inline std::string& MutableSname() { return _sname; }

  inline const std::string& Msg() const { return _msg; }
  inline void SetMsg(const std::string& val__) { _msg = val__; }
  inline std::string& MutableMsg() { return _msg; }

  inline uint32_t Server() const { return _server; }
  inline void SetServer(uint32_t val__) { _server = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasServer() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  uint32_t _mtype;
  std::string _sname;
  std::string _msg;
  uint32_t _server;

  uint32_t _isSetFlag[1];

};

class SCSendMail_0x23: public ::ssu::Object {
 public:
  inline SCSendMail_0x23(): _result(0) { }

  virtual ~SCSendMail_0x23() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

 protected:
  uint32_t _result;

};

class mailitem: public ::ssu::Object {
 public:
  inline mailitem(): _itemid(0), _count(0) { }

  virtual ~mailitem() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Itemid() const { return _itemid; }
  inline void SetItemid(uint32_t val__) { _itemid = val__; }

  inline uint32_t Count() const { return _count; }
  inline void SetCount(uint32_t val__) { _count = val__; }

 protected:
  uint32_t _itemid;
  uint32_t _count;

};

class mailinfo: public ::ssu::Object {
 public:
  inline mailinfo(): _utime(0), _silver(0), _gold(0), _mailtype(0), _isread(false), _isgot(false)
  { memset(_isSetFlag, 0, sizeof(_isSetFlag)); }

  virtual ~mailinfo();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const std::string& Mailid() const { return _mailid; }
  inline void SetMailid(const std::string& val__) { _mailid = val__; }
  inline std::string& MutableMailid() { return _mailid; }

  inline uint32_t Utime() const { return _utime; }
  inline void SetUtime(uint32_t val__) { _utime = val__; }

  inline const std::string& Sendname() const { return _sendname; }
  inline void SetSendname(const std::string& val__) { _sendname = val__; }
  inline std::string& MutableSendname() { return _sendname; }

  inline const std::string& Title() const { return _title; }
  inline void SetTitle(const std::string& val__) { _title = val__; }
  inline std::string& MutableTitle() { return _title; }

  inline const std::string& Content() const { return _content; }
  inline void SetContent(const std::string& val__) { _content = val__; }
  inline std::string& MutableContent() { return _content; }

  inline uint32_t Silver() const { return _silver; }
  inline void SetSilver(uint32_t val__) { _silver = val__; }

  inline uint32_t Gold() const { return _gold; }
  inline void SetGold(uint32_t val__) { _gold = val__; }

  inline const mailitem& Mitem(size_t index__) const { return *_mitem[index__]; }
  inline mailitem * NewMitem() { return new(std::nothrow) mailitem; }
  inline mailitem * AddMitem() { mailitem * val__ = new(std::nothrow) mailitem; if(val__ == NULL) return NULL; _mitem.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<mailitem *>& MutableMitem() { return _mitem; }
  inline size_t MitemSize() const { return _mitem.Size(); }
  inline void ClearMitem() { for(::ssu::RepeatedObject<mailitem *>::iterator iter = _mitem.begin(); iter != _mitem.end(); ++ iter) { delete *iter; } _mitem.Clear(); }
  inline void ReserveMitem(size_t size__) { if(_mitem.Size() < size__) _mitem.Reserve(size__); }

  inline uint32_t Mailtype() const { return _mailtype; }
  inline void SetMailtype(uint32_t val__) { _mailtype = val__; }

  inline bool Isread() const { return _isread; }
  inline void SetIsread(bool val__) { _isread = val__; }

  inline bool Isgot() const { return _isgot; }
  inline void SetIsgot(bool val__) { _isgot = val__; _isSetFlag[0] |= 0x01; }
  inline bool HasIsgot() const { return (_isSetFlag[0] & 0x01) > 0; }

 protected:
  std::string _mailid;
  uint32_t _utime;
  std::string _sendname;
  std::string _title;
  std::string _content;
  uint32_t _silver;
  uint32_t _gold;
  ::ssu::RepeatedObject<mailitem *> _mitem;
  uint32_t _mailtype;
  bool _isread;
  bool _isgot;

  uint32_t _isSetFlag[1];

};

class SCMailList_0x24: public ::ssu::Object {
 public:
  virtual ~SCMailList_0x24();
 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline const mailinfo& Maillist(size_t index__) const { return *_maillist[index__]; }
  inline mailinfo * NewMaillist() { return new(std::nothrow) mailinfo; }
  inline mailinfo * AddMaillist() { mailinfo * val__ = new(std::nothrow) mailinfo; if(val__ == NULL) return NULL; _maillist.Add(val__); return val__; }
  inline ::ssu::RepeatedObject<mailinfo *>& MutableMaillist() { return _maillist; }
  inline size_t MaillistSize() const { return _maillist.Size(); }
  inline void ClearMaillist() { for(::ssu::RepeatedObject<mailinfo *>::iterator iter = _maillist.begin(); iter != _maillist.end(); ++ iter) { delete *iter; } _maillist.Clear(); }
  inline void ReserveMaillist(size_t size__) { if(_maillist.Size() < size__) _maillist.Reserve(size__); }

 protected:
  ::ssu::RepeatedObject<mailinfo *> _maillist;

};

class SCReadMail_0x25: public ::ssu::Object {
 public:
  inline SCReadMail_0x25(): _result(0) { }

  virtual ~SCReadMail_0x25() { }

 public:
  virtual uint8_t * PackBuffer(uint8_t * buf);
  virtual bool UnpackBuffer(const uint8_t *& buf, size_t& leftSize);
  virtual size_t Size() const;

 public:
  inline uint32_t Result() const { return _result; }
  inline void SetResult(uint32_t val__) { _result = val__; }

 protected:
  uint32_t _result;

};

}
}
}
}

#endif // _SSU_PACKETSSTOC_H_
