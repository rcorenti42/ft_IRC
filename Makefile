NAME = ircserv

CC = c++

CCFLAG = -Wall -Wextra -Werror -g3 -std=c++98 #-fsanitize=address

SOURCES = 	srcs/main.cpp \
			srcs/Server.cpp \
			srcs/Client.cpp \
			srcs/Channel.cpp \
			srcs/Commands.cpp \
			srcs/ConnectionManager.cpp \
			srcs/CommandManager.cpp

OBJECTS	= $(SOURCES:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CCFLAG) -I includes $(OBJECTS) -o $(NAME)
	@echo "\033[0;92m* $(NAME) binary was created *\033[0m"

%.o: %.cpp
	$(CC) $(CCFLAG) -I includes -c $< -o $@

clean : all
	rm -f $(OBJECTS)
	@echo "\033[0;91m* $(NAME) object files were deleted *\033[0m"

fclean : clean
	rm -f $(NAME)
	@echo "\033[0;91m* $(NAME) was deleted* \033[0m"

re : fclean all

run : all
	./$(NAME)

.PHONY : all clean fclean re
