#ifndef INCLUDE_COMPONENTSCLIENTS_REDIS_H
#define INCLUDE_COMPONENTSCLIENTS_REDIS_H

#include <cpp_redis/cpp_redis>
#include "clientbase.h"

class RedisClient : public ClientBase {
   public:
    RedisClient();
    virtual ~RedisClient();
    virtual int connect(
	const std::string& ip, std::size_t port, uint32_t timeout_msecs = 0, const std::string& password = "");
    virtual int reconnect();
    virtual int disconnect();
    virtual int distory();

    int set(const std::string& key, const std::string& value);
    int get(std::string& _return, const std::string& key);

   private:
	cpp_redis::client client_;

};

#endif
