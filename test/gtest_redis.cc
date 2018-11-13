#include <stdio.h>
#include "gtest/gtest.h"
#include "redis/redis.h"

std::shared_ptr<RedisClient> client_(new RedisClient);
TEST(RedisClientTest, connect) {
    int ret = client_->connect("127.0.0.1", 6379);
    EXPECT_TRUE(!ret);
}

TEST(RedisClientTest, set) {
    int ret = client_->set("kay", "hello word");
    EXPECT_EQ(0, ret);
}
TEST(RedisClientTest, get) {
    std::string value;
    int ret = client_->get(value, "kay");
    EXPECT_EQ(0, ret);
    std::cout << value << std::endl;
    EXPECT_EQ(value, "hello word");
}
