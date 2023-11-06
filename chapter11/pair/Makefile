

CXX=g++
CXX_FLAGS=-Wall -g -o0
CXX_LDFLAGS=
BIN=pair
output_dir=output

all:${output_dir} ${BIN}

${output_dir}:
	@mkdir $@

${BIN}:src/main.cpp
	${CXX} ${CXX_FLAGS}  $< -o ${output_dir}/$@

phony:clean

clean:
	rm ${BIN}  ${output_dir} -rf
