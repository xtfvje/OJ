#pragma once
/* ��Ŀ������
       ������ħ��ץ���ˣ�������Ҫ���ȳ������Ĺ�������������ħ���ĳǱ���ħ���ĳǱ���һ���ܴ���Թ���
   Ϊ��ʹ����򵥻������Ǽ�������Թ���һ�� N*M �Ķ�ά�����Թ�����һЩǽ�����Ӳ���ͨ��������ֻ��
   �ƶ������ڣ����������ĸ�����)�ķ����ڣ�����һ��ֻ���ƶ�һ��������˵�����������(x,y��һ��ֻ����
   ����(x-1,y),(x+1,y),(x,y-1),(x,y+1)���е�һ��λ���ϡ���ͼ�ɡ�S������P������.������*�����ַ��Ź�
   �ɣ���.����ʾ���ӿ���ͨ������*����ʾǽ�����Ӳ���ͨ����'S'��ʾ���ӵ�λ�ã���P����ʾ������λ�ã�T
   ��ʾ��������ʣ��ʱ�䣬���ӱ�����T���ڵ��﹫����λ�ã����ܾȻ����
*/

const int M = 10;
const int N = 10;

// ���߷���
enum DIRECTION
{
	D_UP = 0,    // ��
	D_DOWN,      // ��
	D_LEFT,      // ��
	D_RIGHT,     // ��
	D_SIZE
};

enum ROOM_TYPE
{
	TYPE_ROAD,       // ·����ʾ����ͨ��
	TYPE_WINDOW,     // ǽ������ͨ��
	TYPE_PRINCE,     // ���ӵ�λ��
	TYPE_PRINCESS,   // ������λ��
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