target("triple_refl")
    set_kind("moduleonly")
    add_files("*.mpp")
    add_deps("triple_base")
    add_includedirs(".", {public = true})

target("triple_refl-tests")
    set_kind("binary")
    add_files("tests/*.test.cpp")
    add_packages("catch2")
    add_deps("triple_refl")
