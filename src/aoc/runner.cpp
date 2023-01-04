#include "aoc/runner.h"

#include "aoc/registry.h"
#include "aoc/remote.h"

namespace aoc {
    registry::implementation get_implementation(year_t year, day_t day) {
        auto &registry = registry::get_registry();
        auto implementation = registry.find({year, day});

        if (implementation == registry.end()) {
            std::ostringstream msg;
            msg << "No implementation registered for Dec " << day << "," << year;
            throw std::runtime_error(msg.str());
        }
        return implementation->second;
    }

    void run(year_t year, day_t day, std::ostream &out) {
        auto implementation = get_implementation(year, day);

        out << std::endl << "* Dec " << day << ", " << year << " *" << std::endl;

        auto input = remote::data(year, day).get();

        out << "=> Part 1: ";
        auto time1 = implementation.part1(input, out);
        out << std::endl;

        out << "=> Part 2: ";
        auto time2 = implementation.part2(input, out);
        out << std::endl;

        out << "=> Time (us): " << time1 << "/" << time2 << std::endl;
    }

    void run_all(year_t year, std::ostream &out) {
        std::size_t count = 0;
        for (const auto &impl: registry::get_registry()) {
            if (impl.first.first == year) {
                run(year, impl.first.second, out);
                count++;
            }
        }

        if (count == 0) {
            std::ostringstream msg;
            msg << "No implementations registered for Dec " << year;
            throw std::runtime_error(msg.str());
        }
    }
}