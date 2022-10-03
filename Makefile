NAME = ircserv

CC = c++

CCFLAG = -std=c++98 -Wall -Wextra -Werror -g3 -fsanitize=address

SOURCES = 	srcs/main.cpp \
			srcs/Server.cpp \
			srcs/Client.cpp \
			srcs/Channel.cpp \
			srcs/Commands.cpp \
			srcs/CommandsRet.cpp \
			srcs/CommandsReply.cpp \
			srcs/ConnectionManager.cpp

OBJECTS	= $(SOURCES:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CCFLAG) -I includes $(OBJECTS) -o $(NAME)
	@echo "\033[0;92m* $(NAME) binary was created *\033[0m"

%.o: %.cpp
	$(CC) $(CCFLAG) -I includes -c $< -o $@

clean :
	rm -rf $(OBJECTS)
	@echo "\033[0;91m* $(NAME) object files were deleted *\033[0m"

fclean : clean
	rm -rf $(NAME)
	@echo "\033[0;91m* $(NAME) was deleted* \033[0m"

re : fclean all

run : all
	./$(NAME)

.PHONY : all clean fclean re
