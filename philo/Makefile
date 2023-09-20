
NAME		:=	philo

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -MMD -MP
THREAD_FLAG :=	-pthread

UNAME 		:= $(shell uname)
ifeq ($(UNAME), Linux)
	CFLAGS	+=	-pedantic
endif

ifdef SANI
	CFLAGS += -g -fsanitize=thread 
endif


SRCS_DIR	:=	srcs
UTILS_DIR	:=	utils
SRCS		:=	$(UTILS_DIR)/ft_atoi.c \
				$(UTILS_DIR)/ft_isdigit.c
SRCS		+=	args.c \
				main.c

OBJS_DIR	:=	objs
OBJS		:=	$(SRCS:%.c=$(OBJS_DIR)/%.o)

INCLUDES_DIR	:=	includes
INCLUDES		:=	-I./$(INCLUDES_DIR)/

DEPS		:=	$(OBJS:.o=.d)
MKDIR		:=	mkdir -p

#--------------------------------------------
.PHONY	: all
all		: $(NAME)

# todo
# bonus	:

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(THREAD_FLAG)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(THREAD_FLAG)

.PHONY	: clean
clean	:
	$(RM) -r $(OBJS_DIR)

.PHONY	: fclean
fclean	: clean
	$(RM) $(NAME)

.PHONY	: re
re		: fclean all

#--------------------------------------------
.PHONY	: run
run		: re
	./$(NAME) 1 10 2 3

.PHONY	: sani
sani	:
	make re SANI=1

.PHONY	: norm
norm	:
	python3 ../test/norm.py

#--------------------------------------------

-include $(DEPS)
