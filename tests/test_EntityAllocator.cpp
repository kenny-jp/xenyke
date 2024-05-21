#include <gtest/gtest.h>
#include <xenyke/eng/ecs/entity_allocator.hpp>
#include <limits>

using namespace xke::ecs;

enum class TestEntityID : uint32_t {};

TEST(EntityIDAllocatorTest, AllocateSingleID) {
    EntityIDAllocator<TestEntityID> allocator;
    auto id = allocator.allocate();
    EXPECT_NE(id, EntityIDAllocator<TestEntityID>::INVALID_ENTITY_ID);
}

TEST(EntityIDAllocatorTest, AllocateMultipleIDs) {
    EntityIDAllocator<TestEntityID> allocator;
    auto ids = allocator.allocate(5);
    EXPECT_EQ(ids.size(), 5);
    for (const auto& id : ids) {
        EXPECT_NE(id, EntityIDAllocator<TestEntityID>::INVALID_ENTITY_ID);
    }
}

TEST(EntityIDAllocatorTest, DeallocateAndReuseID) {
    EntityIDAllocator<TestEntityID> allocator;
    auto id1 = allocator.allocate();
    /*auto id2 = */allocator.allocate();
    allocator.deallocate(id1);
    auto id3 = allocator.allocate();
    EXPECT_EQ(id1, id3); // ID should be reused
}

TEST(EntityIDAllocatorTest, AllocatedCount) {
    EntityIDAllocator<TestEntityID> allocator;
    allocator.allocate(10);
    EXPECT_EQ(allocator.allocatedCount(), 10);
    allocator.deallocate(allocator.allocate());
    EXPECT_EQ(allocator.allocatedCount(), 10); // Should still be 10 after deallocate and reallocate
}

TEST(EntityIDAllocatorTest, MassiveDeallocateAndReuse) {
    EntityIDAllocator<TestEntityID> allocator;
    auto ids = allocator.allocate(1000);
    EXPECT_EQ(allocator.allocatedCount(), 1000);

    for (const auto& id : ids) {
        allocator.deallocate(id);
    }
    EXPECT_EQ(allocator.allocatedCount(), 0);

    auto newIds = allocator.allocate(1000);
    EXPECT_EQ(allocator.allocatedCount(), 1000);
    for (const auto& id : newIds) {
        EXPECT_NE(id, EntityIDAllocator<TestEntityID>::INVALID_ENTITY_ID);
    }
}

TEST(EntityIDAllocatorTest, MaxCapacityTest) {
    EntityIDAllocator<TestEntityID> allocator;
    const size_t maxCapacity = std::numeric_limits<std::underlying_type_t<TestEntityID>>::max();

    for (size_t i = 0; i < maxCapacity; ++i) {
        allocator.allocate();
    }

    // // Tentative d'allocation supplémentaire après avoir atteint la capacité maximale
    // auto id = allocator.allocate();
    // EXPECT_EQ(id, EntityIDAllocator<TestEntityID>::INVALID_ENTITY_ID);
}


TEST(EntityIDAllocatorTest, PerformanceTest) {
    EntityIDAllocator<TestEntityID> allocator;
    const size_t numEntities = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    auto ids = allocator.allocate(numEntities);
    auto end = std::chrono::high_resolution_clock::now();

    EXPECT_EQ(ids.size(), numEntities);
    EXPECT_EQ(allocator.allocatedCount(), numEntities);

    for (const auto& id : ids) {
        allocator.deallocate(id);
    }
    EXPECT_EQ(allocator.allocatedCount(), 0);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Allocation of " << numEntities << " entities took " << duration.count() << " milliseconds.\n";
}

TEST(EntityIDAllocatorTest, VeryMassiveAllocationTest) {
    EntityIDAllocator<TestEntityID> allocator;
    const size_t numEntities = 10000000; // 10 millions

    auto start = std::chrono::high_resolution_clock::now();
    auto ids = allocator.allocate(numEntities);
    auto end = std::chrono::high_resolution_clock::now();

    EXPECT_EQ(ids.size(), numEntities);
    EXPECT_EQ(allocator.allocatedCount(), numEntities);

    for (const auto& id : ids) {
        allocator.deallocate(id);
    }
    EXPECT_EQ(allocator.allocatedCount(), 0);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Allocation of " << numEntities << " entities took " << duration.count() << " milliseconds.\n";
}

// Test de stress

TEST(EntityIDAllocatorTest, StressTest) {
    EntityIDAllocator<TestEntityID> allocator;
    const size_t numOperations = 1000000; // 1 million
    std::vector<TestEntityID> ids;
    ids.reserve(numOperations);

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numOperations; ++i) {
        ids.push_back(allocator.allocate());
    }

    for (size_t i = 0; i < numOperations; ++i) {
        if (i % 2 == 0) {
            allocator.deallocate(ids[i]);
        }
    }

    for (size_t i = 0; i < numOperations / 2; ++i) {
        allocator.allocate();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Stress test with " << numOperations << " operations took " << duration.count() << " milliseconds.\n";
}

// Test multithreadé

TEST(EntityIDAllocatorTest, MultithreadedTest) {
    EntityIDAllocator<TestEntityID> allocator;
    const size_t numEntities = 1000000;
    const size_t numThreads = 4;
    std::atomic<size_t> allocatedCount(0);

    auto allocateEntities = [&]() {
        for (size_t i = 0; i < numEntities / numThreads; ++i) {
            allocator.allocate();
            ++allocatedCount;
        }
    };

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(allocateEntities);
    }
    for (auto& t : threads) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();

    EXPECT_EQ(allocatedCount.load(), numEntities);
    EXPECT_EQ(allocator.allocatedCount(), numEntities);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Multithreaded allocation of " << numEntities << " entities took " << duration.count() << " milliseconds.\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
