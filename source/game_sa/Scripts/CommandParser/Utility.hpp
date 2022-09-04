#pragma once

#include <tuple> // tuple

#include "Pools.h"

namespace notsa {
namespace script {
namespace detail {
template<typename T>
auto& PoolOf();

template<>
auto& PoolOf<CPed>() { return *GetPedPool(); }
template<>
auto& PoolOf<CVehicle>() { return *GetVehiclePool(); }
template<>
auto& PoolOf<CBuilding>() { return *GetBuildingPool(); }
template<>
auto& PoolOf<CObject>() { return *GetObjectPool(); }
template<>
auto& PoolOf<CDummy>() { return *GetDummyPool(); }
template<>
auto& PoolOf<CColModel>() { return *GetColModelPool(); }
template<>
auto& PoolOf<CTask>() { return *GetTaskPool(); }
template<>
auto& PoolOf<CPedIntelligence>() { return *GetPedIntelligencePool(); }
template<>
auto& PoolOf<CPtrNodeSingleLink>() { return *GetPtrNodeSingleLinkPool(); }
template<>
auto& PoolOf<CPtrNodeDoubleLink>() { return *GetPtrNodeDoubleLinkPool(); }
template<>
auto& PoolOf<CEntryInfoNode>() { return *GetEntryInfoNodePool(); }
template<>
auto& PoolOf<CPointRoute>() { return *GetPointRoutePool(); }
template<>
auto& PoolOf<CPatrolRoute>() { return *GetPatrolRoutePool(); }
template<>
auto& PoolOf<CEvent>() { return *GetEventPool(); }
template<>
auto& PoolOf<CNodeRoute>() { return *GetNodeRoutePool(); }
template<>
auto& PoolOf<CTaskAllocator>() { return *GetTaskAllocatorPool(); }
template<>
auto& PoolOf<CPedAttractor>() { return *GetPedAttractorPool(); }
}; // detail

/*!
* Struct used to return multiple values from a script function.
* Eg.: MultiRet<int, int> => Push 2 ints using `StoreParameters`
*/
template<typename... Ts>
using MultiRet = std::tuple<Ts...>;
//struct MultiRet : public std::tuple<Ts...> {
//    using std::tuple::tuple;
//};

/*!
* Special return value used to update the compare flag.
*/
struct CompareFlagUpdate {
    bool state{};
};

}; // script


// Credit goes to https://github.com/sbx320
// Thank you!
template<std::size_t I, typename... Ts>
using nth_element_t = typename std::tuple_element<I, std::tuple<Ts...>>::type;

}; // notsa
