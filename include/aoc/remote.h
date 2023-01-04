#ifndef ADVENTOFCODE2019_REMOTE_H
#define ADVENTOFCODE2019_REMOTE_H

#include <string>
#include <filesystem>
#include "types.h"

namespace aoc::remote {
    std::string get_session_key();

    struct data {
        year_t year;
        day_t day;

        data(year_t year, day_t day) : year(year), day(day) {}

        void download() const;

        std::filesystem::path path() const;

        std::filesystem::path get() const;
    };
}
#endif //ADVENTOFCODE2019_REMOTE_H
