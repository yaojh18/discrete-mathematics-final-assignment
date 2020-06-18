all: bin/init.h bin/loader.h bin/data.h bin/m_algorithm.h src/data_process.cpp 
	g++ src/data_process.cpp -o src/data_process