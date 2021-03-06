/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_CORE_MACRO
#define CHECKHEADER_SLIB_CORE_MACRO

#include "definition.h"

#define SLIB_UINT8_MAX		(sl_uint8)(0xFF)
#define SLIB_INT8_MAX		(sl_int8)(0x7F)
#define SLIB_INT8_MIN		(sl_int8)(-0x80)
#define SLIB_UINT16_MAX		(sl_uint16)(0xFFFF)
#define SLIB_INT16_MAX		(sl_int16)(0x7FFF)
#define SLIB_INT16_MIN		(sl_int16)(-0x8000)
#define SLIB_UINT32_MAX		0xFFFFFFFF
#define SLIB_INT32_MAX		0x7FFFFFFF
#define SLIB_INT32_MIN		-0x80000000
#define SLIB_UINT64_MAX		SLIB_UINT64(0xFFFFFFFFFFFFFFFF)
#define SLIB_INT64_MAX		SLIB_INT64(0x7FFFFFFFFFFFFFFF)
#define SLIB_INT64_MIN		SLIB_INT64(-0x8000000000000000)

#ifdef SLIB_ARCH_IS_64BIT
#define SLIB_SIZE_MAX		SLIB_UINT64_MAX
#define SLIB_REG_MAX		SLIB_INT64_MAX
#define SLIB_REG_MIN		SLIB_INT64_MIN
#else
#define SLIB_SIZE_MAX		SLIB_UINT32_MAX
#define SLIB_REG_MAX		SLIB_INT32_MAX
#define SLIB_REG_MIN		SLIB_INT32_MIN
#endif

#if defined(SLIB_COMPILER_IS_VC)
#	define SLIB_STRINGIFY(...)				(#__VA_ARGS__)
#	define SLIB_STRINGIFY_UNICODE(...)		SLIB_UNICODE(#__VA_ARGS__)
#elif defined(SLIB_COMPILER_IS_GCC)
#	define SLIB_STRINGIFY(x...)				(#x)
#	define SLIB_STRINGIFY_UNICODE(x...)		SLIB_UNICODE(#x)
#endif

#define SLIB_IS_ALIGNED(p, a)		(!((unsigned long)(p) & ((a) - 1)))
#define SLIB_IS_ALIGNED_4(x)		(!(((sl_reg)((void*)(x))) & 3))
#define SLIB_IS_ALIGNED_8(x)		(!(((sl_reg)((void*)(x))) & 7))

#define SLIB_MAX(a, b)				((a)>(b)?(a):(b))
#define SLIB_MIN(a, b)				((a)<(b)?(a):(b))

#define SLIB_CHECK_FLAG(v, flag)	(((v) & (flag)) != 0)
#define SLIB_SET_FLAG(v, flag)		v |= (flag);
#define SLIB_RESET_FLAG(v, flag)	v &= (~(flag));

#define SLIB_GET_BYTE(A,n)			((sl_uint8)((A) >> (n << 3)))
#define SLIB_GET_BYTE0(A)			((sl_uint8)(A))
#define SLIB_GET_BYTE1(A)			((sl_uint8)((A) >> 8))
#define SLIB_GET_BYTE2(A)			((sl_uint8)((A) >> 16))
#define SLIB_GET_BYTE3(A)			((sl_uint8)((A) >> 24))
#define SLIB_GET_BYTE4(A)			((sl_uint8)((A) >> 32))
#define SLIB_GET_BYTE5(A)			((sl_uint8)((A) >> 40))
#define SLIB_GET_BYTE6(A)			((sl_uint8)((A) >> 48))
#define SLIB_GET_BYTE7(A)			((sl_uint8)((A) >> 56))
#define SLIB_GET_WORD(A,n)			((sl_uint16)((A) >> (n << 4)))
#define SLIB_GET_WORD0(A)			((sl_uint16)(A))
#define SLIB_GET_WORD1(A)			((sl_uint16)((A) >> 16))
#define SLIB_GET_WORD2(A)			((sl_uint16)((A) >> 32))
#define SLIB_GET_WORD3(A)			((sl_uint16)((A) >> 48))
#define SLIB_GET_DWORD(A,n)			((sl_uint32)((A) >> (n << 5)))
#define SLIB_GET_DWORD0(A)			((sl_uint32)(A))
#define SLIB_GET_DWORD1(A)			((sl_uint32)((A) >> 32))

#define SLIB_MAKE_WORD(A,B)					((((sl_uint32)(A))<<8) | ((sl_uint32)(B)))
#define SLIB_MAKE_DWORD(A,B,C,D)			((((sl_uint32)(A))<<24) | (((sl_uint32)(B))<<16) | (((sl_uint32)(C))<<8) | ((sl_uint32)(D)))
#define SLIB_MAKE_DWORD2(A,B)				((((sl_uint32)(A))<<16) | ((sl_uint32)(B)))
#define SLIB_MAKE_QWORD(A,B,C,D,E,F,G,H)	(((sl_uint64)(SLIB_MAKE_DWORD(A,B,C,D)) << 32) | SLIB_MAKE_DWORD(E,F,G,H))
#define SLIB_MAKE_QWORD2(A,B,C,D)			(((sl_uint64)(SLIB_MAKE_DWORD2(A,B)) << 32) | SLIB_MAKE_DWORD2(C,D))
#define SLIB_MAKE_QWORD4(A,B)				((((sl_uint64)(A)) << 32) | (B))

#if defined(SLIB_COMPILER_IS_VC)
#	define SLIB_HAS_FEATURE_iS_CONVERTIBLE_TO
#elif defined(SLIB_COMPILER_IS_GCC)
#	if defined(__has_feature)
#		if __has_feature(is_convertible_to)
#			define SLIB_HAS_FEATURE_iS_CONVERTIBLE_TO
#		endif
#	endif
#endif

#if defined(SLIB_HAS_FEATURE_iS_CONVERTIBLE_TO)
#	define SLIB_TRY_CONVERT_TYPE(FROM, TO) \
		{ static_assert(__is_convertible_to(FROM, TO), "Cannot convert from '" #FROM "' to '" #TO "'"); }
#else
#	define SLIB_TRY_CONVERT_TYPE(FROM, TO) \
		{ static_assert(slib::IsConvertible<FROM, TO>::value, "Cannot convert from '" #FROM "' to '" #TO "'"); }
#endif


#define SLIB_MEMBERS_OF_PRIMITIVE_WRAPPER(CLASS, TYPE, VALUE) \
public: \
	constexpr CLASS(TYPE _value) : VALUE(_value) {} \
	constexpr CLASS(const CLASS& other) : VALUE(other.VALUE) {} \
	constexpr operator TYPE() const { return VALUE; } \
	SLIB_INLINE CLASS& operator=(const CLASS& other) { VALUE = other.VALUE; return *this; } \
	SLIB_INLINE CLASS& operator=(TYPE _value) { VALUE = _value; return *this; } \
	constexpr sl_bool operator==(const CLASS& other) const { return VALUE == other.VALUE; } \
	constexpr sl_bool operator==(TYPE _value) const { return VALUE == _value; } \
	constexpr sl_bool operator!=(const CLASS& other) const { return VALUE != other.VALUE; } \
	constexpr sl_bool operator!=(TYPE _value) const { return VALUE != _value; }

#define SLIB_MEMBERS_OF_FLAGS(CLASS, VALUE) \
	SLIB_MEMBERS_OF_PRIMITIVE_WRAPPER(CLASS, int, VALUE) \
	constexpr CLASS() : VALUE(0) {} \
	SLIB_INLINE CLASS& operator|=(int _value) { VALUE |= _value; return *this; } \
	SLIB_INLINE CLASS& operator&=(int _value) { VALUE &= _value; return *this; }


#define SLIB_PROPERTY(TYPE, NAME) \
protected: \
	TYPE _m_property_##NAME; \
public: \
	typename slib::PropertyTypeHelper<TYPE>::RetType get##NAME() const { return _m_property_##NAME; } \
	void set##NAME(typename slib::PropertyTypeHelper<TYPE>::ArgType v) { _m_property_##NAME = v; } \

#define SLIB_BOOLEAN_PROPERTY(NAME) \
protected: \
	sl_bool _m_property_##NAME; \
public: \
	sl_bool is##NAME() const { return _m_property_##NAME; } \
	void set##NAME(sl_bool v) { _m_property_##NAME = v; }


#define SLIB_REFERABLE_MEMBER slib::ReferableKeeper _slib_referable_keeper(this);
#define SLIB_REFERABLE_CONSTRUCTOR SLIB_REFERABLE_MEMBER
#define SLIB_REFERABLE_DESTRUCTOR SLIB_REFERABLE_MEMBER
#define SLIB_KEEP_REF SLIB_REFERABLE_MEMBER

#define SLIB_DECLARE_OBJECT \
public: \
	static sl_object_type ObjectType(); \
	static sl_bool checkObjectType(sl_object_type type); \
	virtual sl_object_type getObjectType() const; \
	virtual sl_bool isInstanceOf(sl_object_type type) const;

#define SLIB_DEFINE_OBJECT_TYPE(CLASS) \
	char _g_objectId_##CLASS[] = #CLASS; \
	sl_object_type CLASS::ObjectType() { return _g_objectId_##CLASS; } \

#define SLIB_DEFINE_ROOT_OBJECT(CLASS) \
	SLIB_DEFINE_OBJECT_TYPE(CLASS) \
	sl_bool CLASS::checkObjectType(sl_object_type type) { return type == _g_objectId_##CLASS; } \
	sl_object_type CLASS::getObjectType() const { return _g_objectId_##CLASS; } \
	sl_bool CLASS::isInstanceOf(sl_object_type type) const { return type == _g_objectId_##CLASS; }

#define SLIB_DEFINE_OBJECT(CLASS, BASE) \
	SLIB_DEFINE_OBJECT_TYPE(CLASS) \
	sl_bool CLASS::checkObjectType(sl_object_type type) { if (type == _g_objectId_##CLASS) return sl_true; return BASE::checkObjectType(type); } \
	sl_object_type CLASS::getObjectType() const { return _g_objectId_##CLASS; } \
	sl_bool CLASS::isInstanceOf(sl_object_type type) const { if (type == _g_objectId_##CLASS) return sl_true; return BASE::checkObjectType(type); }

#define SLIB_TEMPLATE_OBJECT(BASE, ID) \
public: \
	static sl_object_type ObjectType() { return ID; } \
	static sl_bool checkObjectType(sl_object_type type) { if (type == ID) return sl_true; return BASE::checkObjectType(type); } \
	sl_object_type getObjectType() const { return ID; } \
	sl_bool isInstanceOf(sl_object_type type) const { if (type == ID) return sl_true; return BASE::checkObjectType(type); }

#define SLIB_REF_WRAPPER_NO_OP(WRAPPER, ...) \
public: \
	static sl_object_type ObjectType() { return __VA_ARGS__::ObjectType(); } \
	SLIB_INLINE WRAPPER() {} \
	SLIB_INLINE WRAPPER(sl_null_t) {} \
	SLIB_INLINE WRAPPER(__VA_ARGS__* obj) : ref(obj) {} \
	SLIB_INLINE WRAPPER(const WRAPPER& other) : ref(other.ref) {} \
	SLIB_INLINE WRAPPER(WRAPPER&& other) : ref(Move(other.ref)) {} \
	WRAPPER(const Atomic<WRAPPER>& other) : ref(*(reinterpret_cast<const AtomicRef<__VA_ARGS__>*>(&other))) {} \
	WRAPPER(Atomic<WRAPPER>&& other) : ref(Move(*(reinterpret_cast<AtomicRef<__VA_ARGS__>*>(&other)))) {} \
	SLIB_INLINE static const WRAPPER& null() { return *(reinterpret_cast<WRAPPER const*>(&_Ref_Null)); } \
	SLIB_INLINE sl_bool isNull() const { return ref.isNull(); } \
	SLIB_INLINE sl_bool isNotNull() const { return ref.isNotNull(); } \
	void setNull() { ref.setNull(); } \
	WRAPPER& operator=(sl_null_t) { ref.setNull(); return *this; } \
	WRAPPER& operator=(__VA_ARGS__* obj) { ref = obj; return *this; } \
	WRAPPER& operator=(const WRAPPER& other) { ref = other.ref; return *this; } \
	WRAPPER& operator=(WRAPPER&& other) { ref = Move(other.ref); return *this; } \
	WRAPPER& operator=(const Atomic<WRAPPER>& other) { ref = *(reinterpret_cast<const AtomicRef<__VA_ARGS__>*>(&other)); return *this; } \
	WRAPPER& operator=(Atomic<WRAPPER>&& other) { ref = Move(*(reinterpret_cast<AtomicRef<__VA_ARGS__>*>(&other))); return *this; }

#define SLIB_REF_WRAPPER(WRAPPER, ...) \
	SLIB_REF_WRAPPER_NO_OP(WRAPPER, __VA_ARGS__) \
	sl_bool operator==(const WRAPPER& other) const { return ref._ptr == other.ref._ptr; } \
	sl_bool operator==(const Atomic<WRAPPER>& other) const { return ref._ptr == (reinterpret_cast<const AtomicRef<__VA_ARGS__>*>(&other))->_ptr; } \
	sl_bool operator!=(const WRAPPER& other) const { return ref._ptr != other.ref._ptr; } \
	sl_bool operator!=(const Atomic<WRAPPER>& other) const { return ref._ptr != (reinterpret_cast<const AtomicRef<__VA_ARGS__>*>(&other))->_ptr; }


#define SLIB_ATOMIC_REF_WRAPPER_NO_OP(...) \
public: \
	Atomic() {} \
	Atomic(sl_null_t) {} \
	Atomic(__VA_ARGS__* obj) : ref(obj) {} \
	Atomic(typename RemoveAtomic<Atomic>::Type const& other) : ref(*(reinterpret_cast<const Ref<__VA_ARGS__>*>(&other))) {} \
	Atomic(typename RemoveAtomic<Atomic>::Type&& other) : ref(Move(*(reinterpret_cast<Ref<__VA_ARGS__>*>(&other)))) {} \
	Atomic(const Atomic& other) : ref(other.ref) {} \
	Atomic(Atomic&& other) : ref(Move(other.ref)) {} \
	sl_bool isNull() const { return ref.isNull(); } \
	sl_bool isNotNull() const { return ref.isNotNull(); } \
	void setNull() { ref.setNull(); } \
	Atomic& operator=(sl_null_t) { ref.setNull(); return *this; } \
	Atomic& operator=(__VA_ARGS__* obj) { ref = obj; return *this; } \
	Atomic& operator=(typename RemoveAtomic<Atomic>::Type const& other) { ref = *(reinterpret_cast<const Ref<__VA_ARGS__>*>(&other)); return *this; } \
	Atomic& operator=(typename RemoveAtomic<Atomic>::Type&& other) { ref = Move(*(reinterpret_cast<Ref<__VA_ARGS__>*>(&other))); return *this; } \
	Atomic& operator=(const Atomic& other) { ref = other.ref; return *this; } \
	Atomic& operator=(Atomic&& other) { ref = Move(other.ref); return *this; }

#define SLIB_ATOMIC_REF_WRAPPER(...) \
	SLIB_ATOMIC_REF_WRAPPER_NO_OP(__VA_ARGS__) \
	sl_bool operator==(typename RemoveAtomic<Atomic>::Type const& other) const { return ref._ptr == (reinterpret_cast<const Ref<__VA_ARGS__>*>(&other))->_ptr; } \
	sl_bool operator==(const Atomic& other) const { return ref._ptr == other.ref._ptr; } \
	sl_bool operator!=(typename RemoveAtomic<Atomic>::Type const& other) const { return ref._ptr != (reinterpret_cast<const Ref<__VA_ARGS__>*>(&other))->_ptr; } \
	sl_bool operator!=(const Atomic& other) const { return ref._ptr != other.ref._ptr; }

#endif
