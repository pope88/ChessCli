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
  buf = ::ssu::Utils::PackRepeatedPackedTag(buf, 6, _steps, ::ssu::Utils::PackUInt32, ::ssu::Utils::SizeUInt32);
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
     case 6:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPacked(buf, leftSize, _steps, ::ssu::Utils::UnpackUInt32)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserLogin_0x02::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_result) + (HasUserId() ? (1 + ::ssu::Utils::SizeUInt32(_userId)) : 0) + (HasUserName() ? (1 + ::ssu::Utils::SizeString(_userName)) : 0) + (HasVipLevel() ? (1 + ::ssu::Utils::SizeUInt32(_vipLevel)) : 0) + (HasBanTime() ? (1 + ::ssu::Utils::SizeUInt32(_banTime)) : 0) + 1 + ::ssu::Utils::SizeRepeatedPacked(_steps, ::ssu::Utils::SizeUInt32);
}

uint8_t * SCUserInfo_0x03::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _gold);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _totalTopup);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _totalConsume);
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
     default: break;
    }
  }
  return true;
}

size_t SCUserInfo_0x03::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_gold) + 1 + ::ssu::Utils::SizeUInt32(_totalTopup) + 1 + ::ssu::Utils::SizeUInt32(_totalConsume);
}

uint8_t * RoomInfo::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _roomId);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _palyerNum);
  return buf;
}

bool RoomInfo::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _roomId)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _palyerNum)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t RoomInfo::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_roomId) + 1 + ::ssu::Utils::SizeUInt32(_palyerNum);
}

SCUserRoomList_0x04::~SCUserRoomList_0x04() {
  for(::ssu::RepeatedObject<RoomInfo *>::iterator iter = _rmlist.begin(); iter != _rmlist.end(); ++ iter) { delete *iter; } _rmlist.Clear();
}

uint8_t * SCUserRoomList_0x04::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackRepeatedTag(buf, 1, _rmlist, ::ssu::Utils::PackObjectTag<RoomInfo>);
  return buf;
}

bool SCUserRoomList_0x04::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _rmlist, ::ssu::Utils::UnpackObjectPtr<RoomInfo>)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserRoomList_0x04::Size() const {
  return 1 * _rmlist.Size() + ::ssu::Utils::SizeRepeated(_rmlist, ::ssu::Utils::SizeObject<RoomInfo>);
}

uint8_t * SCUserRoomInfo_0x05::PackBuffer(uint8_t * buf) {
  return buf;
}

bool SCUserRoomInfo_0x05::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t SCUserRoomInfo_0x05::Size() const {
  return 0;
}

uint8_t * SCUserEnterRoom_0x06::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _res);
  return buf;
}

bool SCUserEnterRoom_0x06::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _res)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t SCUserEnterRoom_0x06::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_res);
}

}
}
}
}
