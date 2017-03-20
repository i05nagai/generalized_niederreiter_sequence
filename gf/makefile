.SUFFIXES:
.SUFFIXES: .o .c

CC = gcc
#DEBUG = -g -Wall #-O0
HEADER = -I/usr/local/include
.c.o : 
	$(CC) $(DEBUG) $(HEADER) -c $<

### SOURCES ###
EXAMPLE_SOURCES = example.c

GF_SOURCES = GF.c
GF_SOURCES += GFX.c

N_LDS_GF_SOURCES = LDS_GF.c
N_LDS_GF_SOURCES += GF_niederriter.c
N_LDS_GF_SOURCES += GF_gc_niederriter.c
N_LDS_GF_SOURCES += GF_gc2_niederriter.c
N_LDS_GF_SOURCES += LDS_Gauss_GF.c
N_LDS_GF_SOURCES += GF_matrix_gen.c
N_LDS_GF_SOURCES += GaussDevBM.c

GF_TABLE_GENERATOR_SOURCES = GF_table_generator.c
GF_GEN_IRRED_POLY_SOURCES = GF_gen_irred_poly.c

### OBJCTS ###
EXAMPLE_OBJS = ${EXAMPLE_SOURCES:.c=.o}
GF_OBJS = ${GF_SOURCES:.c=.o}
N_LDS_GF_OBJS = ${N_LDS_GF_SOURCES:.c=.o}
GF_TABLE_GENERATOR_OBJS = ${GF_TABLE_GENERATOR_SOURCES:.c=.o}
GF_GEN_IRRED_POLY_OBJS = ${GF_GEN_IRRED_POLY_SOURCES:.c=.o}

### LIST ###
EXAMPLE_LIST = ${EXAMPLE_SOURCES:.c=.u}
GF_LIST = ${GF_SOURCES:.c=.u}
N_LDS_GF_LIST = ${N_LDS_GF_SOURCES:.c=.u}
GF_TABLE_GENERATOR_LIST = ${GF_TABLE_GENERATOR_SOURCES:.c=.u}
GF_GEN_IRRED_POLY_LIST = ${GF_GEN_IRRED_POLY_SOURCES:.c=.u}

### STRINGS ###
GF = GF
N_LDS_GF = n_lds_GF

### DIRECTORYS ###
LIBDIR = -I/usr/local/include
LIBDIR += -I/usr/include
LIBDIR += -I./
LIBDIR += -L/usr/local/lib
LIBDIR += -L/usr/lib
LIBDIR += -L./

### LIBRARYS ###
LIBFLAGS = $(LIBDIR)
LIBFLAGS += -l$(N_LDS_GF) -l$(GF)
LIBFLAGS += -lgsl -lgslcblas -lm

### EXECUTABLE FILE NAMES ###
EXAMPLE = example
GF_TABLE_GENERATOR = GF_table_generator
GF_GEN_IRRED_POLY = GF_gen_irred_poly

### TARGET LIBRARYS ###
TARGET_GF = lib$(GF).a
TARGET_N_LDS_GF = lib$(N_LDS_GF).a

TARGETS = $(TARGET_GF)
TARGETS += $(TARGET_N_LDS_GF)

### MAKE ###
all : clean $(EXAMPLE) $(TARGETS) $(GF_TABLE_GENERATOR) $(GF_GEN_IRRED_POLY)

$(EXAMPLE) : $(EXAMPLE_OBJS) $(TARGET_N_LDS_GF) $(TARGET_GF)
	$(CC) -o $@ $^ $(LIBFLAGS)

$(TARGET_GF) : $(GF_OBJS)
	rm -f $(TARGET_GF)
	ar cvr $(TARGET_GF) $(GF_OBJS)

$(TARGET_N_LDS_GF) : $(N_LDS_GF_OBJS)
	rm -f $(TARGET_N_LDS_GF)
	ar cvr $(TARGET_N_LDS_GF) $(N_LDS_GF_OBJS)

$(GF_TABLE_GENERATOR) : $(GF_TABLE_GENERATOR_OBJS)
	$(CC) -o $@ $^

$(GF_GEN_IRRED_POLY) : $(GF_GEN_IRRED_POLY_OBJS) $(TARGET_GF)
	$(CC) -o $@ $^ $(LIBFLAGS)

clean : 
	rm -f *.o $(TARGETS)