NAME = ircserv

CC = c++

CCFLAG = -std=c++98 -Wall -Wextra -Werror

SOURCES = 	srcs/main.cpp \
			srcs/Server.cpp \
			srcs/Client.cpp \
			srcs/Channel.cpp \
			srcs/Commands.cpp \
			srcs/CommandsRet.cpp

HEADERS = 	includes/Server.hpp \
			includes/Client.hpp \
			includes/Channel.hpp \
			includes/Commands.hpp

OBJECTS	= $(SOURCES:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJECTS) $(HEADERS)
	$(CC) $(CCFLAG) -I includes $(OBJECTS) -o $(NAME)
	@echo "\033[0;92m* $(NAME) binary was created *\033[0m"

%.o: %.cpp $(HEADERS)
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
