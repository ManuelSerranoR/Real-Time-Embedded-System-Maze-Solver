#include junk

/* 
* Must include header for for functions used below:
*       hit_brakes()
*       go_fwd()
*       left_turn()
*       right_turn()
*/


/* 
* We will be following the right hand approach
* the mouse will follow the maze touching the right side of the walls
*/
int main (void)
{
	/* Ft = ftront ultra sonic sensor, lt = left, rt = right */
	volatile const float ft_dst;
	volatile const float lt_dst;
	volatile const float rt_dst;

	const float max_dst = 2; // These should be set after tuning
	const float min_dst = .2; 
	float num_rt_turns = 0;
	const max_rt = 0; // maximum number of right turns allowed in a row
	int init_start = 1

	
	/*
	*  Basic structure: brake if you have finished the maze
	*  If started find a wall
	*  Then follow wall till right hand open or hit a wall
	*  Turn right if right hand side open
	*  Turn left if in a corner
	*  Make sure number of right turns is limited to avoid being stuck on an island
	*/
	while(1)
	{
		if (init_start)
		{
			while(ft_dst>min_dst)
			{
				go_fwd();  // This is for the initial drop into the maze
			}
		}
		while(((ft_dst >= max_dst) && (rt_dst >= max_dst)) && (lt_dst >= max_dst))
		{
			hit_brakes(); // This is for when we have left the maze
		}
		if((ft_dst <= min_dst) && (rt_dst > min_dst))
		{
			if (num_rt_turns >= max_rt)
			{
				right_turn(); // This is for when there is an opening on the right
				num_rt_turns++
			}
			else
			{
				left_trun(); // This is to get off of an island
				num_rt_turns = 0;
			}
		}
		if((ft_dst<=min_dst) && (rt_dst<=min_dst))
		{
			left_turn(); // This is for when stuck in a corner
		}
		while((ft_dst >= min_dst) && (rt_dst <= min_dst))
		{
			go_fwd(); // This is to follow the maze
		}
		if((ft_dst <= min_dst) && (rt_dst > min_dst))
		{
			if (num_rt_turns >= max_rt)
			{
				right_turn(); // This is for when there is an opening on the right
				num_rt_turns++
			}
			else
			{
				left_trun(); // This is to get off of an island
				num_rt_turns = 0;
			}
		}
		if((ft_dst<=min_dst) && (rt_dst<=min_dst))
		{
			left_turn(); // This is for when stuck in a corner
		}

	}
}
