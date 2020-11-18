CC=gcc
FLAGS=-std=c99 -W -Wall -pedantic
LIBS= -lm 	#utilisation de math.h

_OBJS=card.o\
    game.o\
		poker_play.o
OBJDIR=obj#le path vers les .o
SDIR=src#le path vers les .c
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS)) #remplacer src/ par obj/ dans les dépendances des .o

_TESTS=check_hands.o
TESTDIR=test
TESTS = $(patsubst %,$(TESTSDIR)/%,$(_TESTS))
TESTLIBS= -lcheck -lm -lpthread -lrt -lsubunit

all :: $(OBJS)
	$(CC) $(OBJS) -o poker_play -g ${LIBS} -Ilibs

$(OBJDIR)/%.o: $(SDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

#TESTS
$(TESTDIR)/%.o: $(TESTDIR)/%.c $(OBJ)
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

test :
	$(CC) $(TESTS) $(OBJS) -o tests -g ${LIBS} ${TESTLIBS} -Ilibs

clean :
	rm -fr *.o
