together: sliders TestHarness
sliders: sliders.o main.o
	g++ -o sliders main.o sliders.o
TestHarness: sliders.o TestHarness.o
	g++ -o TestHarness TestHarness.o sliders.o
main.o: main.cc sliders.h
	g++ -c main.cc
sliders.o: sliders.cc sliders.h
	g++ -c sliders.cc
TestHarness.o: TestHarness.cc sliders.h
	g++ -c TestHarness.cc
