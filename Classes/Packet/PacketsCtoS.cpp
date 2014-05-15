#include "PacketsCtoS.h"

namespace game {
namespace net {
namespace data {
namespace CtoS {

uint8_t * HeadPack::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackFixed32Tag(buf, 1, _cmdtype);
  buf = ::ssu::Utils::PackFixed32Tag(buf, 2, _cmdlength);
  buf = ::ssu::Utils::PackFixed32Tag(buf, 3, _cliid);
  buf = ::ssu::Utils::PackFixed32Tag(buf, 4, _svrid);
  return buf;
}

bool HeadPack::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 5 || !::ssu::Utils::UnpackFixed32(buf, leftSize, _cmdtype)) return false;
      break;
     case 2:
      if(type_ != 5 || !::ssu::Utils::UnpackFixed32(buf, leftSize, _cmdlength)) return false;
      break;
     case 3:
      if(type_ != 5 || !::ssu::Utils::UnpackFixed32(buf, leftSize, _cliid)) return false;
      break;
     case 4:
      if(type_ != 5 || !::ssu::Utils::UnpackFixed32(buf, leftSize, _svrid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t HeadPack::Size() const {
  return 1 + ::ssu::Utils::SizeFixed32(_cmdtype) + 1 + ::ssu::Utils::SizeFixed32(_cmdlength) + 1 + ::ssu::Utils::SizeFixed32(_cliid) + 1 + ::ssu::Utils::SizeFixed32(_svrid);
}

uint8_t * CSUserLogout_0xFFFF::PackBuffer(uint8_t * buf) {
  return buf;
}

bool CSUserLogout_0xFFFF::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t CSUserLogout_0xFFFF::Size() const {
  return 0;
}

uint8_t * CSUserRegister_0x01::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _username);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _pwd);
  return buf;
}

bool CSUserRegister_0x01::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _username)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _pwd)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSUserRegister_0x01::Size() const {
  return 1 + ::ssu::Utils::SizeString(_username) + 1 + ::ssu::Utils::SizeString(_pwd);
}

uint8_t * CSUserLogin_0x02::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _username);
  if(HasPwd()) buf = ::ssu::Utils::PackStringTag(buf, 2, _pwd);
  if(HasWallow()) buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _wallow);
  return buf;
}

bool CSUserLogin_0x02::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _username)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _pwd)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _wallow)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSUserLogin_0x02::Size() const {
  return 1 + ::ssu::Utils::SizeString(_username) + (HasPwd() ? (1 + ::ssu::Utils::SizeString(_pwd)) : 0) + (HasWallow() ? (1 + ::ssu::Utils::SizeUInt32(_wallow)) : 0);
}

uint8_t * CSUserInfo_0x03::PackBuffer(uint8_t * buf) {
  return buf;
}

bool CSUserInfo_0x03::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t CSUserInfo_0x03::Size() const {
  return 0;
}

uint8_t * CSNewHero_0x04::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackBoolTag(buf, 1, _ismale);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _name);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _job);
  return buf;
}

bool CSNewHero_0x04::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _ismale)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _name)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _job)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSNewHero_0x04::Size() const {
  return 1 + ::ssu::Utils::SizeBool(_ismale) + 1 + ::ssu::Utils::SizeString(_name) + 1 + ::ssu::Utils::SizeUInt32(_job);
}

uint8_t * CSHeroLoad_0x05::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _heroid);
  return buf;
}

bool CSHeroLoad_0x05::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _heroid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSHeroLoad_0x05::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_heroid);
}

uint8_t * CSHeroInfos_0x06::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _noid);
  return buf;
}

bool CSHeroInfos_0x06::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _noid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSHeroInfos_0x06::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_noid);
}

uint8_t * CSAskItemsInfo_0x08::PackBuffer(uint8_t * buf) {
  return buf;
}

bool CSAskItemsInfo_0x08::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t CSAskItemsInfo_0x08::Size() const {
  return 0;
}

uint8_t * CSEquipAttribute::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _equipId);
  if(HasPosition()) buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _position);
  if(HasIsBand()) buf = ::ssu::Utils::PackBoolTag(buf, 3, _isBand);
  return buf;
}

bool CSEquipAttribute::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _equipId)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _position)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isBand)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSEquipAttribute::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_equipId) + (HasPosition() ? (1 + ::ssu::Utils::SizeUInt32(_position)) : 0) + (HasIsBand() ? (1 + ::ssu::Utils::SizeBool(_isBand)) : 0);
}

uint8_t * CSItem::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _itemId);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _icount);
  if(HasIsBand()) buf = ::ssu::Utils::PackBoolTag(buf, 3, _isBand);
  return buf;
}

bool CSItem::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _itemId)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _icount)) return false;
      break;
     case 3:
      if(type_ != 0 || !::ssu::Utils::UnpackBool(buf, leftSize, _isBand)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSItem::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_itemId) + 1 + ::ssu::Utils::SizeUInt32(_icount) + (HasIsBand() ? (1 + ::ssu::Utils::SizeBool(_isBand)) : 0);
}

CSUseItem_0x09::~CSUseItem_0x09() {
  for(::ssu::RepeatedObject<CSItem *>::iterator iter = _items.begin(); iter != _items.end(); ++ iter) { delete *iter; } _items.Clear();
}

uint8_t * CSUseItem_0x09::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackRepeatedTag(buf, 1, _items, ::ssu::Utils::PackObjectTag<CSItem>);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _heroId);
  return buf;
}

bool CSUseItem_0x09::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackRepeatedPtr(buf, leftSize, _items, ::ssu::Utils::UnpackObjectPtr<CSItem>)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _heroId)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSUseItem_0x09::Size() const {
  return 1 * _items.Size() + ::ssu::Utils::SizeRepeated(_items, ::ssu::Utils::SizeObject<CSItem>) + 1 + ::ssu::Utils::SizeUInt32(_heroId);
}

uint8_t * dlitems::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _itemid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _num);
  return buf;
}

bool dlitems::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _itemid)) return false;
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
  return 1 + ::ssu::Utils::SizeUInt32(_itemid) + 1 + ::ssu::Utils::SizeUInt32(_num);
}

CSDeleteItems_0x10::~CSDeleteItems_0x10() {
  for(::ssu::RepeatedObject<dlitems *>::iterator iter = _ditems.begin(); iter != _ditems.end(); ++ iter) { delete *iter; } _ditems.Clear();
}

uint8_t * CSDeleteItems_0x10::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackRepeatedTag(buf, 1, _ditems, ::ssu::Utils::PackObjectTag<dlitems>);
  return buf;
}

bool CSDeleteItems_0x10::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
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

size_t CSDeleteItems_0x10::Size() const {
  return 1 * _ditems.Size() + ::ssu::Utils::SizeRepeated(_ditems, ::ssu::Utils::SizeObject<dlitems>);
}

uint8_t * CSPutOnEquip_0x13::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _key);
  return buf;
}

bool CSPutOnEquip_0x13::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _key)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSPutOnEquip_0x13::Size() const {
  return 1 + ::ssu::Utils::SizeString(_key);
}

uint8_t * CSPutOffEquip_0x14::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _key);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _pos);
  return buf;
}

bool CSPutOffEquip_0x14::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _key)) return false;
      break;
     case 2:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _pos)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSPutOffEquip_0x14::Size() const {
  return 1 + ::ssu::Utils::SizeString(_key) + 1 + ::ssu::Utils::SizeUInt32(_pos);
}

uint8_t * CSAcceptTask_0x15::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  return buf;
}

bool CSAcceptTask_0x15::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
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

size_t CSAcceptTask_0x15::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid);
}

uint8_t * CSSubmitTask_0x16::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  return buf;
}

bool CSSubmitTask_0x16::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
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

size_t CSSubmitTask_0x16::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid);
}

uint8_t * CSUpdateTask_0x17::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _taskid);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 2, _fval);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 3, _fva2);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 4, _fva3);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 5, _fva4);
  buf = ::ssu::Utils::PackUInt32Tag(buf, 6, _fva5);
  return buf;
}

bool CSUpdateTask_0x17::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
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

size_t CSUpdateTask_0x17::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_taskid) + 1 + ::ssu::Utils::SizeUInt32(_fval) + 1 + ::ssu::Utils::SizeUInt32(_fva2) + 1 + ::ssu::Utils::SizeUInt32(_fva3) + 1 + ::ssu::Utils::SizeUInt32(_fva4) + 1 + ::ssu::Utils::SizeUInt32(_fva5);
}

uint8_t * CSHeroProp_0x18::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _heroid);
  return buf;
}

bool CSHeroProp_0x18::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _heroid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSHeroProp_0x18::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_heroid);
}

uint8_t * CSExtendPack_0x19::PackBuffer(uint8_t * buf) {
  return buf;
}

bool CSExtendPack_0x19::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t CSExtendPack_0x19::Size() const {
  return 0;
}

uint8_t * CSMaterialMerge_0x20::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _itemId);
  return buf;
}

bool CSMaterialMerge_0x20::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _itemId)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSMaterialMerge_0x20::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_itemId);
}

uint8_t * CSEquipMerge_0x21::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _equipId);
  return buf;
}

bool CSEquipMerge_0x21::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _equipId)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSEquipMerge_0x21::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_equipId);
}

uint8_t * CSTalk_0x22::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _mtype);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _msg);
  if(HasHeroid()) buf = ::ssu::Utils::PackStringTag(buf, 3, _heroid);
  if(HasHeroname()) buf = ::ssu::Utils::PackStringTag(buf, 4, _heroname);
  return buf;
}

bool CSTalk_0x22::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mtype)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _msg)) return false;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _heroid)) return false;
      _isSetFlag[0] |= 0x01;
      break;
     case 4:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _heroname)) return false;
      _isSetFlag[0] |= 0x02;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSTalk_0x22::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_mtype) + 1 + ::ssu::Utils::SizeString(_msg) + (HasHeroid() ? (1 + ::ssu::Utils::SizeString(_heroid)) : 0) + (HasHeroname() ? (1 + ::ssu::Utils::SizeString(_heroname)) : 0);
}

uint8_t * CSSendMail_0x23::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackStringTag(buf, 1, _recname);
  buf = ::ssu::Utils::PackStringTag(buf, 2, _title);
  buf = ::ssu::Utils::PackStringTag(buf, 3, _content);
  return buf;
}

bool CSSendMail_0x23::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _recname)) return false;
      break;
     case 2:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _title)) return false;
      break;
     case 3:
      if(type_ != 2 || !::ssu::Utils::UnpackString(buf, leftSize, _content)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSSendMail_0x23::Size() const {
  return 1 + ::ssu::Utils::SizeString(_recname) + 1 + ::ssu::Utils::SizeString(_title) + 1 + ::ssu::Utils::SizeString(_content);
}

uint8_t * CSReadMail_0x24::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _mailid);
  return buf;
}

bool CSReadMail_0x24::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mailid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSReadMail_0x24::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_mailid);
}

uint8_t * CSReadMail_0x25::PackBuffer(uint8_t * buf) {
  buf = ::ssu::Utils::PackUInt32Tag(buf, 1, _mailid);
  return buf;
}

bool CSReadMail_0x25::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  uint32_t tag_; uint8_t type_;
  while(leftSize > 0) {
    if(!::ssu::Utils::UnpackTag(buf, leftSize, tag_, type_)) return false;
    switch(tag_) {
     case 1:
      if(type_ != 0 || !::ssu::Utils::UnpackUInt32(buf, leftSize, _mailid)) return false;
      break;
     default: break;
    }
  }
  return true;
}

size_t CSReadMail_0x25::Size() const {
  return 1 + ::ssu::Utils::SizeUInt32(_mailid);
}

uint8_t * CSGetMailList_0x26::PackBuffer(uint8_t * buf) {
  return buf;
}

bool CSGetMailList_0x26::UnpackBuffer(const uint8_t *& buf, size_t& leftSize) {
  return true;
}

size_t CSGetMailList_0x26::Size() const {
  return 0;
}

}
}
}
}
