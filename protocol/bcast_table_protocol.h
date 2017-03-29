/*
 * bcast_table_protocol.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BCAST_TABLE_PROTOCOL_H
#define BCAST_TABLE_PROTOCOL_H

namespace protocol {
using namespace msg;

template <>
struct Encoder<BCAST_TABLE> {
  static bool Apply(const Location& from, const Location& to,
      std::vector<Location>& locs, Message** msg) {
    if (!*msg) *msg = new Message;
    (*msg)->type = BCAST_TABLE;
    (*msg)->from = *from;
    (*msg)->to   = *to;
    (*msg)->blob.resize(locs.size() * sizeof(Location) + sizeof(int));
    char* p = (char*)((*msg)->blob.data());
    *(int*)p = (int)locs.size();
    memcpy(p + sizeof(int), locs[0], sizeof(Location) * locs.size());
    return true;
  }
};

template <>
struct Decoder<BCAST_TABLE> {
  static bool Apply(const Message& msg, Location* from,
      Location* to, std::vector<Location>* locs) {
    if (!from || !to || !locs) {
      LOG(ERROR) << "from or to or locs is empty, bcast table decode failure";
      return false;
    }

    char* p = reinterpret_cast<char*>(msg.blob.data());
    int num = *(int*)p;
    locs->resize(num);
    memcpy(&locs[0], p + sizeof(int), sizeof(Location) * num);
    return true;
  };
};

}

#endif /* !BCAST_TABLE_PROTOCOL_H */
