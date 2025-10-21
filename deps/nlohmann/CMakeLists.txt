# nlohmann/json library (header-only)
# This is a header-only library, so we just need to expose the include directory

add_library(nlohmann_json INTERFACE)

target_include_directories(nlohmann_json INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add an alias target for compatibility
add_library(nlohmann_json::nlohmann_json ALIAS nlohmann_json)

