OBJECTS = *.o
BINAIRE = wolf3d
SRC = libft/*.c\
		src/main.c\
		src/draw.c\
		src/map.c\
		src/player.c\
		src/raycasting.c\
		src/keys.c

FLAGS = -Wall -Wextra -Werror 
NAME = wolf3d.a

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRC) -I header/wolf3d.h
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)
	make -C mlx/
	gcc $(FLAGS) src/main.c -o $(BINAIRE) $(NAME) -I mlx mlx/libmlx.a -framework OpenGL -framework AppKit

sanitize:
	gcc $(FLAGS) src/main.c -o $(BINAIRE) $(NAME) -I mlx mlx/libmlx.a -framework OpenGL -framework AppKit -g

lldb:
	gcc -g $(SRC) $(NAME) -I mlx mlx/libmlx.a -framework OpenGL -framework AppKit

cleanlldb:
	rm a.out
	rm -r a.out.dSYM

runlldb:
	lldb ./a.out

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(BINAIRE)
	rm -f $(NAME)

re: fclean all
