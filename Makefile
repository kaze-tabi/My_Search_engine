bin/testDictProducer.exe:build/testDictProducer.o build/DictProducer.o
	g++ build/testDictProducer.o build/DictProducer.o -o bin/testDictProducer.exe -lworkflow
build/testDictProducer.o:test/testDictProducer.cc
	g++ -c test/testDictProducer.cc -o build/testDictProducer.o -g -Wall -I include
build/DictProducer.o:src/DictProducer.cc include/DictProducer.h
	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include
build/SplitToolCppThulac.o:src/SplitToolCppThulac.cc include/SplitToolCppThulac.h include/SplitTool.h vendor/THULAC/thulac.h
	g++ -c src/SplitToolCppThulac.cc -o build/SplitToolCppThulac.o -g -Wall -I include