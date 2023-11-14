
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

#--------------------------------------------
# srcs
#--------------------------------------------
SRCS_DIR	:=	srcs
SRCS		:=	args.c \
				destroy.c \
				main.c \
				monitor_cycle.c \
				monitor_death.c \
				mutex.c \
				philo_action.c \
				philo_cycle.c \
				philo_eat.c \
				philo_forks.c \
				philo_simulate.c \
				philo_sleep_think.c \
				put.c \
				usleep_gradual.c

#--------------------------------------------
# utils
#--------------------------------------------
UTILS_DIR	:=	utils
SRCS		+=	$(UTILS_DIR)/call_atomic.c \
				$(UTILS_DIR)/debug.c \
				$(UTILS_DIR)/ft_atoi.c \
				$(UTILS_DIR)/ft_free.c \
				$(UTILS_DIR)/ft_isdigit.c \
				$(UTILS_DIR)/get_current_time.c

#--------------------------------------------
# ft_deque
#--------------------------------------------
DEQUE_DIR	:=	ft_deque
SRCS		+=	$(UTILS_DIR)/$(DEQUE_DIR)/dq_add_back.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_add_front.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_clear_all.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_clear_node.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_is_empty.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_new.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_node_new.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_pop_back.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_pop_front.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_pop_selected_node.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_print.c \
				$(UTILS_DIR)/$(DEQUE_DIR)/dq_set_node.c

#--------------------------------------------
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
