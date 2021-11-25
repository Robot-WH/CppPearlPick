include_directories( include/ )

#message( WARNING "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(test_remove_reference src/test/test_remove_reference.cpp  )
target_link_libraries(test_remove_reference
)

add_executable(test_move_forward src/test/test_move_forward.cpp  )
target_link_libraries(test_move_forward
)

add_executable(test_tuple src/test/test_tuple.cpp  )
target_link_libraries(test_tuple
)

add_executable(test_bind src/test/test_bind.cpp  )
target_link_libraries(test_bind
)

add_executable(test_function src/test/test_function.cpp  )
target_link_libraries(test_function
)


