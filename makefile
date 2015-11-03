CXX        := g++-4.8
CXXFLAGS   += -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f Coach
	rm -f Coach.tmp
	rm -f TestCoach
	rm -f TestCoach.tmp

config:
	git config -l

scrub:
	make  clean
	rm -f  Coach.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: Coach.tmp TestCoach.tmp

Coach: coach.h coach.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) coach.c++ -o Coach

Coach.tmp: Coach
	./Coach < Coach.in > Coach.tmp
	diff Coach.tmp Coach.out

TestCoach: coach.h coach.c++ TestCoach.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) coach.c++ TestCoach.c++ -o TestCoach $(LDFLAGS)

TestCoach.tmp: TestCoach
	$(VALGRIND) ./TestCoach
	$(GCOV) -b coach.c++     | grep -A 5 "File 'coach.c++'"     >> TestCoach.tmp
	$(GCOV) -b TestCoach.c++ | grep -A 5 "File 'TestCoach.c++'" >> TestCoach.tmp
	cat TestCoach.tmp
