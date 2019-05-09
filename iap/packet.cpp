#include "packet.hpp"

namespace iap {

Packet::Packet() {}

int Packet::length() const
{
  return length_;
}

uint8_t Packet::lingoId() const
{
  return lingoId_;
}

std::vector<byte> Packet::data() const
{
  return data_;
}

} // namespace iap
