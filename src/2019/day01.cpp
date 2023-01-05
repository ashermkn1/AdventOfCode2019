#include "aoc/aoc.h"
#include <range/v3/all.hpp>

namespace rv = ranges::views;
namespace {
    namespace grammar {
        namespace dsl = lexy::dsl;

        struct number {
            static constexpr auto rule = dsl::sign + dsl::integer<std::int64_t> + dsl::newline;
            static constexpr auto value = lexy::as_integer<std::int64_t>;
        };

        struct parser {
            static constexpr auto rule = dsl::terminator(dsl::eof).opt_list(dsl::p<number>);
            static constexpr auto value = lexy::as_list<std::vector<std::int64_t>>;
        };
    }
    long long calc_fuel(long long fuel) {
        if (fuel <= 0) {
            return 0;
        } else {
            return fuel + calc_fuel(fuel / 3 - 2);
        }
    }
    AOC_IMPL(2019, 1) {
        using parser = grammar::parser;

        static constexpr auto part1 = [](auto data) {
            auto fuel_costs = data | rv::transform([](const auto &num) {
                return num / 3 - 2;
            });

            return std::reduce(fuel_costs.begin(), fuel_costs.end());
        };

        static constexpr auto part2 = [](auto data) {
            auto fuel_costs = data | rv::transform([](const auto& num) {
                return calc_fuel(num / 3 - 2);
            });

            return std::reduce(fuel_costs.begin(), fuel_costs.end());
        };
    };

    AOC_TEST_CASE(0, 0, R"()")
}