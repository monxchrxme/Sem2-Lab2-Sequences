# Создаем интерфейсную библиотеку seq_lib.
# Ключевое слово INTERFACE означает, что эта библиотека header-only (состоит только из .hpp и .tpp).
# Она не компилируется в отдельный бинарник (.a или .lib), а существует только для того,
# чтобы элегантно передавать пути к заголовочным файлам всем, кто от нее зависит.
add_library(seq_lib INTERFACE)

# Говорим CMake: "Тот, кто прилинкует seq_lib, должен искать заголовочные файлы в текущей папке src".
target_include_directories(seq_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Создаем основной исполняемый файл нашего приложения
add_executable(laba2_app main.cpp)

# Линкуем приложение с интерфейсной библиотекой.
# Теперь main.cpp "видит" все наши папки (memory, sequences, interfaces) без указания длинных путей.
target_link_libraries(laba2_app PRIVATE seq_lib)