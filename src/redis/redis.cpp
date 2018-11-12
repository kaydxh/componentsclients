#include "redis/redis.h"

RedisClient::RedisClient() {}
RedisClient::~RedisClient() {}

int RedisClient::connect(const std::string& ip, std::size_t port,
			 uint32_t timeout_msecs, const std::string& password) {
    try {
	client_.connect(
	    ip, port,
	    [this](const std::string& host, std::size_t port,
		   cpp_redis::client::connect_state status) {
		if (status == cpp_redis::client::connect_state::dropped) {
		    std::cout << "client disconnected from " << host << ":"
			      << port << std::endl;
		}
	    });
    } catch (...) {
	std::cout << "client connecte server " << ip << ":" << port
		  << " exception" << std::endl;
	return -1;
    }

    if (!password.empty() && client_.is_connected()) {
	try {
	    client_.auth(password, [](cpp_redis::reply& reply) {
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
