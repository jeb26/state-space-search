#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define BF 4

#define DFS 0
#define BFS 1
#define BEST 2
#define BB 3
#define ASTAR 4

struct node {
	int loc[N+1][N];
	struct node *next;
};
struct node *start, *goal;
struct node *init(), *expand();
char strategy[10];
int flag;
/*
   Protoypes for functions that return ints
 */
int expand_a_node(), length();

/*
   Prototypes for void functions
 */
void up(), dn(), lt(), rt(), swap(), print_array(), init_2D(), init_3D(), print_a_node();

int main(int argc, char **argv)
{

	//int nums[N] = {1, 5, 1, 15 ,15 ,6 ,7 ,8 ,4 ,9};
	int succ_buf[BF][N+1][N];

	start = init(argc, argv);

	expand_a_node(start->loc, succ_buf);

	printf("intial:\n");
	print_a_node(start);
	print_array("after down move", succ_buf[0]);
	print_array("after right move", succ_buf[1]);
	print_array("after up move", succ_buf[2]);
	print_array("after left move", succ_buf[3]);
	/*
	int nums[N][N], len;
	init_2D(nums);
	print_array(nums);

	//find elem in 2D array
	int i,j, found = 0;
	for(i = 0; (i < N) && !found; i++)
	{
		for(j = 0; (j < N) && !found; j++)
		{
			if(nums[i][j] == 2)
			{
				printf("i:%d j:%d\n", i, j);
				found = 1;
			}
		}
	}
	i--;
	j--;

	//perform dn move
	int temp = nums[i][j];
	nums[i][j] = nums[i+1][j];
	nums[i+1][j] = temp;

	printf("After swap:\n");
	print_array(nums);
	*/

	/*
	len = length(goal);
	printf("len: %d\n", len);
	*/

	return 0;
}

struct node *expand(struct node *selected)
{
	int i, j, k, cnt, succ_buf[BF][N+1][N];
	struct node *cp, *tp, *expanded;
	tp = selected;

	cnt = expand_a_node(tp->loc, succ_buf);


	return expanded;
}

int expand_a_node(int node[N+1][N], int succ_buf[BF][N+1][N])
{
	int i, j, cnt, found, g_val, h_val;
	
	//globals are *start and *goal
	//find the blank
	found = 0;
	for(i = 0; (i < N) && !found; i++){
		for(j = 0; (j < N) && !found; j++){
			if(node[i][j] == 0){
				found = 1;
			}
		}
	}
	//loop runs for extra iteration so values must be decremented
	i--;
	j--;
	//putchar('\n');
	//printf("i:%d j:%d\n", i, j);

	//intializing succ_buff with the board before moves
	int x,y,z;
	for(x = 0; x < BF; x++)
	{
		for(y = 0; y < N+1; y++)
		{
			for(z = 0; z < N; z++)
			{
				succ_buf[x][y][z] = node[y][z];
			}
		}	
	}	

	cnt = 0;
	//check if legal then perform down move
	if(i < (N - 1))
	{
		dn(i, j, 0, succ_buf);
		cnt++;
	}
	//check if legal then perform right move
	if(j < (N - 1))
	{
		rt(i, j, 1, succ_buf);
	}
	//check if legal then perform up move
	if(i > 0)
	{
		up(i, j, 2, succ_buf);
	}
	//check if legal then perform left move
	if(j > 0)
	{
		lt(i, j, 3, succ_buf);
	}

	return cnt;
}

void dn(int i, int j, int index, int succ_buf[BF][N+1][N])
{
	swap(i, j, i+1, j, index, succ_buf);
}

void rt(int i, int j, int index, int succ_buf[BF][N+1][N])
{
	swap(i, j, i, j+1, index, succ_buf);
}

void up(int i, int j, int index, int succ_buf[BF][N+1][N])
{
	swap(i, j, i-1, j, index, succ_buf);
}

void lt(int i, int j, int index, int succ_buf[BF][N+1][N])
{
	swap(i, j, i, j-1, index, succ_buf);
}

void swap(int i, int j, int k, int l, int index, int succ_buf[BF][N+1][N]){
	int temp = succ_buf[index][i][j];
	succ_buf[index][i][j] = succ_buf[index][k][l];
	succ_buf[index][k][l] = temp;
}

void init_2D(int a[N][N])
{
	int i, j, idx = 0;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			a[i][j] = idx; 
			idx++;
		}
	}
}

void print_array(char *msg, int a[N][N])
{
	int i, j;
	printf("%s:\n", msg);
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			printf("%2d ", a[i][j]);
		putchar('\n');
	}
	//putchar('\n');
}

void print_a_node(struct node *np) {
  int i,j, (*mp)[N];
  mp = np->loc;
  for (i=0;i<N;i++) {
    for (j=0;j<N;j++) printf("%2d ",np->loc[i][j]);
    printf("\n");
  }
  printf("\n");
}

struct node *init(int argc, char **argv){
	int i,j,k,idx;
	struct node *tp;

	tp=(struct node *) malloc(sizeof(struct node));
	idx = 1;
	for (j=0;j<N;j++)
	for (k=0;k<N;k++) tp->loc[j][k]=atoi(argv[idx++]);
	for (k=0;k<N;k++) tp->loc[N][k]=0;	/* set f,g,h of initial state to 0 */
	tp->next=NULL;
	start=tp;
	//printf("initial state\n"); print_a_node(start);

	tp=(struct node *) malloc(sizeof(struct node));
	idx = 1;
	for (j=0;j<N;j++)
	for (k=0;k<N;k++) tp->loc[j][k] = idx++;
	tp->loc[N-1][N-1] = 0;	      /* empty tile=0 */
	for (k=0;k<N;k++) tp->loc[N][k]=0;	/* set f,g,h of goal state to 0 */
	tp->next=NULL;
	goal=tp; 
	//printf("goal state\n"); print_a_node(goal);
	printf("intial and goal state generated....\n");

	strcpy(strategy,argv[idx]);
	if (strcmp(argv[idx],"dfs")) flag=DFS;
	else if (strcmp(argv[idx],"bfs")) flag = BFS;
	else flag=BEST;

	return start;
}

int length(struct node *hp)
{
	struct node *tp = malloc(sizeof(struct node));
	tp = hp;

	int cnt =0;
	while(tp)
	{
		cnt++;
		tp = tp->next;
	}
	return cnt;
}
