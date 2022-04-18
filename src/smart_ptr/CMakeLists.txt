

include_directories( include/ )

#message( WARNING "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

add_executable(scoped_ptr scoped_ptr.cpp  )
target_link_libraries(scoped_ptr
)

add_executable(scoped_array scoped_array.cpp  )
target_link_libraries(scoped_array
)

add_executable(  shared_ptr shared_ptr.cpp  )
target_link_libraries( shared_ptr
)