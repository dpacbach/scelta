// Copyright (c) 2017 Vittorio Romeo
// MIT License |  https://opensource.org/licenses/MIT
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include "../meta/always_false.hpp"
#include "../utils/optional_utils.hpp"
#include "./dispatch.hpp"

// Usage of C++17: nested `namespace`.
namespace scelta::traits::adt
{
    namespace impl
    {
        struct visit_optional_t
        {
            // clang-format off
            template <typename Tag, typename... Ts>
            constexpr auto operator()(Tag, Ts&&... xs)
                SCELTA_RETURNS(
                    ::scelta::impl::visit_optional(FWD(xs)...)
                )
            // clang-format on
        };
    }

    template <typename T>
    struct visit
    {
        static_assert(meta::always_false_v<T>,
            "`scelta::traits::adt::visit` not specialized for `T`.");
    };

    template <typename>
    struct valid
    {
        template <typename... Variants>
        constexpr auto operator()(Variants&&...)
        {
            return true;
        }
    };

    template <typename T>
    inline constexpr traits::impl::dispatch<visit<T>> visit_v{};

    template <typename T>
    inline constexpr traits::impl::dispatch<valid<T>> valid_v{};
}
