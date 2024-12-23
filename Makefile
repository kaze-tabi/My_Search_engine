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



bin/main.exe: build/WebPageQuery.o \
              build/WebSearch.o \
              build/WebPage.o \
              build/SearchEngineServer.o \
              build/NetServer.o \
			  build/CandidateResult.o \
              build/KeyRecommander.o \
              build/DoubleLRU.o \
              build/Dictionary.o \
              build/CacheManager.o \
              build/BigLRUcache.o \
              build/SplitToolCppJieba.o \
              build/Configuration.o \
              build/SynCacge.o \
              build/main.o 
	g++ \
              build/WebPageQuery.o \
              build/WebSearch.o \
              build/WebPage.o \
              build/SearchEngineServer.o \
              build/NetServer.o \
			  build/CandidateResult.o \
              build/KeyRecommander.o \
              build/DoubleLRU.o \
              build/Dictionary.o \
              build/CacheManager.o \
              build/BigLRUcache.o \
              build/SplitToolCppJieba.o \
              build/Configuration.o \
              build/SynCacge.o \
              build/main.o \
              -o bin/main.exe \
              -lworkflow -ltinyxml2 -lwfrest

build/SplitToolCppJieba.o: src/offline/SplitToolCppJieba.cc include/offline/SplitToolCppJieba.h
	g++ -c src/offline/SplitToolCppJieba.cc -o build/SplitToolCppJieba.o -g -Wall -I include -I include/offline -I include/online

build/Configuration.o: src/offline/Configuration.cc include/offline/Configuration.h
	g++ -c src/offline/Configuration.cc -o build/Configuration.o -g -Wall -I include -I include/offline -I include/online

build/Dictionary.o: src/online/Dictionary.cc include/online/Dictionary.h
	g++ -c src/online/Dictionary.cc -o build/Dictionary.o -g -Wall -I include -I include/offline -I include/online

build/WebPage.o: src/offline/WebPage.cc include/offline/WebPage.h
	g++ -c src/offline/WebPage.cc -o build/WebPage.o -g -Wall -I include -I include/offline

build/WebPageQuery.o: src/online/WebPageQuery.cc include/online/WebPageQuery.h 
	g++ -c src/online/WebPageQuery.cc -o build/WebPageQuery.o -g -Wall -I include -I include/offline -I include/online

build/CandidateResult.o: src/online/CandidateResult.cc include/online/CandidateResult.h 
	g++ -c src/online/CandidateResult.cc -o build/CandidateResult.o -g -Wall -I include -I include/offline -I include/online

build/WebSearch.o: src/online/WebSearch.cc include/online/WebSearch.h 
	g++ -c src/online/WebSearch.cc -o build/WebSearch.o -g -Wall -I include -I include/offline -I include/online

build/KeyRecommander.o: src/online/KeyRecommander.cc include/online/KeyRecommander.h 
	g++ -c src/online/KeyRecommander.cc -o build/KeyRecommander.o -g -Wall -I include -I include/offline -I include/online

build/DoubleLRU.o: src/online/DoubleLRU.cc include/online/DoubleLRU.h include/online/LRUCache.h
	g++ -c src/online/DoubleLRU.cc -o build/DoubleLRU.o -g -Wall -I include -I include/offline -I include/online

build/SynCacge.o: src/online/SynCacge.cc include/online/SynCacge.h
	g++ -c src/online/SynCacge.cc -o build/SynCacge.o -g -Wall -I include -I include/offline -I include/online

build/CacheManager.o: src/online/CacheManager.cc include/online/CacheManager.h 
	g++ -c src/online/CacheManager.cc -o build/CacheManager.o -g -Wall -I include -I include/offline -I include/online

build/BigLRUcache.o: src/online/BigLRUcache.cc include/online/BigLRUcache.h 
	g++ -c src/online/BigLRUcache.cc -o build/BigLRUcache.o -g -Wall -I include -I include/offline -I include/online

build/NetServer.o: src/online/NetServer.cc include/online/NetServer.h 
	g++ -c src/online/NetServer.cc -o build/NetServer.o -g -Wall -I include -I include/offline -I include/online

build/SearchEngineServer.o: src/online/SearchEngineServer.cc include/online/SearchEngineServer.h 
	g++ -c src/online/SearchEngineServer.cc -o build/SearchEngineServer.o -g -Wall -I include -I include/offline -I include/online

build/main.o: src/main.cc
	g++ -c src/main.cc -o build/main.o -g -Wall -I include -I include/offline -I include/online