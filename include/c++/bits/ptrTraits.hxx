// SPDX-License-Identifier: BSD-3-Clause
#ifndef BITS_PTR_TRAITS_HXX
#define BITS_PTR_TRAITS_HXX

#include <type_traits>

namespace std
{
	namespace impl
	{
		struct undefined_t;

		template<typename T> struct get_first_arg { using type = undefined_t; };
		template<template<typename, typename...> typename template_t, typename T, typename... types_t>
			struct get_first_arg<template_t<T, types_t...>> { using type = T; };
		template<typename T> using get_first_arg_t = typename get_first_arg<T>::type;

		template<typename T> using make_not_void = std::conditional_t<std::is_void_v<T>, undefined_t, T>;
	} // namespace impl

	template<typename ptr_t> struct pointer_traits
	{
	private:
		template<typename T> using elem_t = typename T::element_type;
		template<typename T> using diff_t = typename T::difference_type;

	public:
		using pointer = ptr_t;
		using element_type = impl::detected_or_t<impl::get_first_arg_t<ptr_t>, elem_t, ptr_t>;
		using difference_type = impl::detected_or_t<ptrdiff_t, diff_t, ptr_t>;

		static ptr_t pointer_to(impl::make_not_void<element_type> &elem) { return ptr_t::pointer_to(elem); }

		static_assert(!is_same_v<element_type, impl::undefined_t>,
			"pointer type defines element_type or is like SomePointer<T, Args>");
	};
} // namespace std

#endif /*BITS_PTR_TRAITS_HXX*/
