NAME		:= libcapt.a
C			:= gcc
CFLAGS		:= -Wall -Werror -Wextra -MMD -MP
SRCDIR		:= .
OBJDIR		:= ./obj
INCLUDE		:= ./
SRCS		:= $(shell find $(SRCDIR) -type f -name "*.c" | xargs basename -a)
# SRCS		:= capt_stdout.c get_string_from_fd.c
OBJS		:= $(SRCS:%.c=$(OBJDIR)/%.o)
DEPENDS		:= $(OBJS:.o=.d)
SHELL		:= /bin/bash
PURPLE		:= \033[1;35m
GREEN		:= \033[1;32m
RESET		:= \033[0;39m

FTPF		:= 
FTPFINC		:= 

all		: $(NAME)

-include $(DEPENDS)

test	:
	gcc $(FTPFINC) main.c libcapt.a -lpthared  $(FTPF) -lftprintf
	./a.out

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)/$(*D)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo -e "	""$(GREEN)$@$(RESET)"

t:
	echo $(SRCS)
$(NAME)	: $(OBJS)
	@$(AR) -src $(NAME) $(OBJS)
	@echo -e "\n$(PURPLE) build	$(GREEN)$@$(RESET)"

clean	: rm_reloc

fclean	: clean rm_exec

b_clean	: rm_reloc

b_fclean: rm_exec

rm_reloc:
	$(RM) -r $(OBJDIR)

rm_exec	:
	$(RM) $(NAME)

re		: fclean all

debug	: CFLAGS += -g -fsanitize=address
debug	: re

.PHONY	: all clean fclean re bonus add norm rm_exec rm_reloc b_clean b_fclean head test