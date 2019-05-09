#include "stream.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

namespace iap {

Stream::Stream(std::iostream &device) : device_{device} {}

Stream &Stream::operator<<(const Packet &packet)
{
  std::vector<byte> data = package(packet);

  device_.write(reinterpret_cast<char *>(data.data()), data.size());
  return *this;
}

Stream &Stream::operator>>(Packet &packet)
{
  std::vector<byte> data;
  byte cur{};
  cur = device_.get();
  while (cur != StartByte) {
    cur = device_.get();
  }
  data.push_back(cur);
  // next byte is length or marker
  cur = device_.get();
  data.push_back(cur);
  int16_t length{cur};
  if (cur == 0) {
    cur = device_.get();
    length += cur << 1;
    cur = device_.get();
    length += cur;
  }
  size_t currentSize = data.size();
  data.resize(currentSize + length + 1);
  device_.read(reinterpret_cast<char *>(&data[currentSize]), length + 1);
  packet = extract(data);
  return *this;
}

std::vector<byte> Stream::package(const Packet &packet)
{
  std::vector<byte> packed{};
  packed.reserve(packet.length() + 6);
  packed.push_back(0);
  packed.push_back(StartByte);
  if (packet.length() > 255) {
    packed.push_back(0);
    packed.push_back(packet.length() >> 1 & 0xFF);
    packed.push_back(packet.length() & 0xFF);
  }
  else {
    packed.push_back(static_cast<uint8_t>(packet.length() & 0xFF));
  }
  packed.push_back(packet.lingoId());
  std::copy(begin(packet.data()), end(packet.data()), std::back_inserter(packed));
  packed.push_back(checksum8(begin(packed) + 4, end(packed)));
  return packed;
}

Packet Stream::extract(const std::vector<byte> &data)
{
  Packet pack;
  return pack;
}

uint8_t
Stream::checksum8(std::vector<byte>::const_iterator begin, std::vector<byte>::const_iterator end)
{
  int8_t res = std::accumulate(begin, end, static_cast<int8_t>(0));
  return -res;
}

} // namespace iap
