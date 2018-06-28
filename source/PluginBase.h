/*
    Plugin-SDK (Grand Theft Auto) SHARED header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstddef>
#include <cstdint>
#include "Base.h"

namespace plugin {

namespace Core {

// Gets the SDK version
PLUGIN_API unsigned int GetVersion();

}

// helpers for constructor overloading (deprecated)

struct dummy_func_t { }; // Dummy func tag type
static const dummy_func_t dummy; // Dummy func tag object

// meta template for functions
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
template<auto Func>
struct meta;
#elif (defined(_MSC_VER))
template<typename FuncType, FuncType Func>
struct meta;
#else

#endif

// meta templates for constructors, destructors and new/delete operators

template<typename ClassType, typename OverloadedDecl = void()>
struct ctor_meta;

template<typename ClassType>
struct dtor_meta;

template<typename ClassType>
struct del_dtor_meta;

template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
struct op_new_meta;

template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
struct op_new_array_meta;

template<typename ClassType, typename OverloadedDecl = void(void *)>
struct op_delete_meta;

template<typename ClassType, typename OverloadedDecl = void *(unsigned int)>
struct op_delete_array_meta;

// vtable description
template<typename ClassType>
struct vtable_meta;

// stack_object

template <typename T>
struct stack_object {
private:
    T object;
public:
    template<typename ...ArgTypes>
    stack_object(ArgTypes... args) : object(args...) {}
    T *operator->() { return &object; }
    T &get_object() { return object; }
};

template <typename T>
struct stack_object_no_default {
    stack_object_no_default() {}
    stack_object_no_default(stack_object_no_default &&) = delete;
    stack_object_no_default &operator=(stack_object_no_default &&) = delete;
protected:
    char objBuff[sizeof(T)];
public:
    T *operator->() { return reinterpret_cast<T *>(objBuff); }
    T &get_object() { return *reinterpret_cast<T *>(objBuff); }
};

// custom new/delete

template <typename ClassType, typename... ArgTypes>
ClassType *operator_new(ArgTypes... args) {
    return new ClassType(args...);
}

template <typename ClassType>
ClassType *operator_new_array(size_t size) {
    return new ClassType[size];
}

template <typename ClassType>
void operator_delete(ClassType *data) {
    delete data;
}

template <typename ClassType>
void operator_delete_array(ClassType *data) {
    delete[] data;
}

/*
// helpers for event creating

template<typename Meta>
using event_t = std::conditional_t<std::is_same<typename Meta::calling_convention_t, CallingConventions::Thiscall>::value,
    ThiscallEvent<typename Meta::refs_t, Meta::cb_priority, typename Meta::args_t, typename Meta::def_t>,
    CdeclEvent<typename Meta::refs_t, Meta::cb_priority, typename Meta::args_t, typename Meta::def_t>
>;

template<typename Meta, typename Refs, int Priority = Meta::cb_priority, typename Args = typename Meta::args_t, typename Def = typename Meta::def_t>
using custom_event_t = std::conditional_t<std::is_same<typename Meta::calling_convention_t, CallingConventions::Thiscall>::value,
    ThiscallEvent<Refs, Priority, Args, Def>,
    CdeclEvent<Refs, Priority, Args, Def>
>;
*/

// multi-version address list
template<int... Addresses>
struct MvAddresses {};

// Gets the virtual method table from the object @self
inline void** GetVMT(const void* self) {
    return *(void***)(self);
}

// Gets the virtual method from @self in the table index @index 
inline void* GetVMT(const void* self, size_t index) {
    return GetVMT(self)[index];
}

template <unsigned int address, typename... Args>
void Call(Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
}

template <typename Ret, unsigned int address, typename... Args>
Ret CallAndReturn(Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
}

template <unsigned int address, typename C, typename... Args>
void CallMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, unsigned int address, typename C, typename... Args>
Ret CallMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <unsigned int tableIndex, typename C, typename... Args>
void CallVirtualMethod(C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
}

template <typename Ret, unsigned int tableIndex, typename C, typename... Args>
Ret CallVirtualMethodAndReturn(C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>((*reinterpret_cast<void ***>(_this))[tableIndex])(_this, args...);
}

template <typename... Args>
void CallDyn(unsigned int address, Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename Ret, typename... Args>
Ret CallAndReturnDyn(unsigned int address, Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(GetGlobalAddress(address))(args...);
}

template <typename C, typename... Args>
void CallMethodDyn(unsigned int address, C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(GetGlobalAddress(address))(_this, args...);
}

template <typename Ret, typename C, typename... Args>
Ret CallMethodAndReturnDyn(unsigned int address, C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(GetGlobalAddress(address))(_this, args...);
}

template <typename... Args>
void CallDynGlobal(unsigned int address, Args... args) {
    reinterpret_cast<void(__cdecl *)(Args...)>(address)(args...);
}

template <typename Ret, typename... Args>
Ret CallAndReturnDynGlobal(unsigned int address, Args... args) {
    return reinterpret_cast<Ret(__cdecl *)(Args...)>(address)(args...);
}

template <typename C, typename... Args>
void CallMethodDynGlobal(unsigned int address, C _this, Args... args) {
    reinterpret_cast<void(__thiscall *)(C, Args...)>(address)(_this, args...);
}

template <typename Ret, typename C, typename... Args>
Ret CallMethodAndReturnDynGlobal(unsigned int address, C _this, Args... args) {
    return reinterpret_cast<Ret(__thiscall *)(C, Args...)>(address)(_this, args...);
}

}

// meta access
#if (defined(__GNUC__) || defined(__GNUG__) || defined(__clang__))
#define metaof(func) plugin::meta<&func >
#define metaof_o(func, decl) plugin::meta<static_cast<decl>(&func)>
#define META_BEGIN(func) template<> struct meta<&func > {
#define META_BEGIN_OVERLOADED(func, decl) template<> struct meta<static_cast<decl>(&func)> {
#elif (defined(_MSC_VER))
#define metaof(func) plugin::meta<decltype(&func), (&func)>
#define metaof_o(func, decl) plugin::meta<decl, (&func)>
#define META_BEGIN(func) template<> struct meta<decltype(&func), (&func)> {
#define META_BEGIN_OVERLOADED(func, decl) template<> struct meta<decl, (&func)> {
#else

#endif

#define CTOR_META_BEGIN(classType) template<> struct ctor_meta<classType> {
#define CTOR_META_BEGIN_OVERLOADED(classType, decl) template<> struct ctor_meta<classType, decl> {
#define DTOR_META_BEGIN(classType) template<> struct dtor_meta<classType> {
#define DEL_DTOR_META_BEGIN(classType) template<> struct del_dtor_meta<classType> {
#define OP_NEW_META_BEGIN(classType) template<> struct op_new_meta<classType> {
#define OP_NEW_META_BEGIN_OVERLOADED(classType, decl) template<> struct op_new_meta<classType, decl> {
#define OP_NEW_ARRAY_META_BEGIN(classType) template<> struct op_new_array_meta<classType> {
#define OP_NEW_ARRAY_META_BEGIN_OVERLOADED(classType, decl) template<> struct op_new_array_meta<classType, decl> {
#define OP_DELETE_META_BEGIN(classType) template<> struct op_delete_meta<classType> {
#define OP_DELETE_META_BEGIN_OVERLOADED(classType, decl) template<> struct op_delete_meta<classType, decl> {
#define OP_DELETE_ARRAY_META_BEGIN(classType) template<> struct op_delete_array_meta<classType> {
#define OP_DELETE_ARRAY_META_BEGIN_OVERLOADED(classType, decl) template<> struct op_delete_array_meta<classType, decl> {

#define META_END };

#define ctor_metaof(classType) plugin::ctor_meta<classType>
#define ctor_metaof_o(classType, decl) plugin::ctor_meta<classType, decl>
#define dtor_metaof(classType) plugin::dtor_meta<classType>
#define del_dtor_metaof(classType) plugin::del_dtor_meta<classType>
#define op_new_metaof(classType) plugin::op_new_meta<classType>
#define op_new_metaof_o(classType, decl) plugin::op_new_meta<classType, decl>
#define op_new_array_metaof(classType) plugin::op_new_array_meta<classType>
#define op_new_array_metaof_o(classType, decl) plugin::op_new_array_meta<classType, decl>
#define op_delete_metaof(classType) plugin::op_delete_meta<classType>
#define op_delete_metaof_o(classType, decl) plugin::op_delete_meta<classType, decl>
#define op_delete_array_metaof(classType) plugin::op_delete_array_meta<classType>
#define op_delete_array_metaof_o(classType, decl) plugin::op_delete_array_meta<classType, decl>

#define addrof(func) metaof(func)::address
#define gaddrof(func) metaof(func)::global_address
#define argsof(func) metaof(func)::args_t
#define refsof(func) metaof(func)::refs_t
#define idof(func) metaof(func)::id
#define addrof_o(func, decl) metaof_o(func, decl)::address
#define gaddrof_o(func, decl) metaof_o(func, decl)::global_address
#define argsof_o(func, decl) metaof_o(func, decl)::args_t
#define refsof_o(func, decl) metaof_o(func, decl)::refs_t
#define idof_o(func, decl) metaof_o(func, decl)::id

#define ctor_addr(classType) ctor_metaof(classType)::address
#define ctor_gaddr(classType) ctor_metaof(classType)::global_address
#define ctor_args(classType) ctor_metaof(classType)::args_t
#define ctor_refs(classType) ctor_metaof(classType)::refs_t
#define ctor_id(classType) ctor_metaof(classType)::id
#define ctor_addr_o(classType, decl) ctor_metaof_o(classType, decl)::address
#define ctor_gaddr_o(classType, decl) ctor_metaof_o(classType, decl)::global_address
#define ctor_args_o(classType, decl) ctor_metaof_o(classType, decl)::args_t
#define ctor_refs_o(classType, decl) ctor_metaof_o(classType, decl)::refs_t
#define ctor_id_o(classType, decl) ctor_metaof_o(classType, decl)::id

#define dtor_addr(classType) dtor_metaof(classType)::address
#define dtor_gaddr(classType) dtor_metaof(classType)::global_address
#define dtor_args(classType) dtor_metaof(classType)::args_t
#define dtor_refs(classType) dtor_metaof(classType)::refs_t
#define dtor_id(classType) dtor_metaof(classType)::id

#define del_dtor_addr(classType) del_dtor_metaof(classType)::address
#define del_dtor_gaddr(classType) del_dtor_metaof(classType)::global_address
#define del_dtor_args(classType) del_dtor_metaof(classType)::args_t
#define del_dtor_refs(classType) del_dtor_metaof(classType)::refs_t
#define del_dtor_id(classType) del_dtor_metaof(classType)::id

#define op_new_addr(classType) op_new_metaof(classType)::address
#define op_new_gaddr(classType) op_new_metaof(classType)::global_address
#define op_new_args(classType) op_new_metaof(classType)::args_t
#define op_new_refs(classType) op_new_metaof(classType)::refs_t
#define op_new_id(classType) op_new_metaof(classType)::id
#define op_new_addr_o(classType, decl) op_new_metaof_o(classType, decl)::address
#define op_new_gaddr_o(classType, decl) op_new_metaof_o(classType, decl)::global_address
#define op_new_args_o(classType, decl) op_new_metaof_o(classType, decl)::args_t
#define op_new_refs_o(classType, decl) op_new_metaof_o(classType, decl)::refs_t
#define op_new_id_o(classType, decl) op_new_metaof_o(classType, decl)::id

#define op_new_array_addr(classType) op_new_array_metaof(classType)::address
#define op_new_array_gaddr(classType) op_new_array_metaof(classType)::global_address
#define op_new_array_args(classType) op_new_array_metaof(classType)::args_t
#define op_new_array_refs(classType) op_new_array_metaof(classType)::refs_t
#define op_new_array_id(classType) op_new_array_metaof(classType)::id
#define op_new_array_addr_o(classType, decl) op_new_array_metaof_o(classType, decl)::address
#define op_new_array_gaddr_o(classType, decl) op_new_array_metaof_o(classType, decl)::global_address
#define op_new_array_args_o(classType, decl) op_new_array_metaof_o(classType, decl)::args_t
#define op_new_array_refs_o(classType, decl) op_new_array_metaof_o(classType, decl)::refs_t
#define op_new_array_id_o(classType, decl) op_new_array_metaof_o(classType, decl)::id

#define op_delete_addr(classType) op_delete_metaof(classType)::address
#define op_delete_gaddr(classType) op_delete_metaof(classType)::global_address
#define op_delete_args(classType) op_delete_metaof(classType)::args_t
#define op_delete_refs(classType) op_delete_metaof(classType)::refs_t
#define op_delete_id(classType) op_delete_metaof(classType)::id
#define op_delete_addr_o(classType, decl) op_delete_metaof_o(classType, decl)::address
#define op_delete_gaddr_o(classType, decl) op_delete_metaof_o(classType, decl)::global_address
#define op_delete_args_o(classType, decl) op_delete_metaof_o(classType, decl)::args_t
#define op_delete_refs_o(classType, decl) op_delete_metaof_o(classType, decl)::refs_t
#define op_delete_id_o(classType, decl) op_delete_metaof_o(classType, decl)::id

#define op_delete_array_addr(classType) op_delete_array_metaof(classType)::address
#define op_delete_array_gaddr(classType) op_delete_array_metaof(classType)::global_address
#define op_delete_array_args(classType) op_delete_array_metaof(classType)::args_t
#define op_delete_array_refs(classType) op_delete_array_metaof(classType)::refs_t
#define op_delete_array_id(classType) op_delete_array_metaof(classType)::id
#define op_delete_array_addr_o(classType, decl) op_delete_array_metaof_o(classType, decl)::address
#define op_delete_array_gaddr_o(classType, decl) op_delete_array_metaof_o(classType, decl)::global_address
#define op_delete_array_args_o(classType, decl) op_delete_array_metaof_o(classType, decl)::args_t
#define op_delete_array_refs_o(classType, decl) op_delete_array_metaof_o(classType, decl)::refs_t
#define op_delete_array_id_o(classType, decl) op_delete_array_metaof_o(classType, decl)::id

// vtable description - macro

#define VTABLE_DESC(className, vtAddr, vtSize)\
namespace plugin {\
template<> struct vtable_meta<className> {\
    static const unsigned int address = vtAddr;\
    static const unsigned int size = vtSize;\
};\
}

#define metaof_vtable(className) plugin::vtable_meta<className >

#define vtableid(className) plugin::vtable_meta<className >::address

// custom object construction

#define PLUGIN_NO_DEFAULT_CONSTRUCTION(className) \
    className() = delete;\
    className(className const &) = delete;\
    className(className &&) = delete;\
    ~className() = delete;\
    className &operator=(className &&) = delete;

#define PLUGIN_NO_DEFAULT_CONSTRUCTION_VIRTUALBASE(className) \
    className() = delete;\
    className(className const &) = delete;\
    className(className &&) = delete;\
    virtual ~className() = delete;\
    className &operator=(className &&) = delete;

// get global address for current exe version
#ifdef GTASA
#define GLOBAL_ADDRESS_BY_VERSION(a,b,c,d,e,f) (plugin::GetGlobalAddress(plugin::by_version_dyn(a,b,c,d,e,f)))
#define ADDRESS_BY_VERSION(a,b,c,d,e,f) (plugin::by_version_dyn(a,b,c,d,e,f))
#else
#define GLOBAL_ADDRESS_BY_VERSION(a,b,c) (plugin::GetGlobalAddress(plugin::by_version_dyn(a,b,c)))
#define ADDRESS_BY_VERSION(a,b,c) (plugin::by_version_dyn(a,b,c))
#endif
