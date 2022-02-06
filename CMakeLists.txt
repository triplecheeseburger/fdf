cmake_minimum_required(VERSION 3.21)
project(fdf)

include_directories(.)
include_directories(mlx)
link_directories(/Users/hakim/fdf/mlx)
link_directories(/Users/hakim/fdf/libft)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -I./includes")

add_executable(fdf
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        parse.c
        parse_color.c
        fdf.c
        temporal.c
        utils_free.c
        utils_map.c
        xiaolin_wu.c
        color.c
        drawing_utils.c
        drawing.c
        prepare.c
        projection.c
        input_handler.c)

target_link_libraries (fdf mlx)
target_link_libraries (fdf ft)
