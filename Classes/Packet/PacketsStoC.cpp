#include "PacketsStoC.h"

namespace game {
namespace net {
namespace data {
namespace StoC {

uint8_t * SCUserRegister_0x01::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  if(HasUserId()) buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _userId);
  return buf;
}

bool SCUserRegister_0x01::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _userId)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserRegister_0x01::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result) + (HasUserId() ? (1 + ::ssu::Utils::SizeUInt32(_userId)) : 0);
}

uint8_t * SCUserLogin_0x02::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  if(HasUserId()) buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _userId);
  if(HasUserName()) buf = ::ssu::Utils::PackStringTag(buf, 3, _userName);
  if(HasVipLevel()) buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _vipLevel);
  if(HasBanTime()) buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _banTime);
  return buf;
}

bool SCUserLogin_0x02::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _userId)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _userName)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _vipLevel)) return false;
      _isSetFlag[0] |= 0x04;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _banTime)) return false;
      _isSetFlag[0] |= 0x08;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserLogin_0x02::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result) + (HasUserId() ? (1 + ::ssu::Utils::SizeUInt32(_userId)) : 0) + (HasUserName() ? (1 + ::ssu::Utils::SizeString(_userName)) : 0) + (HasVipLevel() ? (1 + ::ssu::Utils::SizeUInt32(_vipLevel)) : 0) + (HasBanTime() ? (1 + ::ssu::Utils::SizeUInt32(_banTime)) : 0);
}

uint8_t * HeroInfo::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackBoolTag(buf, 1, _isMale);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _name);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _level);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _roleid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _job);
  return buf;
}

bool HeroInfo::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isMale)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _name)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _level)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _roleid)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _job)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t HeroInfo::Size() const {
  return 1 + ::ssu::Utils::SizeBool(_isMale) + 1 + ::ssu::Utils::SizeString(_name) + 1 + ::ssu::Utils::SizeUInt32(_level) + 1 + ::ssu::Utils::SizeUInt32(_roleid) + 1 + ::ssu::Utils::SizeUInt32(_job);
}

SCUserInfo_0x03::~SCUserInfo_0x03() {
  for(::ssu::RepeatedObject<HeroInfo *>::iterator iter = _roles.begin(); iter != _roles.end(); ++ iter) { delete *iter; } _roles.Clear();
}

uint8_t * SCUserInfo_0x03::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _gold);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _totalTopup);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _totalConsume);
  buf = ::ssu::Utils::PackRepeatedTag(buf, 4, _roles, ::ssu::Utils::PackObjectTag<HeroInfo>);
  return buf;
}

bool SCUserInfo_0x03::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _gold)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _totalTopup)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _totalConsume)) return false;
      break;
     case 4:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _roles, ::ssu::Utils::UnpackObjectPtr<HeroInfo>)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserInfo_0x03::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_gold) + 1 + ::ssu::Utils::SizeUInt32(_totalTopup) + 1 + ::ssu::Utils::SizeUInt32(_totalConsume) + 1 * _roles.Size() + ::ssu::Utils::SizeRepeated(_roles, ::ssu::Utils::SizeObject<HeroInfo>);
}

uint8_t * SCNewHero_0x04::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  if(HasRoleid()) buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _roleid);
  return buf;
}

bool SCNewHero_0x04::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _roleid)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCNewHero_0x04::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result) + (HasRoleid() ? (1 + ::ssu::Utils::SizeUInt32(_roleid)) : 0);
}

uint8_t * SCHeroLoad_0x05::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _steps);
  if(HasMapId()) buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _mapId);
  if(HasMapX()) buf = ::ssu::Utils::PackFloatTag(buf, 4, _mapX);
  if(HasMapY()) buf = ::ssu::Utils::PackFloatTag(buf, 5, _mapY);
  return buf;
}

bool SCHeroLoad_0x05::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _steps)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mapId)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 4:
      if(type_ != 5 || !::ssu::Utils::UnpackFloat(buf, leftSize, _mapX)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     case 5:
      if(type_ != 5 || !::ssu::Utils::UnpackFloat(buf, leftSize, _mapY)) return false;
      _isSetFlag[0] |= 0x04;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCHeroLoad_0x05::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result) + 1 + ::ssu::Utils::SizeUInt32(_steps) + (HasMapId() ? (1 + ::ssu::Utils::SizeUInt32(_mapId)) : 0) + (HasMapX() ? (1 + ::ssu::Utils::SizeFloat(_mapX)) : 0) + (HasMapY() ? (1 + ::ssu::Utils::SizeFloat(_mapY)) : 0);
}

uint8_t * SCHeroInfos_0x06::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _goldB);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _silver);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _energy);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _prestige);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _level);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 6, _experience);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 7, _packSize);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 8, _pets);
  if(HasWallow()) buf = ::ssu::Utils::PackUInt32Tag(buf, 9, _wallow);
  if(HasWallowTime()) buf = ::ssu::Utils::PackUInt32Tag(buf, 10, _wallowTime);
  return buf;
}

bool SCHeroInfos_0x06::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _goldB)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _silver)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _energy)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _prestige)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _level)) return false;
      break;
     case 6:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _experience)) return false;
      break;
     case 7:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _packSize)) return false;
      break;
     case 8:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _pets)) return false;
      break;
     case 9:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _wallow)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 10:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _wallowTime)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCHeroInfos_0x06::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_goldB) + 1 + ::ssu::Utils::SizeUInt32(_silver) + 1 + ::ssu::Utils::SizeUInt32(_energy) + 1 + ::ssu::Utils::SizeUInt32(_prestige) + 1 + ::ssu::Utils::SizeUInt32(_level) + 1 + ::ssu::Utils::SizeUInt32(_experience) + 1 + ::ssu::Utils::SizeUInt32(_packSize) + 1 + ::ssu::Utils::SizeUInt32(_pets) + (HasWallow() ? (1 + ::ssu::Utils::SizeUInt32(_wallow)) : 0) + (HasWallowTime() ? (1 + ::ssu::Utils::SizeUInt32(_wallowTime)) : 0);
}

uint8_t * SCPlayerInfoChange_0x7::PackBuffer(uint8_t * buf) {
  if(HasTotalTopup()) buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _totalTopup);
  if(HasTotalConsume()) buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _totalConsume);
  return buf;
}

bool SCPlayerInfoChange_0x7::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _totalTopup)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _totalConsume)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCPlayerInfoChange_0x7::Size() const {
  return (HasTotalTopup() ? (1 + ::ssu::Utils::SizeUInt32(_totalTopup)) : 0) + (HasTotalConsume() ? (1 + ::ssu::Utils::SizeUInt32(_totalConsume)) : 0);
}

uint8_t * SCEquipAttribute::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _keyid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _equipId);
  buf = ::ssu::Utils::PackRepeatedTag(buf, 3, _extraData, ::ssu::Utils::PackUInt32Tag);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _position);
  if(HasIsBand()) buf = ::ssu::Utils::PackBoolTag(buf, 5, _isBand);
  return buf;
}

bool SCEquipAttribute::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _keyid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _equipId)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackRepeated(buf, leftSize, _extraData, ::ssu::Utils::UnpackUInt32)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _position)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isBand)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCEquipAttribute::Size() const {
  return 1 + ::ssu::Utils::SizeString(_keyid) + 1 + ::ssu::Utils::SizeUInt32(_equipId) + 1 * _extraData.Size() + ::ssu::Utils::SizeRepeated(_extraData, ::ssu::Utils::SizeUInt32) + 1 + ::ssu::Utils::SizeUInt32(_position) + (HasIsBand() ? (1 + ::ssu::Utils::SizeBool(_isBand)) : 0);
}

uint8_t * SCItem::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _keyid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _itemId);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _icount);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _position);
  if(HasIsBand()) buf = ::ssu::Utils::PackBoolTag(buf, 5, _isBand);
  return buf;
}

bool SCItem::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _keyid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _itemId)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _icount)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _position)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isBand)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCItem::Size() const {
  return 1 + ::ssu::Utils::SizeString(_keyid) + 1 + ::ssu::Utils::SizeUInt32(_itemId) + 1 + ::ssu::Utils::SizeUInt32(_icount) + 1 + ::ssu::Utils::SizeUInt32(_position) + (HasIsBand() ? (1 + ::ssu::Utils::SizeBool(_isBand)) : 0);
}

SCItemList_0x08::~SCItemList_0x08() {
  for(::ssu::RepeatedObject<SCItem *>::iterator iter = _items.begin(); iter != _items.end(); ++ iter) { delete *iter; } _items.Clear();
  for(::ssu::RepeatedObject<SCEquipAttribute *>::iterator iter = _equipments.begin(); iter != _equipments.end(); ++ iter) { delete *iter; } _equipments.Clear();
}

uint8_t * SCItemList_0x08::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _listType);
  buf = ::ssu::Utils::PackRepeatedTag(buf, 2, _items, ::ssu::Utils::PackObjectTag<SCItem>);
  buf = ::ssu::Utils::PackRepeatedTag(buf, 3, _equipments, ::ssu::Utils::PackObjectTag<SCEquipAttribute>);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _hint);
  return buf;
}

bool SCItemList_0x08::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _listType)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _items, ::ssu::Utils::UnpackObjectPtr<SCItem>)) return false;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _equipments, ::ssu::Utils::UnpackObjectPtr<SCEquipAttribute>)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _hint)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCItemList_0x08::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_listType) + 1 * _items.Size() + ::ssu::Utils::SizeRepeated(_items, ::ssu::Utils::SizeObject<SCItem>) + 1 * _equipments.Size() + ::ssu::Utils::SizeRepeated(_equipments, ::ssu::Utils::SizeObject<SCEquipAttribute>) + 1 + ::ssu::Utils::SizeUInt32(_hint);
}

uint8_t * dlitems::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _keyid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _num);
  return buf;
}

bool dlitems::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _keyid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _num)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t dlitems::Size() const {
  return 1 + ::ssu::Utils::SizeString(_keyid) + 1 + ::ssu::Utils::SizeUInt32(_num);
}

SCDeleteItems_0x10::~SCDeleteItems_0x10() {
  for(::ssu::RepeatedObject<dlitems *>::iterator iter = _ditems.begin(); iter != _ditems.end(); ++ iter) { delete *iter; } _ditems.Clear();
}

uint8_t * SCDeleteItems_0x10::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackRepeatedTag(buf, 1, _ditems, ::ssu::Utils::PackObjectTag<dlitems>);
  return buf;
}

bool SCDeleteItems_0x10::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _ditems, ::ssu::Utils::UnpackObjectPtr<dlitems>)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCDeleteItems_0x10::Size() const {
  return 1 * _ditems.Size() + ::ssu::Utils::SizeRepeated(_ditems, ::ssu::Utils::SizeObject<dlitems>);
}

uint8_t * SCPutOnEquip_0x13::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _res);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _key);
  return buf;
}

bool SCPutOnEquip_0x13::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _res)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _key)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCPutOnEquip_0x13::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_res) + 1 + ::ssu::Utils::SizeString(_key);
}

uint8_t * SCPutOffEquip_0x14::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _res);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _key);
  return buf;
}

bool SCPutOffEquip_0x14::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _res)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _key)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCPutOffEquip_0x14::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_res) + 1 + ::ssu::Utils::SizeString(_key);
}

uint8_t * SCAcceptTask_0x15::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  return buf;
}

bool SCAcceptTask_0x15::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _taskid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCAcceptTask_0x15::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid);
}

uint8_t * SCSubmitTask_0x16::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  return buf;
}

bool SCSubmitTask_0x16::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _taskid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCSubmitTask_0x16::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid);
}

uint8_t * SCUpdateTask_0x17::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _fval);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _fva2);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _fva3);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _fva4);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 6, _fva5);
  return buf;
}

bool SCUpdateTask_0x17::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _taskid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _fval)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _fva2)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _fva3)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _fva4)) return false;
      break;
     case 6:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _fva5)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUpdateTask_0x17::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid) + 1 + ::ssu::Utils::SizeUInt32(_fval) + 1 + ::ssu::Utils::SizeUInt32(_fva2) + 1 + ::ssu::Utils::SizeUInt32(_fva3) + 1 + ::ssu::Utils::SizeUInt32(_fva4) + 1 + ::ssu::Utils::SizeUInt32(_fva5);
}

uint8_t * SCHeroProp_0x18::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _heroid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _maxHp);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _attck);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _strength);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _agility);
  return buf;
}

bool SCHeroProp_0x18::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _heroid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _maxHp)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _attck)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _strength)) return false;
      break;
     case 5:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _agility)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCHeroProp_0x18::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_heroid) + 1 + ::ssu::Utils::SizeUInt32(_maxHp) + 1 + ::ssu::Utils::SizeUInt32(_attck) + 1 + ::ssu::Utils::SizeUInt32(_strength) + 1 + ::ssu::Utils::SizeUInt32(_agility);
}

uint8_t * SCExtendPack_0x19::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _extendRes);
  return buf;
}

bool SCExtendPack_0x19::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _extendRes)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCExtendPack_0x19::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_extendRes);
}

uint8_t * SCTalk_0x22::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _mtype);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _sname);
  buf = ::ssu::Utils::PackStringTag(buf, 3, _msg);
  if(HasServer()) buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _server);
  return buf;
}

bool SCTalk_0x22::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mtype)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _sname)) return false;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _msg)) return false;
      break;
     case 4:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _server)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCTalk_0x22::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_mtype) + 1 + ::ssu::Utils::SizeString(_sname) + 1 + ::ssu::Utils::SizeString(_msg) + (HasServer() ? (1 + ::ssu::Utils::SizeUInt32(_server)) : 0);
}

uint8_t * SCSendMail_0x23::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  return buf;
}

bool SCSendMail_0x23::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCSendMail_0x23::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result);
}

uint8_t * mailitem::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _itemid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _count);
  return buf;
}

bool mailitem::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _itemid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _count)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t mailitem::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_itemid) + 1 + ::ssu::Utils::SizeUInt32(_count);
}

mailinfo::~mailinfo() {
  for(::ssu::RepeatedObject<mailitem *>::iterator iter = _mitem.begin(); iter != _mitem.end(); ++ iter) { delete *iter; } _mitem.Clear();
}

uint8_t * mailinfo::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _mailid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _utime);
  buf = ::ssu::Utils::PackStringTag(buf, 3, _sendname);
  buf = ::ssu::Utils::PackStringTag(buf, 4, _title);
  buf = ::ssu::Utils::PackStringTag(buf, 5, _content);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 6, _silver);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 7, _gold);
  buf = ::ssu::Utils::PackRepeatedTag(buf, 8, _mitem, ::ssu::Utils::PackObjectTag<mailitem>);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 9, _mailtype);
  buf = ::ssu::Utils::PackBoolTag(buf, 10, _isread);
  if(HasIsgot()) buf = ::ssu::Utils::PackBoolTag(buf, 11, _isgot);
  return buf;
}

bool mailinfo::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _mailid)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _utime)) return false;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _sendname)) return false;
      break;
     case 4:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _title)) return false;
      break;
     case 5:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _content)) return false;
      break;
     case 6:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _silver)) return false;
      break;
     case 7:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _gold)) return false;
      break;
     case 8:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _mitem, ::ssu::Utils::UnpackObjectPtr<mailitem>)) return false;
      break;
     case 9:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mailtype)) return false;
      break;
     case 10:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isread)) return false;
      break;
     case 11:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isgot)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t mailinfo::Size() const {
  return 1 + ::ssu::Utils::SizeString(_mailid) + 1 + ::ssu::Utils::SizeUInt32(_utime) + 1 + ::ssu::Utils::SizeString(_sendname) + 1 + ::ssu::Utils::SizeString(_title) + 1 + ::ssu::Utils::SizeString(_content) + 1 + ::ssu::Utils::SizeUInt32(_silver) + 1 + ::ssu::Utils::SizeUInt32(_gold) + 1 * _mitem.Size() + ::ssu::Utils::SizeRepeated(_mitem, ::ssu::Utils::SizeObject<mailitem>) + 1 + ::ssu::Utils::SizeUInt32(_mailtype) + 1 + ::ssu::Utils::SizeBool(_isread) + (HasIsgot() ? (1 + ::ssu::Utils::SizeBool(_isgot)) : 0);
}

SCMailList_0x24::~SCMailList_0x24() {
  for(::ssu::RepeatedObject<mailinfo *>::iterator iter = _maillist.begin(); iter != _maillist.end(); ++ iter) { delete *iter; } _maillist.Clear();
}

uint8_t * SCMailList_0x24::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackRepeatedTag(buf, 1, _maillist, ::ssu::Utils::PackObjectTag<mailinfo>);
  return buf;
}

bool SCMailList_0x24::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _maillist, ::ssu::Utils::UnpackObjectPtr<mailinfo>)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCMailList_0x24::Size() const {
  return 1 * _maillist.Size() + ::ssu::Utils::SizeRepeated(_maillist, ::ssu::Utils::SizeObject<mailinfo>);
}

uint8_t * SCReadMail_0x25::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _result);
  return buf;
}

bool SCReadMail_0x25::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _result)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCReadMail_0x25::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result);
}

}
}
}
}
