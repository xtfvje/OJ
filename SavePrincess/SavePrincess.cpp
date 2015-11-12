#include "SavePrincess.h"
#include <iostream>

using namespace std;

static void init_room(struct room_info* r)
{
	memset(r, 0, sizeof(*r));
}


/*
* ����ָ���ӵ�ָ��,����Ϊǽ�򷵻�NULL
* M*N ���Թ���max_row = M - 1, max_col = N - 1
*/
static struct room_info* get_child(struct room_info* maze, int max_row, int max_col,
                                   struct room_info* cur_room, enum DIRECTION direct)
{
	int row = 0;
	int col = 0;
	int idx = 0;
	struct room_info* child = NULL;

	if (NULL == maze || NULL == cur_room)
	{
		return NULL;
	}

	row = cur_room->row;
	col = cur_room->col;

	switch (direct)
	{
	case D_UP:
		if (row <= 0)
		{
			return NULL;
		}

		row--;
		break;
	case D_DOWN:
		if (row >= max_row)
		{
			return NULL;
		}
		row++;

		break;
	case D_LEFT:
		if (col <= 0)
		{
			return NULL;
		}
		col--;

		break;
	case D_RIGHT:
		if (col >= max_col)
		{
			return NULL;
		}
		col++;

		break;
	default:
		break;
	}

	idx = row * (max_col + 1) + col;

	child = maze + idx;
	if (TYPE_WINDOW == child->type)
	{
		return NULL;
	}
	else
	{
		return child;
	}
}

 /* �ɹ�����ָ��S��ָ�룬 ʧ�ܷ���NULL*/
static struct room_info* init_maze(struct room_info* maze, int M, int N, char* maze_data)
{
	int row = 0;
	int col = 0;
	struct room_info* prince = NULL;

	/* ��һ��ʶ��ǽ��,ȷ������ */
	for (row = 0; row < M; row++)
	{
		for (col = 0; col < N; col++)
		{
			int idx = row * N + col;
			char c = *(maze_data + idx);

			init_room(maze + idx);

			maze[idx].row = row;
			maze[idx].col = col;

		    switch (c)
		    {
		    case '.':
		 	   maze[idx].type = TYPE_ROAD;
		 	   break;
		    case '*':
		 	   maze[idx].type = TYPE_WINDOW;
		 	   break;
		    case 'S':
		 	   prince = maze + idx;
		 	   maze[idx].type = TYPE_PRINCE;
		 	   break;
		    case 'P':
		 	   maze[idx].type = TYPE_PRINCESS;
		 	   break;
		    default:
		 	   return NULL;
		    }
		}
	}

   /*�ڶ��齨��ͼ*/
   for (row = 0; row < M; row++)
   {
	   for (col = 0; col < N; col++)
	   {
		   int idx = row * N + col;

		   maze[idx].child[D_UP] = get_child(maze, M - 1, N - 1, maze + idx, D_UP);
		   maze[idx].child[D_DOWN] = get_child(maze, M - 1, N - 1, maze + idx, D_DOWN);
		   maze[idx].child[D_LEFT] = get_child(maze, M - 1, N - 1, maze + idx, D_LEFT);
		   maze[idx].child[D_RIGHT] = get_child(maze, M - 1, N - 1, maze + idx, D_RIGHT);
	   }
	 }

	return prince;
}


static void init_node_info(struct node_info* info)
{
	memset(info, 0, sizeof(*info));
}

static void queue_push(struct node_info* queue, struct room_info* room,
	int cur_level, struct node_info* parent)
{
	struct node_info* new_node = NULL;

	if (NULL == room)
	{
		return;
	}

	new_node = (struct node_info*)malloc(sizeof(struct node_info));
	init_node_info(new_node);

	new_node->level = cur_level + 1;
	new_node->parent = parent;
	new_node->room = room;

	while (queue != NULL)
	{
		if (NULL == queue->next)
		{
			queue->next = new_node;
			break;
		}

		queue = queue->next;
	}
}

static void queue_release(struct node_info* queue)
{
	struct node_info* tmp = NULL;
	while (queue != NULL)
	{
		tmp = queue->next;
		free(queue);

		queue = tmp;
	}
}


/* �ҵ�princess������Ҫ�Ĳ���
* �Ҳ������߳�����-1
*/
static int find_princess(struct room_info* maze, struct room_info* prince)
{
	struct node_info* queue = NULL;
	struct node_info* cur_step = NULL;

	queue = (struct node_info*)malloc(sizeof(struct node_info));
	if (NULL == queue)
	{
		return -1;
	}

	init_node_info(queue);
	queue->parent = NULL;
	queue->level = 0;
	queue->room = prince;

	cur_step = queue;
	while (cur_step != NULL)
	{
		struct room_info* cur_room = cur_step->room;
		if (NULL == cur_room)
		{
			fprintf(stderr, "IT CAN NOT HAPPEN!\n");
			break;
		}

		if (TYPE_PRINCESS == cur_room->type)
		{
			struct node_info* tmp = cur_step;
			/* we find princess :) */
			fprintf(stdout, "\nThe way back to prince... \n");
			while (tmp != NULL)
			{
				fprintf(stdout, "(%d, %d) ", tmp->room->row, tmp->room->col);

				tmp = tmp->parent;
			}
			fprintf(stdout, "\n");

			queue_release(queue);
			return cur_step->level;
		}
		else if (TYPE_ROAD == cur_room->type
			|| TYPE_PRINCE == cur_room->type)
		{
			struct room_info* tmp = NULL;

			if (1 == cur_room->pass_by)
			{
				cur_step = cur_step->next;
				continue;
			}

			cur_room->pass_by = 1;

			/* �Ѻ����Ƕ������к��� */
			tmp = cur_room->child[D_UP];
			queue_push(queue, tmp, cur_step->level, cur_step);

			tmp = cur_room->child[D_DOWN];
			queue_push(queue, tmp, cur_step->level, cur_step);

			tmp = cur_room->child[D_LEFT];
			queue_push(queue, tmp, cur_step->level, cur_step);

			tmp = cur_room->child[D_RIGHT];
			queue_push(queue, tmp, cur_step->level, cur_step);
		}
		else
		{
			fprintf(stderr, "Wired!\n");
		}

		cur_step = cur_step->next;
	}

	queue_release(queue);
	return -1;
}

int save_princess(int M, int N, char* maze_data, int time)
{
	struct room_info* maze = NULL;
	struct room_info* prince = NULL;
	int time_need = 0;

	if (M <= 1 || N <= 1 || NULL == maze_data || 0 == time)
	{
		return 0;
	}

	maze = (struct room_info*)malloc(M * N * sizeof(struct room_info));
	if (NULL == maze)
	{
		return 0;
	}

	prince = init_maze(maze, M, N, maze_data);
	if (NULL == prince)
	{
		/*������������*/
		return 0;
	}

	time_need = find_princess(maze, prince);
	if (-1 == time_need)
	{
		return 0;
	}
	else if (time_need > time)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}