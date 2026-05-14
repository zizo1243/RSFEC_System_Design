//
// Created by ziadf on 5/25/2025.
//
#include <gtest/gtest.h>#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <set>

std::map<std::string, std::set<std::string>> test_results;

class TestResultListener : public ::testing::EmptyTestEventListener {
    void OnTestEnd(const ::testing::TestInfo& test_info) override {
        std::string suite_name = test_info.test_suite_name();
        if (test_info.result()->Passed()) {
            test_results[suite_name].insert(test_info.name());
        }
    }

    void OnTestProgramEnd(const ::testing::UnitTest& unit_test) override {
        std::cout << "\n=== Test Summary ===\n";
        for (int i = 0; i < unit_test.total_test_suite_count(); ++i) {
            const ::testing::TestSuite* test_suite = unit_test.GetTestSuite(i);
            const std::string& suite_name = test_suite->name();

            if (test_suite->total_test_count() == test_suite->successful_test_count()) {
                std::cout << "[PASS] All tests in class \"" << suite_name << "\" passed.\n";
            } else {
                std::cout << "[FAIL] Some tests in class \"" << suite_name << "\" failed.\n";
            }
        }
    }
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Add our custom listener
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new TestResultListener);

    return RUN_ALL_TESTS();
}
