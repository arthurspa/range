#pragma once

#include "range_fwd.h"

#ifndef RANGE_PROPOSAL_BUILD_STANDALONE
	#include "Library/ErrorReporting/assert_fwd.h"
#else
	
    #define _CHECKS
    #ifndef _ASSERT
		#include <cassert>
		#define _ASSERT(...) assert((__VA_ARGS__))
	#endif
	#ifndef _ASSERTE
		#define _ASSERTE(...) ((void)0)
	#endif
	#ifndef _ASSERTDEBUG
		#define _ASSERTDEBUG(...) _ASSERT((__VA_ARGS__))
	#endif
	#ifndef _ASSERTFALSE
		#define _ASSERTFALSE _ASSERT(false);
	#endif
	#ifndef _ASSERTNOTIFYFALSE
		#define _ASSERTNOTIFYFALSE _ASSERTFALSE
	#endif
	#ifndef _ASSERTEQUAL
			#define _ASSERTEQUAL(a, b) assert((a)==(b))
	#endif
	#ifndef VERIFYEQUAL
		#define VERIFYEQUAL( expr, constant ) (expr)
	#endif
	#ifndef VERIFY
		#define VERIFY( expr ) (expr)
	#endif

	#define RANGE_UNITTEST_OUTPUT

	// standalone replacements for assign.h
	#include <boost/algorithm/string/compare.hpp>
	typedef boost::is_equal fn_equal_to;
	typedef boost::is_less fn_less;
	typedef boost::is_not_greater fn_less_equal;

	// standalone replacements for functors.h
	struct fn_logical_not {
		template<typename Lhs> auto operator()( Lhs && lhs ) const -> decltype(!std::forward<Lhs>(lhs)) { return !std::forward<Lhs>(lhs); }
	};

    #define SWITCH_NO_DEFAULT( ... ) \
	switch( __VA_ARGS__ ) { \
	default: \
		_ASSERT( false );

	#define switch_no_default( ... ) SWITCH_NO_DEFAULT( __VA_ARGS__ ) /##/

#endif

//-----------------------------------------------------------------------------------------------------------------------------
// Compiler bug/missing feature workarounds
#ifdef CLANG
	#define HAS_VARIADIC_TEMPLATES
	#define THIS_IN_DECLTYPE this->

#else // this is currently MSVC
	#define THIS_IN_DECLTYPE               // MSVC doesn't allow this in a decltype() context (but should)
#endif

//-----------------------------------------------------------------------------------------------------------------------------
// STATIC_ASSERT_OVERLOAD_NOT_SELECTED
//
// see equal.h for a usage example

namespace RANGE_PROPOSAL_NAMESPACE {
	struct wrong_overload_selected {};
}

#define STATIC_ASSERT_OVERLOAD_NOT_SELECTED(NAME, EXPR, MSG, RETURN_T, ...)                                                   \
	typename std::enable_if< EXPR,  RETURN_T>::type NAME(__VA_ARGS__) {                                                       \
		static_assert(!(EXPR), MSG);                                                                                          \
		return std::declval<RETURN_T>();                                                                                      \
	}
