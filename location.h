/*
 * location.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOCATION_H
#define LOCATION_H

// location info for actors

enum ActorType {
  kServerGroup;
  kWorkerGroup;
};

struct Location {
  int port;
  int ip;
  ActorType type;
  int type_id;
};

#endif /* !LOCATION_H */
