#include <memory>
#include <deque>
#include <random>
#include <boost/circular_buffer.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/intrusive_ptr.hpp>
#include <benchmark/benchmark.h>
#include "ring_buffer.h"

struct Test
{
    std::string s1;
    int i1;
    double d1;

    Test(const std::string& s, int i, double d) : s1(s), i1(i), d1(d) {}

    Test() {}

    Test(const Test& test) noexcept : s1(test.s1),i1(test.i1),d1(test.d1) {
    }

    Test(const Test&& test) noexcept : s1(std::move(test.s1)),i1(std::move(test.i1)),d1(std::move(test.d1)) {
    }

    Test& operator=(const Test&& test) noexcept {
        s1 = std::move(test.s1);
        i1 = std::move(test.i1);
        d1 = std::move(test.d1);
        return *this;
    }

    Test& operator=(const Test& test) noexcept {
        s1 = test.s1;
        i1 = test.i1;
        d1 = test.d1;
        return *this;
    }
};

static constexpr int BUF_SIZE = 1000;
static constexpr int ITERATIONS = 100000;
static constexpr int INIT_SIZE = 100;
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(1, 2);

std::deque<Test> cbuf2(1000);
RingBuffer<Test> cbuf1(1000);

static void BM_OwnRingBuffer(benchmark::State &state)
{
    Test test;
    for (auto _ : state)
    {
        for (int i = 0; i < INIT_SIZE; i++)
        {
            cbuf1.emplace(Test());
        }
        for (int i = 0; i < ITERATIONS; i++)
        {
            if (dist(mt) == 1)
            {
                cbuf1.emplace(Test());
            }
            else
            {
                if (!cbuf1.isEmpty())
                    cbuf1.pop();
            }
        }
    }
}

static void BM_StdDeque(benchmark::State &state)
{
    for (auto _ : state)
    {
        for (int i = 0; i < INIT_SIZE; i++)
        {
            cbuf2.push_back(Test());
        }
        for (int i = 0; i < ITERATIONS; i++)
        {
            if (dist(mt) == 1)
            {
                cbuf2.push_back(Test());
            }
            else
            {
                if (!cbuf2.empty())
                    cbuf2.pop_front();
            }
        }
    }
}

BENCHMARK(BM_OwnRingBuffer);
BENCHMARK(BM_StdDeque);

BENCHMARK_MAIN();