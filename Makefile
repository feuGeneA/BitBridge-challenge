all: test benchmark
	./test
	./benchmark

test: listutil.h \
      node.h \
      randomstring.h \
      test.m.cpp \
      dependencies/googletest/build/googlemock/gtest/libgtest.a
	g++ test.m.cpp -o test -std=c++11 -g -pthread \
	    -isystem dependencies/googletest/googletest/include \
	             dependencies/googletest/build/googlemock/gtest/libgtest.a \
		         dependencies/googletest/build/googlemock/gtest/libgtest_main.a

benchmark: listutil.h \
           node.h \
           benchmark.m.cpp \
           dependencies/benchmark
	g++ benchmark.m.cpp -o benchmark -std=c++11 -pthread \
	    -isystem dependencies/benchmark/include \
	             dependencies/benchmark/build/src/libbenchmark.a \
	             dependencies/benchmark/build/src/libbenchmark_main.a

dependencies/googletest/build/googlemock/gtest/libgtest.a: dependencies/googletest
	mkdir dependencies/googletest/build
	cd dependencies/googletest/build; cmake ..
	cd dependencies/googletest/build; make

dependencies/googletest:
	if [ ! -e dependencies ]; then mkdir dependencies; fi
	cd dependencies; git clone https://github.com/google/googletest.git

dependencies/benchmark: dependencies/googletest
	cd dependencies; git clone https://github.com/google/benchmark.git
	cd dependencies/benchmark; ln -sf ../googletest googletest
	mkdir dependencies/benchmark/build
	cd dependencies/benchmark/build; cmake .. -DCMAKE_BUILD_TYPE=RELEASE -DBENCHMARK_ENABLE_GTEST_TESTS=OFF
	cd dependencies/benchmark/build; make

clean:
	rm -rf test benchmark dependencies
