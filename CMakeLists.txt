cmake_minimum_required(VERSION 3.21)
project(fdf)

include_directories(./includes)
include_directories(mlx)
#link_directories(/Users/hakim/fdf/mlx)
#link_directories(/Users/hakim/fdf/libft)
link_directories(/Users/hangyulkim/42/42cursus/2_circle/fdf/mlx)
link_directories(/Users/hangyulkim/42/42cursus/2_circle/fdf/libft)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -I./includes")

add_executable(fdf
        srcs/get_next_line.c
        srcs/get_next_line_utils.c
        srcs/parse.c
        srcs/parse_color.c
        srcs/fdf.c
        srcs/utils_free.c
        srcs/xiaolin_wu.c
        srcs/color.c
        srcs/drawing_utils.c
        srcs/drawing.c
        srcs/prepare.c
        srcs/projection.c
        srcs/input_handler.c)

target_link_libraries (fdf mlx)
target_link_libraries (fdf ft)
