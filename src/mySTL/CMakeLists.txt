cmake_minimum_required(VERSION 3.0.2)

# add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-O3")
# set(CMAKE_CXX_FLAGS "-fno-elide-constructors")    # 关闭返回值优化 


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

add_executable(test_list src/test/container/list_test.cpp  )
target_link_libraries(test_list
)

add_executable(test_any src/test/test_any.cpp )
target_link_libraries(test_any
)

add_executable(test_vector src/test/container/vector_test.cpp  )
target_link_libraries(test_vector
-lpthread -luuid
)

add_executable(test_push_back_emplace_back src/test/container/test_push_back_emplace_back.cpp  )
target_link_libraries(test_push_back_emplace_back
)


add_executable(test_copy_elision src/test/test_copy_elision.cpp)
target_link_libraries(test_copy_elision
)



