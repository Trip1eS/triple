target("triple_graphics_opengl")
    set_kind("moduleonly")
    add_files("*.mpp")
    -- add_files("*.cpp")
    add_deps("glad", "triple_graphics", "triple_app")
