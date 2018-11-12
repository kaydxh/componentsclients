#ifndef INCLUDE_COMOPENTSCLIENTS_H
#define INCLUDE_COMOPENTSCLIENTS_H

#include <string>
class ClientBase {
   public:
    ClientBase() {}
    virtual ~ClientBase() {}
    virtual int connect(const std::string& ip, std::size_t port,
			uint32_t timeout_msecs = 0,
			const std::string& password = "") = 0;
    virtual int reconnect() = 0;
    virtual int disconnect() = 0;
};

#endif
