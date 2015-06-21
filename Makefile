all:
	@g++ GeneticProgramming/*.cpp -std=c++11 -O3 `pkg-config --libs libSimpleAmqpClient` -o gp

run:
	@./gp

clean:
	@rm ./gp
	@rm ./ControlEngine/robots/GP/*
