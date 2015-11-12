#pragma once
/* 题目描述：
       公主被魔王抓走了，王子需要拯救出美丽的公主。他进入了魔王的城堡，魔王的城堡是一座很大的迷宫。
   为了使问题简单化，我们假设这个迷宫是一个 N*M 的二维方格。迷宫里有一些墙，王子不能通过。王子只能
   移动到相邻（上下左右四个方向)的方格内，并且一秒只能移动一步，就是说，如果王子在(x,y）一步只能移
   动到(x-1,y),(x+1,y),(x,y-1),(x,y+1)其中的一个位置上。地图由‘S’，‘P’，‘.’，‘*’四种符号构
   成，‘.’表示王子可以通过，‘*’表示墙，王子不能通过；'S'表示王子的位置；‘P’表示公主的位置；T
   表示公主存活的剩余时间，王子必须在T秒内到达公主的位置，才能救活公主。
*/

const int M = 10;
const int N = 10;

// 行走方向
enum DIRECTION
{
	D_UP = 0,    // 上
	D_DOWN,      // 下
	D_LEFT,      // 左
	D_RIGHT,     // 右
	D_SIZE
};

enum ROOM_TYPE
{
	TYPE_ROAD,       // 路，表示可以通过
	TYPE_WINDOW,     // 墙，不能通过
	TYPE_PRINCE,     // 王子第位置
	TYPE_PRINCESS,   // 公主的位置
};

struct room_info
{
	int row;
	int col;
	enum ROOM_TYPE type;
	int pass_by;
	struct room_info* child[D_SIZE];
};

struct node_info
{
	int level;
	struct room_info* room;
	struct node_info* parent;

	struct node_info* next;
};

static void init_room(struct room_info* r);

static struct room_info* get_child(struct room_info* maze, int max_row, int max_col,
                                   struct room_info* cur_room, enum DIRECTION direct);

static struct room_info* init_maze(struct room_info* maze, int M, int N, char* maze_data);

static void init_node_info(struct node_info* info);

static void queue_push(struct node_info* queue, struct room_info* room,
	                   int cur_level, struct node_info* parent);

static void queue_release(struct node_info* queue);

static int find_princess(struct room_info* maze, struct room_info* prince);

int save_princess(int M, int N, char* maze_data, int time);