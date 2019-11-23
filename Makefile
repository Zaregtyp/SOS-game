#As minhas sources...
SRC=main.c myf.c

#O binário executável (nome do programa)
PROG=myf

################################
CC=gcc
CFLAGS=-Wall

OBJ=$(SRC:.c=.o)  #macro automática para gerar os OBJ a partir das SRC

INCLUDE=                #para as header files (cabeçalhos)
LIB= -lm      -lncurses      #bibliotecas específicas a usar

DOXYFILE= Doxyfile


AULA = 3 #numero da aula corrente

############################################
# Regras
############################################

###########################################
# Regras relativas à compilação e linkagem

$(PROG): prototypes.h $(OBJ)
	$(CC)	$(OBJ)	-o	$(PROG)	$(LIB)

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

proto prototypes.h: $(SRC)   #decidir se esta dependência deve ou não existir!
		@echo "Rebuild prototypes.h"
		@echo '/*File generated automatically. Do not edit*/' > prototypes.h                   #crea prototype
		@echo '/*Generated on' `hostname` ',' `date` '*/' >> prototypes.h
		@cproto -q -O /dev/null $(SRC) >> prototypes.h #va percorrer 


#......................................................................
#......................................................................

############################################
# Regras relativas à geração de documentação

#depende da $(DOXYFILE) e do ficheiro index.html
doc: $(DOXYFILE) html/index.html

#A $(DOXYFILE) só depende de si própria.
#Se não existir é criada e alguns defaults são ajustados:
$(DOXYFILE):
		doxygen -g $(DOXYFILE) ; \
		sed -i 's/^PROJECT_NAME.*$$/PROJECT_NAME          = "My project $(PROG)"/' $(DOXYFILE) ;\
		sed -i 's/^GENERATE_LATEX.*$$/GENERATE_LATEX      = NO/'                   $(DOXYFILE) ;\
		sed -i 's/^HAVE_DOT.*$$/HAVE_DOT                  = YES/'                  $(DOXYFILE) ;\
		sed -i 's/^SOURCE_BROWSER.*$$/SOURCE_BROWSER      = YES/'                  $(DOXYFILE) ;\
		sed -i 's/^GENERATE_TREEVIEW.*$$/GENERATE_TREEVIEW= YES/'                  $(DOXYFILE) ;\
		sed -i 's/^PROJECT_LOGO.*$$/PROJECT_LOGO          = PARIlogo.png/'         $(DOXYFILE) ;

#O ficheiro index.html depende obviamente da Doxyfile e das SRC, mas
#pode ter outras dependências adicionais...

html/index.html: $(DOXYFILE) $(SRC) mainpage.dox PARIlogo.png
	doxygen

#Forçar a geração de documentação mesmo que ela já exista (não depende de index.html)
#forcedoc: $(DOXYFILE)
#		doxygen


#Gera ficheiro de logotipo automaticamente
logo PARIlogo.png:
		convert pattern:circles \( +clone \) +append \( +clone \) -append \
				-fill grey -opaque black  -blur 0x0.5 -shade 120x45 \
				-gravity center -crop 50%  +repage    miff:- |\
				 convert  -size 80x80 tile:- -fill blue \
				-draw "scale 2.5,3 text 2,12 PARI" \
				-draw "scale 2,2 text 2,32 'Aula $(AULA)'" PARIlogo.png


#########################################
# Regras relativas à gestão e organização

view: doc
	firefox html/index.html

clean:
	rm -rf $(PROG) $(OBJ)

allclean: clean
	rm -rf html latex


forcedoc: Doxyfile              #Forçar a geração de documentação mesmo que ela já exista (não depende de index.html)
	doxygen

###########################################
# targets que não são ficheiros e evita
# eventuais conflitos se porventura existirem
# ficheiros ou diretorios com estes nomes.
#
.PHONY: doc clean allclean forcedoc
