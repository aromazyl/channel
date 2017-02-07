/*
 * configure.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef CONFIGURE_H
#define CONFIGURE_H

class Configure {
  private:
    Configure();
    Configure(const Configure&);
    void operator=(const Configure&);

  public:
    static Configure* Get() {
      static Configure conf;
      return &conf;
    }

    std::string& GetConf(const std::string& conf) {
      return conf_[conf];
    }

    bool IsExistConf(const std::string& conf) const {
      return conf_.count(conf);
    }

  private:
    std::unordered_map<std::string, std::string> conf_;

};

#endif /* !CONFIGURE_H */
