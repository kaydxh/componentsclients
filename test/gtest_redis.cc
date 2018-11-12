#include <stdio.h>
#include "gtest/gtest.h"
#include "redis/redis.h"

std::shared_ptr<RedisClient> client_(new RedisClient);
TEST(RedisClientTest, connect) {
    int ret = client_->connect("127.0.0.1", 6379);
    EXPECT_TRUE(!ret);
}
