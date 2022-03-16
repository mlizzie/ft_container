#include "vector.hpp"
#include <vector>
#define SIZE_100 100


# define DEFAULT	"\033[0m"
# define BOLD		"\033[1m"
# define UNDERLINE	"\033[4m"
# define REVERS		"\033[7m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define AQUA		"\033[36m"

# define RANDOM		10
# define STR_PART	100
# define STR_MAX	1000

# define SIZE_0		0
# define SIZE_1		1
# define SIZE_10	10
# define SIZE_100	100
# define SIZE_1K	1000
# define SIZE_10K	10000
# define SIZE_50K	50000
# define SIZE_100K	100000
# define SIZE_1M	1000000
# define SIZE_10M	10000000
# define SIZE_100M	100000000

// Иницилихация вектора std, ft одними параметрами
template <typename T>
void	init_vector_all(std::vector<T>* a_orig, ft::vector<T>* a_my)
{
	std::srand(time(NULL));
	int	size_orig = (*a_orig).size();
	int	size_my = (*a_my).size();
	if (size_orig != size_my)
	{
		std::cout << "Error size" << std::endl;
		return ;
	}
	for (int i = 0; i < size_orig; i++)
		(*a_orig)[i] = (*a_my)[i] = (rand() % RANDOM) + 0.5;
}


void	print_status_comp_str(std::string name, std::string str)
{
	size_t	len = str.length();
	bool	flag = false;

	std::cout << name << std::endl;;

	if (len < STR_MAX)
		std::cout << str << "\n";
	else
	{
		size_t i = 0;

		for (; i < len && i < STR_PART; i++)
			std::cout << str[i];
		std::cout << "... ";
		for (; i < len; i++)
		{
			if (str[i] == 's')
				break ;
		}
		for (size_t j = i; j < len && j < i + STR_PART; j++)
		{
			std::cout << str[j];
			flag = true;
		}
		if (flag == true)
			std::cout << "... ";
	}
	std::cout << std::endl;
}

bool	print_status_comp(std::string orig, std::string my)
{
	std::string ret;

	std::cout << "Comp: ";
	if (orig == my)
	{
		std::cout << "" GREEN " OK \n" DEFAULT;
		return (0);
	}
	else
	{
		std::cout << RED " KO \n" DEFAULT;
		print_status_comp_str("orig", orig);
		print_status_comp_str("my", my);
		return (1);
	}
}

int	main ()
{
	std::cout << "Test 2/6 (size = 0 resize(1000))\n";
    std::string			temp_orig = "", temp_my = "";
    unsigned int		 rez = 0;
    std::vector<int>	orig_1;
	ft::vector<int>		my_1;

	orig_1.resize(SIZE_1K);
	temp_orig = "size=" + std::to_string(orig_1.size()) + "capacity=" + std::to_string(orig_1.capacity()) + "elem=";
	for (size_t i = 0; i < SIZE_1K; i++)
		temp_orig += std::to_string(orig_1[i]) + " ";

	my_1.resize(SIZE_1K);
	temp_my = "size=" + std::to_string(my_1.size()) + "capacity=" + std::to_string(my_1.capacity()) + "elem=";
	for (size_t i = 0; i < SIZE_1K; i++)
		temp_my += std::to_string(my_1[i]) + " ";

	rez += print_status_comp(temp_orig, temp_my);
	//rez += print_status_time(time_orig, time_my);
}