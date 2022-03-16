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
template <typename T>
std::string	vektor_base_test(T *a)
{
	size_t size = 0;
	std::string	temp = "";

	size = (*a).size();
	temp += " size=" + std::to_string(size) + " capacity=" + std::to_string((*a).capacity()) + " elem=";
	for (size_t i = 0; i < size; i++)
		temp += std::to_string((*a)[i]);

	return (temp);
}


int	main ()
{
  

    std::string			temp_orig = "", temp_my = "";
	unsigned int		 rez = 0;
	std::vector<int>	orig_1(1);
	ft::vector<int>		my_1(1);
    std::vector<int>	orig_0(0);

    init_vector_all(&orig_1, &my_1);
	std::vector<int>	orig_2(SIZE_100K);
	ft::vector<int>		my_2(SIZE_100K);

	init_vector_all(&orig_2, &my_2);
	std::vector<int>	orig_3(SIZE_100K);
	ft::vector<int>		my_3(SIZE_100K);
	init_vector_all(&orig_3, &my_3);

	std::cout << "Test 6/12 (self size=100 insert(begin(), begin(), end()))" << std::endl;
	temp_orig = "", temp_my = "";

	//действия c оригиналом
	temp_orig += vektor_base_test(&orig_2);
	orig_2.insert(orig_2.begin(), orig_2.begin(), orig_2.end());
	temp_orig += vektor_base_test(&orig_2);

	
	
	
	//действия c собственной копией
	temp_my += vektor_base_test(&my_2);
	my_2.insert(my_2.begin(), my_2.begin(), my_2.end());
	temp_my += vektor_base_test(&my_2);
	//temp_my += " ";
	


	rez += print_status_comp(temp_orig, temp_my);
	
}