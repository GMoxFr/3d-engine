##################################################################################################################
##  PROJECT																									 	##
##################################################################################################################

NAME		=	`pwd | rev | cut -d "/" -f1 | rev | tr [:upper:] [:lower:]`

##################################################################################################################
##  BUILDING / COMMANDS																						 	##
##################################################################################################################

COMPILER	=	g++
RM			=	rm -f

UNAME_S 	:= $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
  ECHO		= echo
else
  ECHO		= /bin/echo -e
endif

LOGDIR		=	errors/
INCLUDES	=	-I./include/ -I./include/shapes -I./include/lights -I./ $(shell pkg-config --cflags sfml-all)
FLAGS		=	-std=c++17 -MMD -MP
LIBRARIES	=	$(shell pkg-config --libs sfml-all) -lstdc++ -lm -lpthread -ldl

OBJDIR		=	obj/

ifeq ($(UNAME_S),Darwin)
  INCLUDES	+=	-I/opt/homebrew/include/
endif

##################################################################################################################
##  SOURCES																									 	##
##################################################################################################################

SRC			=	$(shell find src/ -name "*.cpp")
OBJ			=	$(addprefix $(OBJDIR), $(SRC:.cpp=.o))
DEP			=	$(addprefix $(OBJDIR), $(SRC:.cpp=.d))

MAIN		=	$(wildcard main/*.cpp)
MOBJ 		=	$(addprefix $(OBJDIR), $(MAIN:.cpp=.o))

##################################################################################################################
##  COLORS																									 	##
##################################################################################################################

DEFAULT	  	=	"\033[00m"
RED 		=	"\033[0;31m"
GREEN		=	"\033[0;32m"
ORANGE 	  	=	"\033[0;33m"
BLUE		=	"\033[0;34m"
PURPLE	  	=	"\033[0;35m"
CYAN		=	"\033[0;36m"
LGRAY 	  	=	"\033[0;37m"
DGRAY 	  	=	"\033[1;30m"
LRED 		=	"\033[1;31m"
LGREEN	  	=	"\033[1;32m"
YELLOW 	  	=	"\033[1;33m"
LBLUE 	  	=	"\033[1;34m"
LPURPLE 	=	"\033[1;35m"
LCYAN 	  	=	"\033[1;36m"
WHITE 	  	=	"\033[1;37m"

##################################################################################################################
##  COMPILING RULES																								##
##################################################################################################################

all:			FLAGS += -W -Wall -Wextra -Werror -g -ggdb -g3
all:			erase full

fast:			FLAGS += -O2 -march=native
fast:			erase full

full:			init $(MOBJ) $(OBJ)
			@$(COMPILER) $(MOBJ) $(OBJ) -o $(NAME) $(LIBSPATH) $(LIBRARIES)	\
			 2>> $(LOGDIR)/$(NAME) &&							\
			 $(ECHO) $(LCYAN) "[OK]" $(CYAN) $(NAME) $(DEFAULT) ||				\
			 $(ECHO) $(LPURPLE)  "[KO]" $(PURPLE) $(NAME) $(DEFAULT)

obj/%.o:		%.cpp
			@$(eval TRACE="$(addprefix $(LOGDIR), $(subst /,-, $<))")
			@mkdir -p $(dir $@)
			@$(COMPILER) $(DEBUGS) $(FLAGS) $(INCLUDES) -c $< -o $@ 2>> $(TRACE) && \
			 $(ECHO) $(LGREEN) "[OK]" $(GREEN) $< $(DEFAULT) || \
			 $(ECHO) $(LRED)  "[KO]" $(RED) $< $(DEFAULT)
			@find $(TRACE) -size 0 -delete || true


##################################################################################################################
##  MISCELLANOUS RULES																						  	##
##################################################################################################################

init:
			@$(ECHO) $(LBLUE) "Compiling project" $(DEFAULT)
			@mkdir -p $(LOGDIR)

clean:
			@$(RM) -r $(OBJDIR) && \
			 $(ECHO) $(LGREEN) "[OK]" $(GREEN) "Object files and dependencies deleted" $(DEFAULT) ||\
			 $(ECHO) $(LRED) "[KO]" $(RED) "Error while deleting object files and dependencies" $(DEFAULT)


fclean:		clean erase
			@$(RM) $(NAME) &&								\
			 $(ECHO) $(LGREEN) "[OK]" $(GREEN) "Program deleted" $(DEFAULT) ||		\
			 $(ECHO) $(LRED) "[KO]" $(RED) "Error while deleting program" $(DEFAULT)

re:	   fclean
			@$(MAKE) -s all

erase:
			@$(RM) -r $(LOGDIR)

debug:
			@echo "SRC: $(SRC)"
			@echo "OBJ: $(OBJ)"
			@echo "MAIN: $(MAIN)"
			@echo "MOBJ: $(MOBJ)"

-include $(DEP)
