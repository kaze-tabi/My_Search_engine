bin/testDictProducer.exe:build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o
	g++ build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o -o bin/testDictProducer.exe -lworkflow
build/testDictProducer.o:test/testDictProducer.cc
	g++ -c test/testDictProducer.cc -o build/testDictProducer.o -g -Wall -I include
build/DictProducer.o:src/DictProducer.cc include/DictProducer.h
	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include
build/SplitToolCppJieba.o:src/SplitToolCppJieba.cc include/SplitToolCppJieba.h
	g++ -c src/SplitToolCppJieba.cc -o build/SplitToolCppJieba.o -g -Wall -I include
 