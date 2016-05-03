#pragma once
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <vector>


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
		int random_integer = rand() % (max + (1) - min);
		random_integer += min;

		return random_integer;
	};

	inline float range(float min, float max)
	{
		assert(max> min);
		/*for (int i = 0; i < 10; i++)
		{
		printf("%f\n", ((float)rand() / RAND_MAX) *(max - min) + min);
		}*/
		float random_float = ((float)rand() / RAND_MAX) *(max - min) + min;
		return random_float;
	};


	inline unsigned int Pick(unsigned int minIndex, unsigned int maxIndex,std::vector<unsigned int> NumbersToIgnore)
	{
		assert(minIndex >= 0);
		assert(maxIndex >= minIndex);
		
		std::vector<unsigned int> temp;
		bool add;

	
		printf("Number of ignores = %d \n\n",NumbersToIgnore.size());
		
		for (unsigned int i = minIndex; i < maxIndex; i++)
		{
			add=true;

			for (unsigned int j = 0; j < NumbersToIgnore.size(); j++)
			{
				if (i == NumbersToIgnore.at(j))
					add = false;
			}
			
			if (add)
			{
				temp.push_back(i);
			}
				
		}
		printf("tempList\n");
		for (size_t i = 0; i < temp.size(); i++)
		{
			printf("%d\n", temp.at(i));
		}
		
		unsigned int result = rand() % temp.size();
		result= temp.at(result);
		printf("\n\nResult= %d\n\n", result);

		return result;
		

	}


	inline unsigned int PickIndexVector(std::vector<unsigned int>* vector)
	{
		
		unsigned int result = rand() % vector->size();

		return result;


	}
#pragma endregion	

}

