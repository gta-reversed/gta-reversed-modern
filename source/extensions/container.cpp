#include "StdInc.h"

#include "container.hpp"

#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <span>

// https://en.cppreference.com/w/cpp/container
static_assert(Container<std::array<int, 1>>);
static_assert(Container<std::vector<int>>);
static_assert(Container<std::deque<int>>);
// static_assert(Container<std::forward_list<int>>); // size
static_assert(Container<std::list<int>>);
static_assert(Container<std::set<int, int>>);
static_assert(Container<std::map<int, int>>);
static_assert(Container<std::multiset<int, int>>);
static_assert(Container<std::multimap<int, int>>);
static_assert(Container<std::unordered_set<int, int>>);
static_assert(Container<std::unordered_map<int, int>>);
static_assert(Container<std::unordered_multiset<int, int>>);
static_assert(Container<std::unordered_multimap<int, int>>);
// static_assert(Container<std::stack<int>>); // forward_iterator
// static_assert(Container<std::queue<int>>); // forward_iterator
// static_assert(Container<std::priority_queue<int>>); // std::regular
// static_assert(Container<std::span<int>>); // std::regular

static_assert(Container<std::string>);
