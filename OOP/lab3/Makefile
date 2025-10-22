all: graphics testMixture testEmpiric

graphics: 
	g++ main.cpp ../lab2/MainDist.cpp MixtureDist.cpp EmpiricDist.cpp ../lab1/dist.cpp ../lab1/mixture.cpp ../lab1/empiric.cpp -o gen_graph

testMixture:
	g++ test/testMixture.cpp ../lab2/MainDist.cpp MixtureDist.cpp  -o testMixture.out

testEmpiric:
	g++ test/testEmpiric.cpp ../lab2/MainDist.cpp MixtureDist.cpp EmpiricDist.cpp -o testEmpiric.out	