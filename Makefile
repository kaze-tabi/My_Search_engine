# bin/testDictProducer.exe:build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o
# 	g++ build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o -o bin/testDictProducer.exe -lworkflow
# build/testDictProducer.o:test/testDictProducer.cc
# 	g++ -c test/testDictProducer.cc -o build/testDictProducer.o -g -Wall -I include
# build/DictProducer.o:src/DictProducer.cc include/DictProducer.h
# 	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include
# build/SplitToolCppJieba.o:src/SplitToolCppJieba.cc include/SplitToolCppJieba.h
# 	g++ -c src/SplitToolCppJieba.cc -o build/SplitToolCppJieba.o -g -Wall -I include
 

bin/test_Dictionary.exe: build/test_Dictionary.o build/Dictionary.o build/DictProducer.o build/SplitToolCppJieba.o
	g++ build/test_Dictionary.o build/Dictionary.o build/DictProducer.o build/SplitToolCppJieba.o -o bin/test_Dictionary.exe -lworkflow
build/test_Dictionary.o: test/test_Dictionary.cc
	g++ -c test/test_Dictionary.cc -o build/test_Dictionary.o -g -Wall -I include
build/Dictionary.o: src/Dictionary.cc include/Dictionary.h
	g++ -c src/Dictionary.cc -o build/Dictionary.o -g -Wall -I include
build/DictProducer.o: src/DictProducer.cc include/DictProducer.h
	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include
