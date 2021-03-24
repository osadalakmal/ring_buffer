#include <gtest/gtest.h>
#include "ring_buffer.h"

using namespace ::testing;

struct Value
{
    std::string s1;
    int i1;
    double d1;

    Value(const std::string& s, int i, double d) : s1(s), i1(i), d1(d) {}

    Value() {}

    Value(const Value& test) noexcept : s1(test.s1),i1(test.i1),d1(test.d1) {
    }

    Value(const Value&& test) noexcept : s1(std::move(test.s1)),i1(std::move(test.i1)),d1(std::move(test.d1)) {
    }

    Value& operator=(const Value&& test) noexcept {
        s1 = std::move(test.s1);
        i1 = std::move(test.i1);
        d1 = std::move(test.d1);
        return *this;
    }

    Value& operator=(const Value& test) noexcept {
        s1 = test.s1;
        i1 = test.i1;
        d1 = test.d1;
        return *this;
    }
};

class RingBufferTest : public ::testing::Test {
protected:
    RingBuffer<std::string> instance;
    RingBufferTest() : instance(3) {}
};

TEST_F(RingBufferTest, InputDoesNotExceedCapacity)
{

    const std::string data[] = {"This", "is"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);

    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    ASSERT_TRUE(instance.isEmpty());
}


TEST_F(RingBufferTest,whereInputEqualsCapacity)
{

    const std::string data[] = {"This", "is", "a"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);

    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());
}


TEST_F(RingBufferTest,whereInputExeedsCapacityByOne)
{

    const std::string data[] = {"This", "is", "a", "Test"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);
    instance.emplace(data[3]);

    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());
}


TEST_F(RingBufferTest,whereInputExeedsCapacityByTwo)
{

    const std::string data[] = {"This", "is", "a", "Test", "Today"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);
    instance.emplace(data[3]);
    instance.emplace(data[4]);

    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());
}


TEST_F(RingBufferTest,whereInputExeedsCapacityByLots)
{

    const std::string data[] = {"This", "is", "a", "Test", "Today", "Expected:", "Monday",
                           "tuesday", "Wednesday"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);
    instance.emplace(data[3]);
    instance.emplace(data[4]);
    instance.emplace(data[5]);
    instance.emplace(data[6]);
    instance.emplace(data[7]);
    instance.emplace(data[8]);

    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());
}

TEST_F(RingBufferTest,whereBufferRefill)
{

    const std::string data[] = {"This", "is", "a"};

    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);

    ASSERT_TRUE(instance.isFull());
    std::string result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());


    instance.emplace(data[0]);
    instance.emplace(data[1]);
    instance.emplace(data[2]);

    ASSERT_TRUE(instance.isFull());
    result = instance.pop();
    ASSERT_EQ(data[0], result);

    result = instance.pop();
    ASSERT_EQ(data[1], result);

    result = instance.pop();
    ASSERT_EQ(data[2], result);

    ASSERT_TRUE(instance.isEmpty());
}
