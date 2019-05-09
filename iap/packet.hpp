#ifndef IAP_PACKET_HPP
#define IAP_PACKET_HPP

#include <cstdint>
#include <vector>

namespace iap {

using byte = unsigned char;

class Packet {
public:
  Packet();

  int length() const;

  uint8_t lingoId() const;

  std::vector<byte> data() const;

private:
  int length_;
  uint8_t lingoId_;
  std::vector<byte> data_;
};

} // namespace iap

#endif // IAP_PACKET_HPP
