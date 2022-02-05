cmake_minimum_required(VERSION 3.21)
project(fdf)

include_directories(.)
include_directories(mlx)
link_directories(/Users/hangyulkim/42/42cursus/2_circle/fdf/mlx)
link_directories(/Users/hangyulkim/42/42cursus/2_circle/fdf/libft)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -I./includes")

add_executable(fdf
        get_next_line/get_next_line.c
        get_next_line/get_next_line_utils.c
        parse/parse.c
        parse/parse_color.c
        fdf.c
        temporal.c
        utils_free.c
        utils_map.c)

target_link_libraries (fdf mlx)
target_link_libraries (fdf ft)
