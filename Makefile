CC=gcc
FLAGS=-std=c99 -W -Wall -pedantic
LIBS= -lm 	#utilisation de math.h

_OBJS=card.o\
    game.o\
		hands.o
OBJDIR=obj#le path vers les .o
SDIR=src#le path vers les .c
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS)) #remplacer src/ par obj/ dans les dépendances des .o

MAIN=$(patsubst %,$(OBJDIR)/%,poker_play.o)

_TESTS=main_test.o\
			 test_hands.o
TESTDIR=test
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))
TESTLIBS= -lcheck -lm -lpthread -lrt -lsubunit

all :: $(OBJS) $(MAIN)
	$(CC) $(OBJS) -o poker_play -g ${LIBS} -Ilibs

$(OBJDIR)/%.o: $(SDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

#TESTS
$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

test :: $(TESTS) $(OBJS)
	$(CC) $(TESTS) $(OBJS) -o tests -g ${LIBS} ${TESTLIBS}

clean :
	rm -fr *.o
	rm test/*.o
	touch a.out tests poker_play
	rm a.out tests poker_play
