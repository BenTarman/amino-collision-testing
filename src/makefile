CC = gcc
OBJS = *.c
NAME = baxterIsAGreatGuy
COMMON_FLAGS = -pg -O2
LIB_FLAGS = -lamino -lamino-collision -lamino-planning -lamino-gl -lGL -lSDL2

BOOST_MATH_PROMOTE_DOUBLE_POLICY=false

CPP_FLAGS = $(COMMON_FLAGS) -I/home/ben/amino/include -I/usr/include/SDL2
LDFLAGS = -L/usr/local/lib $(LIB_FLAGS)

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(OBJS) -o $(NAME) $(CPP_FLAGS) $(LDFLAGS)

debug: $(OBJS) $(HEADERS)
	$(CC) $(OBJS) -o $(NAME) $(CPP_FLAGS) $(LDFLAGS) -g

run: $(NAME)
	./$(NAME)
drd: $(NAME)
	valgrind --tool=drd ./$(NAME)

helgrind: $(NAME)
	valgrind --tool=helgrind ./$(NAME)
clean:
	rm -rf $(NAME)*
