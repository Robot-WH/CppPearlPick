

include_directories( include/ )

#message( WARNING "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(tuple src/tuple/tuple.cpp  )
target_link_libraries(tuple
)

add_executable(test_remove_reference src/test/test_remove_reference.cpp  )
target_link_libraries(test_remove_reference
)


