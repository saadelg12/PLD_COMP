# Détection de l'OS
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
ARCH := $(shell uname -m 2>/dev/null || echo unknown)

# Choix du fichier de configuration selon l'OS
ifeq ($(UNAME_S),Darwin)
    include config-IF501.mk
else
    include config.mk
endif

# Choix du compilateur
ifeq ($(UNAME_S),Darwin)
  ifeq ($(ARCH),arm64)
    CC = arch -x86_64 g++
  else
    CC = g++
  endif
else
  CC = g++
endif

# Options de compilation
CCFLAGS = -g -c -std=c++17 -I$(ANTLRINC) -Wno-attributes
LDFLAGS = -g

default: all
all: ifcc

##########################################
# Liste des objets à compiler
OBJECTS=build/ifccBaseVisitor.o \
	build/ifccLexer.o \
	build/ifccVisitor.o \
	build/ifccParser.o \
	build/main.o \
	build/CodeGenVisitor.o \
	build/SymbolTableVisitor.o

##########################################
# Link final
ifcc: $(OBJECTS)
	@mkdir -p build
	$(CC) $(LDFLAGS) build/*.o $(ANTLRLIB) -o ifcc

##########################################
# Compilation des fichiers à la main
build/%.o: %.cpp generated/ifccParser.cpp
	@mkdir -p build
	$(CC) $(CCFLAGS) -MMD -o $@ $<

##########################################
# Compilation des fichiers générés par ANTLR
build/%.o: generated/%.cpp
	@mkdir -p build
	$(CC) $(CCFLAGS) -MMD -o $@ $<

# Inclusion automatique des fichiers .d générés
-include build/*.d
build/%.d:

##########################################
# Génération des fichiers ANTLR
generated/ifccLexer.cpp: generated/ifccParser.cpp
generated/ifccVisitor.cpp: generated/ifccParser.cpp
generated/ifccBaseVisitor.cpp: generated/ifccParser.cpp
generated/ifccParser.cpp: ifcc.g4
	@mkdir -p generated
	java -jar $(ANTLRJAR) -visitor -no-listener -Dlanguage=Cpp -o generated ifcc.g4

# Ne pas supprimer les fichiers générés
.PRECIOUS: generated/ifcc%.cpp

##########################################
# Affichage de l'arbre syntaxique
FILE ?= ../tests/testfiles/1_return42.c

gui:
	@mkdir -p generated build
	java -jar $(ANTLRJAR) -Dlanguage=Java -o generated ifcc.g4
	javac -cp $(ANTLRJAR) -d build generated/*.java
	java -cp $(ANTLRJAR):build org.antlr.v4.gui.TestRig ifcc axiom -gui $(FILE)

##########################################
# Nettoyage complet
clean:
	rm -rf build generated
	rm -f ifcc
