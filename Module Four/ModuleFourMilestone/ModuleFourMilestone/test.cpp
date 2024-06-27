#include "pch.h"

// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

struct ParameterizedCollectionTest : CollectionTest, ::testing::WithParamInterface<int> {
    ParameterizedCollectionTest() { }
};

INSTANTIATE_TEST_CASE_P(CollectionSizes, ParameterizedCollectionTest, ::testing::Values(0, 1, 5, 10));

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()); //collection should be empty
    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0); //collection should equal size of 0

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty()); //collection should have a value
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1); //collection should equal size of 1
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    ASSERT_FALSE(collection->empty());

    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_P(ParameterizedCollectionTest, MaxSizeGreaterThanSize) {
    
    //test collection is empty
    EXPECT_TRUE(collection->empty());

    //if collection is empty then collection size must be zero
    EXPECT_EQ(collection->size(), 0);

    add_entries(GetParam());

    ASSERT_EQ(collection->size(), GetParam());

    ASSERT_GT(collection->max_size(), collection->size());

}
// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_P(ParameterizedCollectionTest, CapacityGreaterthanOrEqualToSize) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(GetParam());

    ASSERT_EQ(collection->size(), GetParam());

    ASSERT_GE(collection->capacity(), collection->size());
}
// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizeIncreasesCollectionSize) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    collection->resize(5);

    ASSERT_EQ(collection->size(), 5);
}
// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizeDecreasesCollectionSize) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    EXPECT_FALSE(collection->empty());

    EXPECT_EQ(collection->size(), 5);

    collection->resize(2);

    ASSERT_EQ(collection->size(), 2);
}
// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizeCollectionResizeToZero) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    EXPECT_FALSE(collection->empty());

    EXPECT_EQ(collection -> size(), 5);

    collection->resize(0);

    ASSERT_EQ(collection->size(), 0);
}
// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, ClearCollection) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    EXPECT_FALSE(collection->empty());

    EXPECT_EQ(collection->size(), 5);

    collection->clear();

    ASSERT_TRUE(collection->empty());

    ASSERT_EQ(collection->size(), 0);
}
// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, EraseCollection) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    add_entries(5);

    EXPECT_FALSE(collection->empty());

    EXPECT_EQ(collection->size(), 5);

    collection->erase(collection->begin(), collection->end());

    ASSERT_TRUE(collection->empty());

    ASSERT_EQ(collection->size(), 0);
}
// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCollectionCapacity) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    EXPECT_EQ(collection->capacity(), 0);

    collection->reserve(5);

    ASSERT_TRUE(collection->empty());

    ASSERT_EQ(collection->size(), 0);

    ASSERT_GT(collection->capacity(), collection->size());
}
// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExpectionThrown) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    ASSERT_THROW(collection->at(5), std::out_of_range);
}
// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
//Tests to verify adding specified values are assigned
TEST_F(CollectionTest, AssignValuesToCollection) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    collection->assign(5, 10);

    ASSERT_FALSE(collection->empty());

    ASSERT_EQ(collection->size(), 5);

    for (int i = 0; i < collection->size(); i++) {
        ASSERT_EQ(collection->at(i), 10);
    }
}

//Test to confirm collection reserve can't be bigger than max size
TEST_F(CollectionTest, IncreaseCollectionReserveAboveMaxSize) {
    EXPECT_TRUE(collection->empty());

    EXPECT_EQ(collection->size(), 0);

    ASSERT_THROW(collection->reserve(collection->max_size() + 10), std::length_error);
}