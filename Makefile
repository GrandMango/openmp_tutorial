CXX= g++
CXXFLAGS= -std=c++14 -O2 -fopenmp 
SRC=$(wildcard *.cc)
EXF=$(SRC:%.cc=%)
CUR_DIR= $(shell pwd)
OUT_DIR= $(CUR_DIR)/build
OBJ_DIR = $(OUT_DIR)/obj
all: create_dir $(EXF)

define CRT_DIR
	if [ ! -d $(1) ];\
	 	then\
    	mkdir -p $(1);\
    	echo "******$(1) created success!!!******";\
    else\
      echo "******$(1) has been created!!!******";\
	fi	
endef

print:
	@echo EXF: $(EXF)

create_dir:  
	@$(call CRT_DIR,$(OUT_DIR))

$(EXF):%:%.cc
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$@ $<
	
#vector_sum_1: vector_sum_1.cc
#	$(CXX) vector_sum_1.cc $(CXXFLAGS) -o vector_sum_1

#vector_sum_2: vector_sum_2.cc
#	$(CXX) vector_sum_2.cc $(CXXFLAGS) -o vector_sum_2

#vector_sum_scoped: vector_sum_scoped.cc
#	$(CXX) vector_sum_scoped.cc $(CXXFLAGS) -o vector_sum_scoped

clean:
	rm -f $(EXF)
	rm -rf $(OUT_DIR)

