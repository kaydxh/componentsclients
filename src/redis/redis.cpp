#include "redis/redis.h"

RedisClient::RedisClient() {}
RedisClient::~RedisClient() {}

int RedisClient::connect(const std::string &ip, std::size_t port,
                         uint32_t timeout_msecs, const std::string &password) {
  try {
    client_.connect(ip, port,
                    [this](const std::string &host, std::size_t port,
                           cpp_redis::client::connect_state status) {
                      if (status == cpp_redis::client::connect_state::dropped) {
                        std::cout << "client disconnected from " << host << ":"
                                  << port << std::endl;
                      }
                    });
  } catch (...) {
    std::cout << "client connecte server " << ip << ":" << port << " exception"
              << std::endl;
    return -1;
  }

  if (!password.empty() && client_.is_connected()) {
    try {
      client_.auth(password, [](cpp_redis::reply &reply) {
        std::cout << "redis auth reply " << reply.as_string() << std::endl;
      });
    } catch (...) {
      std::cout << "redis auth exception" << std::endl;
    }
  }

  return 0;
}

/**
 cpp redis client auto reconnect
 **/
int RedisClient::reconnect() {
  return 0;
  // client_.reconnect();
  // return cilent_.is_connected() ? 0 : -1;
}

int RedisClient::disconnect() {
  try {
    if (client_.is_connected()) {
      client_.disconnect();
    }
  } catch (...) {
    std::cout << "redis disconnect exception" << std::endl;
    return -1;
  }

  return 0;
}

int RedisClient::distory() { return 0; }

int RedisClient::set(const std::string &key, const std::string &value) {
  try {
    if (client_.is_connected()) {
      client_.set(key, value);
      client_.sync_commit();
      return 0;
    }
  } catch (...) {
    std::cout << "set key:" << key << ",value:" << value << " exception"
              << std::endl;
  }

  return -1;
}

int RedisClient::get(std::string &_return, const std::string &key) {
  try {
    if (client_.is_connected()) {
      client_.get(key, [&, this](cpp_redis::reply &reply) {
        if (reply.is_string()) {
          _return = reply.as_string();
          std::cout << "get key:" << key << ",value:" << _return << std::endl;
        }
      });

      client_.sync_commit();
      return 0;
    }
  } catch (...) {
    std::cout << "get key:" << key << " exception" std::endl;
  }

  return -1;
}
