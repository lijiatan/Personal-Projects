ProgramName = main.exe
Compiler = g++
SRC := $(wildcard ./.program_folders/*.cpp)
compile: build run
build:
	$(Compiler) $(SRC) -o $(ProgramName)
run: 
	cmd /c start cmd /k main.exe
