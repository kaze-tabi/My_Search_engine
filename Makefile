# bin/testDictProducer.exe:build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o
# 	g++ build/testDictProducer.o build/DictProducer.o build/SplitToolCppJieba.o -o bin/testDictProducer.exe -lworkflow
# build/testDictProducer.o:test/testDictProducer.cc
# 	g++ -c test/testDictProducer.cc -o build/testDictProducer.o -g -Wall -I include
# build/DictProducer.o:src/DictProducer.cc include/DictProducer.h
# 	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include
# build/SplitToolCppJieba.o:src/SplitToolCppJieba.cc include/SplitToolCppJieba.h
# 	g++ -c src/SplitToolCppJieba.cc -o build/SplitToolCppJieba.o -g -Wall -I include
 

# bin/test_Dictionary.exe: build/test_Dictionary.o build/Dictionary.o build/DictProducer.o build/SplitToolCppJieba.o
# 	g++ build/test_Dictionary.o build/Dictionary.o build/DictProducer.o build/SplitToolCppJieba.o -o bin/test_Dictionary.exe -lworkflow
# build/test_Dictionary.o: test/test_Dictionary.cc
# 	g++ -c test/test_Dictionary.cc -o build/test_Dictionary.o -g -Wall -I include
# build/Dictionary.o: src/Dictionary.cc include/Dictionary.h
# 	g++ -c src/Dictionary.cc -o build/Dictionary.o -g -Wall -I include
# build/DictProducer.o: src/DictProducer.cc include/DictProducer.h
# 	g++ -c src/DictProducer.cc -o build/DictProducer.o -g -Wall -I include


# bin/testCong.exe: build/testCong.o build/DirScanner.o build/Configuration.o 
# 	g++ build/testCong.o build/DirScanner.o build/Configuration.o -o bin/testCong.exe -lworkflow
# build/testCong.o: test/testCong.cc
# 	g++ -c test/testCong.cc -o build/testCong.o -g -Wall -I include -I include/offline
# build/DirScanner.o: src/offline/DirScanner.cc include/offline/DirScanner.h
# 	g++ -c src/offline/DirScanner.cc -o build/DirScanner.o -g -Wall -I include -I include/offline
# build/Configuration.o: src/offline/Configuration.cc include/offline/Configuration.h
# 	g++ -c src/offline/Configuration.cc -o build/Configuration.o -g -Wall -I include -I include/offline



# bin/testPageLib.exe: build/PageLib.o build/DirScanner.o build/Configuration.o build/testPageLib.o
# 	g++ build/PageLib.o build/DirScanner.o build/Configuration.o build/testPageLib.o -o bin/testPageLib.exe -lworkflow -ltinyxml2
# build/PageLib.o: src/offline/PageLib.cc
# 	g++ -c src/offline/PageLib.cc -o build/PageLib.o -g -Wall -I include -I include/offline
# build/DirScanner.o: src/offline/DirScanner.cc include/offline/DirScanner.h
# 	g++ -c src/offline/DirScanner.cc -o build/DirScanner.o -g -Wall -I include -I include/offline
# build/Configuration.o: src/offline/Configuration.cc include/offline/Configuration.h
# 	g++ -c src/offline/Configuration.cc -o build/Configuration.o -g -Wall -I include -I include/offline
# build/testPageLib.o: test/testPageLib.cc
# 	g++ -c test/testPageLib.cc -o build/testPageLib.o -g -Wall -I include -I include/offline



bin/TestPageLibPreprocessor.exe: build/PageLib.o build/DirScanner.o build/Configuration.o build/PageLibPreprocessor.o build/WebPage.o build/SplitToolCppJieba.o build/TestPageLibPreprocessor.o
	g++ build/PageLib.o build/DirScanner.o build/Configuration.o build/PageLibPreprocessor.o build/WebPage.o build/SplitToolCppJieba.o build/TestPageLibPreprocessor.o -o bin/TestPageLibPreprocessor.exe -lworkflow -ltinyxml2

build/PageLib.o: src/offline/PageLib.cc
	g++ -c src/offline/PageLib.cc -o build/PageLib.o -g -Wall -I include -I include/offline

build/DirScanner.o: src/offline/DirScanner.cc include/offline/DirScanner.h
	g++ -c src/offline/DirScanner.cc -o build/DirScanner.o -g -Wall -I include -I include/offline

build/Configuration.o: src/offline/Configuration.cc include/offline/Configuration.h
	g++ -c src/offline/Configuration.cc -o build/Configuration.o -g -Wall -I include -I include/offline

build/TestPageLibPreprocessor.o: test/TestPageLibPreprocessor.cc
	g++ -c test/TestPageLibPreprocessor.cc -o build/TestPageLibPreprocessor.o -g -Wall -I include -I include/offline

build/PageLibPreprocessor.o: src/offline/PageLibPreprocessor.cc include/offline/PageLibPreprocessor.h
	g++ -c src/offline/PageLibPreprocessor.cc -o build/PageLibPreprocessor.o -g -Wall -I include -I include/offline

build/SplitToolCppJieba.o: src/offline/SplitToolCppJieba.cc include/offline/SplitToolCppJieba.h
	g++ -c src/offline/SplitToolCppJieba.cc -o build/SplitToolCppJieba.o -g -Wall -I include -I include/offline

build/WebPage.o: src/offline/WebPage.cc include/offline/WebPage.h
	g++ -c src/offline/WebPage.cc -o build/WebPage.o -g -Wall -I include -I include/offline





clean:
# rm -f bin/TestPageLibPreprocessor.exe
	rm -f build/*.o