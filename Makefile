CXX= g++
CXXFLAGS= -std=c++14 -O2 -fopenmp
CUR_DIR=$(shell pwd)
SRC_DIR=$(CUR_DIR)/src 
OUT_DIR=$(CUR_DIR)/build
SRC=$(wildcard src/*.cc)
SRC_NODIR=$(notdir $(SRC))
EXF=$(SRC_NODIR:%.cc=%)

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
	@echo SRC_DIR: $(SRC_DIR)
	@echo SRC: $(SRC)
	@echo EXF: $(EXF)

create_dir:  
	@$(call CRT_DIR,$(OUT_DIR))

$(EXF):%:src/%.cc
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$@ $<
	
#vector_sum_1: vector_sum_1.cc
#	$(CXX) vector_sum_1.cc $(CXXFLAGS) -o vector_sum_1


clean:
	rm -rf $(OUT_DIR)

