CC=gcc
FLAGS=-std=c99 -W -Wall -pedantic -g
LIBS= -lm 	#utilisation de math.h

_OBJS=card.o\
    game.o\
		hands.o\
		best.o
OBJDIR=obj#le path vers les .o
SDIR=src#le path vers les .c
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS)) #remplacer src/ par obj/ dans les dépendances des .o
MAIN=$(patsubst %,$(OBJDIR)/%,poker_play.o)

_TESTS=main_test.o\
			 test_hands.o\
			 test_better.o\
			 test_utils.o

TESTDIR=test
TESTS = $(patsubst %,$(TESTDIR)/%,$(_TESTS))
TESTLIBS= -lcheck -lm -lpthread -lrt -lsubunit


all :: poker_play test

poker_play : $(OBJS) $(MAIN)
	$(CC) $^ -o poker_play ${LIBS} -Ilibs

$(OBJDIR)/%.o: $(SDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

#TESTS
$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

test :: $(TESTS) $(OBJS)
	$(CC) $(TESTS) $(OBJS) -o tests ${LIBS} ${TESTLIBS}

clean :
	rm -fr *.o
	rm test/*.o
	touch a.out tests poker_play
	rm a.out tests poker_play
