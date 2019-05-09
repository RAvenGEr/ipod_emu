#ifndef IAP_STREAM_HPP
#define IAP_STREAM_HPP

#include "packet.hpp"
#include <iostream>

namespace iap {

constexpr byte StartByte{0x55};

class Stream {
public:
  Stream(std::iostream &device);

  Stream &operator<<(const Packet &packet);

  Stream &operator>>(Packet &packet);
  static uint8_t
  checksum8(std::vector<byte>::const_iterator begin, std::vector<byte>::const_iterator end);

private:
  std::iostream &device_;

  static std::vector<byte> package(const Packet &packet);
  static Packet extract(const std::vector<byte> &data);
};

} // namespace iap

#endif // IAP_STREAM_HPP
