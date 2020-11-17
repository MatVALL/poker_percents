#utilisation du tutoriel http://perso.univ-lyon1.fr/jean-claude.iehl/Public/educ/Makefile.html
CC=gcc
FLAGS=-std=c99 -W -Wall -pedantic
LIBS= -lm 	#utilisation de math.h

_OBJS=card.o\
    game.o\
		poker_play.o
OBJDIR=obj#le path vers les .o
SDIR=src#le path vers les .c
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS)) #remplacer src/ par obj/ dans les dépendances des .o

$(info ${OBJS})#afficher les .o créés
all :: $(OBJS)
	$(CC) $(OBJS) -o poker_play -g ${LIBS} -Ilibs

$(OBJDIR)/%.o: $(SDIR)/%.c
	$(CC) -c ${FLAGS} $^ -Ilibs -o $@

clean :
	rm -fr *.o
