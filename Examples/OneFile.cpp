#define SPEC_GROUP MainGroup

#include <MiniSpecs.h>
#include <MiniSpecs/Main.h>

// Idea:
// TestData("First Values", 69, "String 69");
// TestData("Second Values", 420, "String 420");
// Test("Test 1") {
//     //
//     auto [str, num, text] = get_test_data<std::string, int, std::string>();
//     auto justStr = get_test_data<std::string>(0);
//     auto justNum = get_test_data<int>(1);
// }

// Or, another example that provides a list of {key, value} pairs for each TestData:
// TestData({"key1", 69}, {"key2", "String 69"});
// TestData({"key1", 420}, {"key2", "String 420"});
// Test("Test 1") {
//     //
//    // Now you get the values using their keys:
//    auto num = get_test_data<int>("key1");
