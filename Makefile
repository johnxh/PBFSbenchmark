CC=/project/cec/class/cse539/tapir/build/bin/clang
CXX=/project/cec/class/cse539/tapir/build/bin/clang++
CILK_LIBS=/project/linuxlab/gcc/6.4/lib64

CFLAGS = -ggdb -O3 -fcilkplus
CXXFLAGS = -ggdb -O3 -fcilkplus
LIBS = -L$(CILK_LIBS) -Wl,-rpath -Wl,$(CILK_LIBS) -lcilkrts -lpthread -lrt -lm
PROGS = pbfs

INST_RTS_LIBS=/project/cec/class/cse539/inst-cilkplus-rts/lib
INST_LIBS = -L$(INST_RTS_LIBS) -Wl,-rpath -Wl,$(INST_RTS_LIBS) -lcilkrts -lpthread -lrt -lm -ldl

all:: $(PROGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

pbfs: ktiming.o pbfs.o
	$(CXX) -o $@ $^ $(LIBS)



clean::
	-rm -f $(PROGS) *.o
