NAME = ircserv

CC = c++

CCFLAG = -std=c++98 -Wall -Wextra -Werror

SOURCES = 	main.cpp \
			CommandsRet.cpp

HEADERS = 	Server.hpp \
			Client.hpp \
			Channel.hpp \
			Commands.hpp

OBJECTS	= $(SOURCES:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(CC) $(CCFLAG) $(OBJECTS) -o $(NAME)
	@echo "\033[0;92m* $(NAME) binary was created *\033[0m"

$(OBJECTS) : $(SOURCES) $(HEADERS)
	$(CC) $(CCFLAG) -c $(SOURCES)

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
