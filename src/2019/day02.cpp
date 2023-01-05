#include "aoc/aoc.h"

namespace {
    namespace grammar {
        namespace dsl = lexy::dsl;

        struct number {
            static constexpr auto rule = dsl::sign + dsl::integer<std::int64_t>;
            static constexpr auto value = lexy::as_integer<std::int64_t>;
        };

        struct parser {
            static constexpr auto rule = dsl::list(dsl::p<number>, dsl::sep(dsl::comma)) + dsl::eol;
            static constexpr auto value = lexy::as_list<std::vector<std::int64_t>>;
        };
    }
    AOC_IMPL(2019, 2) {
        using parser = grammar::parser;

        static constexpr auto part1 = [](auto data) {
            data[1] = 12;
            data[2] = 2;
            aoc::intcode::run_program(data);
            return data[0];
        };
        static constexpr auto part2 = [](auto data) {
            for (auto noun = 0; noun < 100; noun++) {
                for (auto verb = 0; verb < 100; verb++) {
                    auto test(data);
                    test[1] = noun;
                    test[2] = verb;
                    aoc::intcode::run_program(test);
                    if (test[0] == 19690720) {
                        return 100 * noun + verb;
                    }
                }
            }
            return -1;
        };
    };

    AOC_TEST_CASE(0, 0, R"()")
}