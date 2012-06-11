##
## Sample for Memory Manager Module
##

NAME		= memory_manager_sample

SRC_MODULE_DIR  = ../src
INC_MODULE_DIR  = ../inc

SRC		= main.cpp				\
		  $(SRC_MODULE_DIR)/memory_manager.cpp	\

OBJ		= $(SRC:.cpp=.o) $(OPT:.cpp=.o)

CXX		= g++

INCLUDES	= -I../../inc -I$(INC_MODULE_DIR)

CPPDEF		= -DDEBUG

CXXFLAGS	= $(INCLUDES)				\
		  $(CPPDEF)				\
		  -Wall -Wextra				\
		  -O3					\

.cpp.o:
		@$(CXX) $(CXXFLAGS) -c $< -o $@
		@echo [CXX] $<

$(NAME):	$(OBJ)
		@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)
		@echo [CXX] $(NAME)
		@chmod 755 $(NAME)
		@echo [CHMOD] $(NAME)

clean:
		@rm -f *~ *.o *.a *.so *#* *core *.log
		@echo [RM] *~ *.o *.a *.so *#* *core *.log

fclean:		clean
		@rm -f $(NAME)
		@echo [RM] $(NAME)

re:		fclean all

all:		$(NAME)

install:	all
