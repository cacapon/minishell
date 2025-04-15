# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 11:48:18 by ttsubo            #+#    #+#              #
#    Updated: 2025/04/15 16:08:39 by ttsubo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# usage
# make -f test.mk
# make -f test.mk clean

I_FLG = -Iinc -Ilib/libft
L_FLG = -Llib/libft -lft -lreadline

# testを追加する場合はSRCにファイル名を追加してください。
SRC = cd.c exit.c env.c \
	  tokenizer.c
OUT = $(addprefix test_, $(SRC:.c=.out))

all: $(OUT)

test_%.out: tests/builtin/test_%.c src/builtin/%.c
	cc $^ $(L_FLG) $(I_FLG) -o $@

test_%.out: tests/tokenizer/test_%.c
	cc $^ src/tokenizer/*.c $(L_FLG) $(I_FLG) -o $@

clean:
	rm -f test_*.out
