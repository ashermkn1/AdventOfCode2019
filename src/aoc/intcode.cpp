#include "aoc/intcode.h"

namespace aoc::intcode {
    void run_program(program_t& program) {
        for (int pos = 0; program[pos] != 99; pos += 4) {
            switch (program[pos]) {
                case 1:
                    program[program[pos + 3]] = program[program[pos + 1]] + program[program[pos + 2]];
                    break;
                case 2:
                    program[program[pos + 3]] = program[program[pos + 1]] * program[program[pos + 2]];
                    break;
            }
        }
    }
}