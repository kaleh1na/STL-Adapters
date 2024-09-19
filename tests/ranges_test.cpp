#include <gtest/gtest.h>

#include <deque>
#include <forward_list>
#include <iostream>
#include <lib/ranges.cpp>
#include <map>
#include <ranges>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

TEST(RangesTestSuit, KeyTest) {
  map<int, std::string> m = {
      {35, "i"}, {434, "like"}, {3, "c++"}, {82323, "hello"}, {22, "world"}};
  auto k = keys(m);
  vector<int> ans = {3, 22, 35, 434, 82323};
  int i = 0;
  for (auto key : k) {
    ASSERT_EQ(key, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, ValueTest) {
  map<int, std::string> m = {
      {35, "i"}, {434, "like"}, {3, "c++"}, {82323, "hello"}, {22, "world"}};
  auto val = values(m);
  vector<std::string> ans = {"c++", "world", "i", "like", "hello"};
  int i = 0;
  for (auto value : val) {
    ASSERT_EQ(value, ans[i]);
    ++i;
  }
  std::cout << std::endl;
}

TEST(RangesTestSuit, TakeTest) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4};
  auto vec = take(v, 4);
  int i = 0;
  for (auto value : vec) {
    ASSERT_EQ(value, v[i]);
    ++i;
  }
}

TEST(RangesTestSuit, DropTest) {
  const vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4};
  auto vec = drop(v, 4);
  int i = 4;
  for (auto value : vec) {
    ASSERT_EQ(value, v[i]);
    ++i;
  }
}

TEST(RangesTestSuit, ReverseTest) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4};
  auto vec = reverse(v);
  int i = v.size() - 1;
  for (auto value : vec) {
    ASSERT_EQ(value, v[i]);
    --i;
  }
}

TEST(RangesTestSuit, FilterTest) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4};
  auto vec = filter(v, [](int i) { return i % 2 == 0; });
  vector<int> ans;
  for (auto value : v) {
    if (value % 2 == 0) {
      ans.push_back(value);
    }
  }
  int i = 0;
  for (auto value : vec) {
    ASSERT_EQ(value, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, TransformTest) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4};
  auto vec = transform(v, [](int i) { return i * 10; });
  int i = 0;
  for (auto value : vec) {
    ASSERT_EQ(value, v[i] * 10);
    ++i;
  }
}

TEST(RangesTestSuit, ChangesTest) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4, 6, 12};
  auto vec = filter(v, [](int i) { return i % 2 == 0; });
  v.push_back(10);
  v.push_back(11);
  std::vector<int> ans;
  for (auto i : v) {
    if (i % 2 == 0) {
      ans.push_back(i);
    }
  }
  int i = 0;
  for (auto value : vec) {
    ASSERT_EQ(value, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, VectorTest1) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4, 98, 10, 2, 54, 6};
  vector<int> ans = {864, 96};
  int i = 0;
  for (auto val : v | filter([](int i) { return i % 2 == 0; }) |
                      transform([](int i) { return i * 16; }) | drop(4) |
                      filter([](int i) { return i % 3 == 0; })) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, VectorTest2) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4, 98, 10, 2, 54, 6, 15};
  vector<int> ans = {19, 6, 31};
  int i = 0;
  for (auto val : v | filter([](int i) { return i % 2 == 1; }) |
                      transform([](int i) { return i * 17; }) | drop(1) |
                      filter([](int i) { return i % 3 == 0; }) | take(4) |
                      transform([](int i) { return i / 8; })) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, VectorTest3) {
  vector<int> v = {1, 8, 9, 10, 11, 2, 3, 4, 98, 10, 2, 54, 6, 15};
  int i = 0;
  for (auto val : v | filter([](int i) { return i % 2 == 1; }) |
                      transform([](int i) { return i * 17; }) | drop(10) |
                      take(10)) {
    ++i;
  }
  ASSERT_EQ(i, 0);
}

TEST(RangesTestSuit, MapTest1) {
  map<int, int> m = {{35, 1}, {434, 2}, {3, 3}, {82323, 4}, {22, 5}};
  vector<int> ans = {217, 41161};
  int i = 0;
  for (auto key : m | transform([](pair<int, int> x) {
                    return make_pair(x.first / 2, x.second);
                  }) | keys |
                      drop(3)) {
    ASSERT_EQ(key, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, MapTest2) {
  map<int, std::string> m = {
      {35, "i"}, {434, "like"}, {3, "c++"}, {82323, "hello"}, {22, "world"}};
  vector<string> ans = {"i", "like"};
  int i = 0;
  for (auto key : m | take(4) | drop(2) | values) {
    ASSERT_EQ(key, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, MapTest3) {
  map<int, std::string> m = {
      {35, "i"}, {434, "like"}, {3, "c++"}, {82323, "hello"}, {22, "world"}};
  vector<int> ans = {2170, 110};
  int i = 0;
  for (auto val : m | reverse | keys | filter([](int i) {
                    return i % 2 == 0;
                  }) | transform([](int i) { return i * 5; })) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, SetTest1) {
  set<char> s = {'a', 'b', 'd', 'e', 'r', 'l', 'c'};
  vector<char> ans = {'c', 'd', 'e'};
  int i = 0;
  for (auto key : s | reverse | reverse | take(5) | drop(2)) {
    ASSERT_EQ(ans[i], key);
    ++i;
  }
}

TEST(RangesTestSuit, SetTest2) {
  set<int> v = {1, 8, 9, 10, 11, 2, 3, 4, 98, 10, 2, 54, 6, 15};
  vector<int> ans = {31, 19, 6};
  int i = 0;
  for (auto val : v | filter([](int i) { return i % 2 == 1; }) |
                      transform([](int i) { return i * 17; }) | drop(1) |
                      filter([](int i) { return i % 3 == 0; }) | take(4) |
                      transform([](int i) { return i / 8; }) | reverse) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, DequeTest1) {
  deque<int> d = {1, 4, 8, 2, 3, 0, 10};
  auto a = d | transform([](int i) { return i - 100; }) |
           filter([](int i) { return i <= -95; }) | reverse;
  d.pop_front();
  d.push_back(-5);
  vector<int> ans = {-105, -100, -97, -98, -96};
  int i = 0;
  for (auto val : a) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, DequeTest2) {
  deque<char> d = {'a', 'e', 'r'};
  auto a = d | reverse | drop(1) | take(1);
  d.pop_front();
  d.push_back('o');
  vector<char> ans = {'r', 'e'};
  int i = 0;
  for (auto val : a) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, ListTest1) {
  forward_list<int> l = {5, 4, 1, 6, 7, 8, 100};
  auto a = l | transform([](int i) { return i - 8; }) |
           filter([](int i) { return i <= 7; }) | take(4);
  l.push_front(2);
  vector<int> ans = {-6, -3, -4, -7};
  int i = 0;
  for (auto val : a) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}

TEST(RangesTestSuit, ListTest2) {
  forward_list<string> l = {"lalala", "lululu",  "lolo",
                            "ler",    "grandma", "mam"};
  auto a =
      l | filter([](string i) { return i.size() <= 4; }) | take(4) | drop(3);
  l.push_front("lego");
  vector<string> ans = {"mam"};
  int i = 0;
  for (auto val : a) {
    ASSERT_EQ(val, ans[i]);
    ++i;
  }
}
