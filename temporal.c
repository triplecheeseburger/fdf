#include "fdf.h"
//#include "fdf_bonus.h"
//
//void	print_cur_map(t_data *data)
//{
//	printf("=================cur_map=================\n");
//	for (int i = 0; i < data->height; i++)
//	{
//		for (int j = 0; j < data->width; j++)
//			printf("%d ", data->cur_map[i][j]);
//		printf("\n");
//	}
//	printf("=====================================\n\n");
//}

void	print_map(t_data *data)
{
	printf("===============map===============\n");
	for (int i = 0; i < data->height; i++)
	{
		for (int j = 0; j < data->width; j++)
			printf("%d ", data->map[i][j]);
		printf("\n");
	}
	printf("=====================================\n\n");
}

void	print_color_map(t_data *data)
{
	printf("==============color_map==============\n");
	for (int i = 0; i < data->height; i++)
	{
		for (int j = 0; j < data->width; j++)
			printf("%d ", data->color_map[i][j]);
		printf("\n");
	}
	printf("=====================================\n\n");
}