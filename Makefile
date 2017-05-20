SHELL = /bin/sh

PROJECT  := AlghHuff

# ------------------
# External programs
# ------------------
CC  := gcc
RM  := rm -rf
DG  := doxygen

# --------------------
# Directories & Files
# --------------------
D_SRC    := ./src
<<<<<<< HEAD
D_TESTS  := $(D_SRC)/test
D_UNITY  := 

ENTRY_POINT := $(D_SRC)/main.c

FILES_PROGR_C :=  $(filter-out $(ENTRY_POINT), $(wildcard $(D_SRC)/*.c))
FILES_TESTS_C :=  $(wildcard $(D_TESTS)/*.c) $(D_UNITY)/src/unity.c $(D_UNITY)/extras/fixture/src/unity_fixture.c

PROJECT_WITHOUT_TESTS := $(FILES_PROGR_C) $(ENTRY_POINT)
PROJECT_WITH_TESTS := $(FILES_TESTS_C) $(FILES_PROGR_C)

PROJECT_WITHOUT_TESTS_O  := $(PROJECT_WITHOUT_TESTS:.c=.o)
PROJECT_WITH_TESTS_O  := $(PROJECT_WITH_TESTS:.c=.o)
=======
D_DOC    := ./doc
FILES_C  := $(wildcard $(D_SRC)/*.c)
FILES_O  := $(FILES_C:.c=.o)
>>>>>>> 2809a59791b7bd92d302249aa8195a5ca4944331

# ------------
# Flags
# ------------
CFLAGS  := -Wall
CFLAGS  += -std=c99
LFLAGS  :=

INCS := -I $(D_UNITY)/src -I $(D_UNITY)/extras/fixture/src 
# ------------
# Targets
# ------------
default: $(PROJECT)

tests: test-$(PROJECT)

check: test-$(PROJECT)
	./test-$(PROJECT)

%.o: %.c
	$(CC) -c -I $(D_SRC) $(CFLAGS) $(INCS) $< -o $@ -lm 

$(PROJECT): $(PROJECT_WITHOUT_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITHOUT_TESTS_O) -o  $@ 

test-$(PROJECT): $(PROJECT_WITH_TESTS_O)
	$(CC) -I $(D_SRC) $(LFLAGS) $(PROJECT_WITH_TESTS_O) -o $@ $(INCS) 

.phony: doxygen
doxygen:
	$(DG) $(D_DOC)/doxygen.config

.phony: html
html: doxygen

.phony: pdf
pdf: doxygen
	make -C $(D_DOC)/output/latex

.phony:	clean
clean:
<<<<<<< HEAD
	-$(RM) $(PROJECT_WITH_TESTS_O) $(D_SRC)/main.o $(PROJECT) test-$(PROJECT)

=======
	-$(RM) $(FILES_O) $(PROJECT) $(D_DOC)/output
>>>>>>> 2809a59791b7bd92d302249aa8195a5ca4944331
