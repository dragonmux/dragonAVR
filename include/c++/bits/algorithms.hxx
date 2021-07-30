// SPDX-License-Identifier: BSD-3-Clause
#ifndef BITS_ALGORITHMS_HXX
#define BITS_ALGORITHMS_HXX

namespace std
{
	template<typename iter_t, typename outputIter_t>
		constexpr inline outputIter_t copy(iter_t first, const iter_t last, outputIter_t result)
	{
		while (first != last)
			*result++ = *first++;
		return result;
	}
} // namespace std

#endif /*BITS_ALGORITHMS_HXX*/
