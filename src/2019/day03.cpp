#include "aoc/aoc.h"
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <range/v3/all.hpp>
namespace rv = ranges::views;
namespace {
    typedef std::pair<char, int> step;
    namespace grammar {
        namespace dsl = lexy::dsl;

        struct instruction {
            static constexpr auto symbols = lexy::symbol_table<char>
                                                    .map < LEXY_SYMBOL("U") > ('U')
                                                    .map < LEXY_SYMBOL("D") > ('D')
                                                    .map < LEXY_SYMBOL("L") > ('L')
                                                    .map < LEXY_SYMBOL("R") > ('R');

            static constexpr auto rule = dsl::symbol<symbols> + dsl::integer<int>;
            static constexpr auto value = lexy::construct<step>;
        };

        struct wire {
            static constexpr auto rule = dsl::terminator(dsl::eol).opt_list(dsl::p<instruction>, dsl::sep(dsl::comma));
            static constexpr auto value = lexy::as_list<std::vector<step>>;
        };
        struct parser {
            static constexpr auto rule = dsl::times<2>(dsl::p<wire>);
            static constexpr auto value = lexy::construct<std::pair<std::vector<step>, std::vector<step>>>;
        };
    }
    AOC_IMPL(2019, 3) {
        using parser = grammar::parser;
        typedef std::pair<int, int> point;
        static constexpr auto part1 = [](auto wires) {
            auto [wire1, wire2] = wires;

            std::unordered_set < point > points1;

            point curr(0, 0);

            for (const auto [dir, steps]: wire1) {
                for (int i = 0; i < steps; i++) {
                    switch (dir) {
                        case 'U':
                            curr = {curr.first, curr.second + 1};
                            break;
                        case 'D':
                            curr = {curr.first, curr.second - 1};
                            break;
                        case 'L':
                            curr = {curr.first - 1, curr.second};
                            break;
                        case 'R':
                            curr = {curr.first + 1, curr.second};
                            break;
                        default:
                            throw std::runtime_error("Unexpected Direction");
                    }
                    points1.insert(curr);
                }
            }

            std::unordered_set < point > points2;
            curr = {0, 0};
            for (const auto [dir, steps]: wire2) {
                for (int i = 0; i < steps; i++) {
                    switch (dir) {
                        case 'U':
                            curr = {curr.first, curr.second + 1};
                            break;
                        case 'D':
                            curr = {curr.first, curr.second - 1};
                            break;
                        case 'L':
                            curr = {curr.first - 1, curr.second};
                            break;
                        case 'R':
                            curr = {curr.first + 1, curr.second};
                            break;
                        default:
                            throw std::runtime_error("Unexpected Direction");
                    }
                    points2.insert(curr);
                }
            }

            std::vector<point> intersection;


            for (const auto& p : points1) {
                if (points2.contains(p)) {
                    intersection.push_back(p);
                }
            }

            auto dist = intersection | rv::transform([](const auto& p) {
                return abs(p.first) + abs(p.second);
            });
            return *std::min_element(dist.begin(), dist.end());
        };

        static std::unordered_map<point, int> simulate_steps(const std::vector<step>& wire) {
            std::unordered_map<point, int> point_steps;
            point curr(0, 0);
            int steps = 0;
            for (const auto &[dir, num]: wire) {
                for (int i = 0; i < num; i++) {
                    switch (dir) {
                        case 'U':
                            curr = {curr.first, curr.second + 1};
                            break;
                        case 'D':
                            curr = {curr.first, curr.second - 1};
                            break;
                        case 'L':
                            curr = {curr.first - 1, curr.second};
                            break;
                        case 'R':
                            curr = {curr.first + 1, curr.second};
                            break;
                        default:
                            throw std::runtime_error("Unexpected Direction");
                    }
                    steps++;
                    if (!point_steps.contains(curr)) {
                        point_steps.insert({curr, steps});
                    }
                }
            }
            return point_steps;
        }
        static constexpr auto part2 = [](auto wires) {
            auto [wire1, wire2] = wires;

            std::unordered_map<point, int> point_steps1 = implementation::simulate_steps(wire1);

            std::unordered_map<point, int> point_steps2 = implementation::simulate_steps(wire2);
            std::vector<int> intersection;

            for (const auto& [p, s] : point_steps1) {
                if (point_steps2.contains(p)) {
                    intersection.push_back(s + point_steps2[p]);
                }
            }

            return *std::min_element(intersection.begin(), intersection.end());
        };
    };
}