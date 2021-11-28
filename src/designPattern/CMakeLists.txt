
include_directories( include/ )

add_executable(strategy src/strategy/main.cpp  )
target_link_libraries(strategy
)

add_executable(factory src/factory/main.cpp  )
target_link_libraries(factory
)

add_executable(observer src/observer/main.cpp  )
target_link_libraries(observer
)
add_executable(observer2 src/observer/main2.cpp  )
target_link_libraries(observer
)

add_executable(decorator src/decorator/main.cpp  )
target_link_libraries(decorator
)