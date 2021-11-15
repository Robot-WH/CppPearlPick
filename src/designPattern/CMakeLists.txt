
include_directories( include/ )

add_executable(strategy src/strategy/main.cpp  )
target_link_libraries(strategy
)

add_executable(factory src/factory/main.cpp  )
target_link_libraries(factory
)