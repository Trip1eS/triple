#include <catch2/catch_all.hpp>
#include <vector>
import triple.all;

struct Object {
    int x;
};

constexpr size_t entity_count = 1000000;

TEST_CASE("Benchmark") {
    BENCHMARK_ADVANCED("ecs-system")
    (Catch::Benchmark::Chronometer meter) {
        using namespace triple;
        World world;
        for (size_t i = 0; i < entity_count; i++) {
            Entity entity = world.entity();
            world.add_component(entity, Object {1});
        }
        auto query = world.query<Object>();
        meter.measure([&query] {
            size_t result = 0;
            for (auto [object] : query) {
                result += object.x;
            }
            return result;
        });
    };

    BENCHMARK_ADVANCED("ecs-archetype")
    (Catch::Benchmark::Chronometer meter) {
        using namespace triple;
        Archetype archetype(0, {&type<Object>()});
        Object obj {1};
        for (size_t i = 0; i < entity_count; i++) {
            archetype.add_entity(i);
            archetype.set_component(i, type<Object>(), &obj);
        }
        meter.measure([&archetype] {
            size_t result = 0;
            Object* ptr = (Object*)archetype.get_component(0, type<Object>());
            for (size_t i = 0; i < entity_count; i++) {
                result += ptr->x;
                ptr++;
            }
            return result;
        });
    };

    BENCHMARK_ADVANCED("vector-pointer")
    (Catch::Benchmark::Chronometer meter) {
        std::vector<Object*> objs;
        objs.reserve(entity_count);
        for (size_t i = 0; i < entity_count; i++) {
            objs.push_back(new Object {1});
        }
        meter.measure([&objs] {
            size_t result = 0;
            for (const auto& obj : objs) {
                result += obj->x;
            }
            return result;
        });
    };

    BENCHMARK_ADVANCED("vector-contiguous")
    (Catch::Benchmark::Chronometer meter) {
        std::vector<Object> objs;
        objs.reserve(entity_count);
        for (size_t i = 0; i < entity_count; i++) {
            objs.push_back(Object {1});
        }
        meter.measure([&objs] {
            size_t result = 0;
            for (const auto& obj : objs) {
                result += obj.x;
            }
            return result;
        });
    };
}

// using namespace triple;
// void benchmark(Query<Object>& query) {
//     for (int i = 0; i < 1000; i++) {
//         volatile size_t result = 0;
//         for (auto [object] : query) {
//             result += object.x;
//         }
//     }
// }

// int main() {
//     World world;
//     for (size_t i = 0; i < 100000; i++) {
//         Entity entity = world.entity();
//         world.add_component(entity, Object {1});
//     }
//     auto query = world.query<Object>();
//     benchmark(query);

//     return 0;
// }
