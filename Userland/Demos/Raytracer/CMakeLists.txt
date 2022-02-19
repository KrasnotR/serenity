serenity_component(
        Raytracer
        TARGETS Raytracer
)

set(SOURCES
        Raytracer.cpp
        )

serenity_app(Raytracer ICON app-raytracer)
target_link_libraries(Raytracer LibGUI LibCore LibGfx LibMain)
