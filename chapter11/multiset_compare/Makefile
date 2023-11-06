
CXX=g++
CXX_FLAGS=-Wall -g -o0
CXX_LDFLAGS=
BIN=multiset_cmp
output_dir=output

all:${output_dir} $(BIN) 

${output_dir}:
	@mkdir -p $@

${BIN}:${output_dir}/main.o ${output_dir}/Sales_data.o
	${CXX} $^ -o $@

${output_dir}/main.o:src/main.cpp src/Sales_data.h
	$(CXX) $(CXX_FLAGS) $< -c -o $@

${output_dir}/Sales_data.o:src/Sales_data.cpp
	$(CXX) $(CXX_FLAGS) $< -c -o $@

PHONY:clean

clean:
	rm ${output_dir} ${BIN} -rf
