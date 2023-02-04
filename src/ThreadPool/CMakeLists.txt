
add_executable(learn_promise_future test/learn_promise_future.cpp)
target_link_libraries(learn_promise_future
    pthread
)

add_executable(learn_async test/learn_async.cpp)
target_link_libraries(learn_async
    pthread
)

add_executable(test_thread_pool test/test_thread_pool.cpp)
target_link_libraries(test_thread_pool
    pthread
)





