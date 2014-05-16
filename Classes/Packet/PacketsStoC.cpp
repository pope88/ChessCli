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

uint8_t * SCUserRoomInfo_0x04::PackBuffer(uint8_t * buf) {
  return buf;
}

bool SCUserRoomInfo_0x04::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t SCUserRoomInfo_0x04::Size() const {
  return 0;
}

uint8_t * SCUserEnterRoom_0x05::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _res);
  return buf;
}

bool SCUserEnterRoom_0x05::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
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

size_t SCUserEnterRoom_0x05::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_res);
}

}
}
}
}
