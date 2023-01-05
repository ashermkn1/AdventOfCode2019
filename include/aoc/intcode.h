#ifndef ADVENTOFCODE2019_INTCODE_H
#define ADVENTOFCODE2019_INTCODE_H

#include <vector>

namespace aoc::intcode {
    typedef std::vector<long long> program_t;

    void run_program(program_t &program);
}


#endif //ADVENTOFCODE2019_INTCODE_H
