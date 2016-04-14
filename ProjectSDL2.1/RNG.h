#pragma once
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


namespace RNG {
#pragma region 

		inline int range(int min, int max)
		{
			assert(max > min);
			/*for (int i = 0; i < 10; i++)
			{
				int random_integer = rand() % (max + (1) - min);
				random_integer += min;
				printf("%d\n", random_integer);
			}*/
			int random_integer = rand() % (max+(1) - min);
			random_integer += min;

			return random_integer;
		};

		inline float range(float min, float max) 
		{
			assert (max> min);
			/*for (int i = 0; i < 10; i++)
			{
			printf("%f\n", ((float)rand() / RAND_MAX) *(max - min) + min);
			}*/
			float random_float = ((float)rand() / RAND_MAX) *(max - min) + min;
			return random_float;
		};
	
#pragma endregion	

}

