target("triple_core")
    set_kind("moduleonly")
    add_files("*.mpp")
    add_deps(
        "triple_app",
        "triple_base",
        "triple_ecs"
    )