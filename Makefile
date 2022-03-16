NAME			= ft_containers
SRCS			= main.cpp
OBJS			= $(patsubst %.cpp, %.o, $(SRCS))
HEADERS			= vector.hpp
CC				= clang++
RM				= rm -f
FLAGS			= -Wall -Wextra -Werror -std=c++11

%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(HEADERS) $(OBJS)
				$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re