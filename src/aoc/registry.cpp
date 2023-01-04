#include "aoc/registry.h"

namespace aoc::registry {
    registry_t& get_registry() {
        static registry_t registry;
        return registry;
    }
}