CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla
EXEC = chess
OBJECTS = Subject.o main.o Board.o GameState.o Setup.o Computer.o TextDisplay.o Cell.o GraphicsDisplay.o Window.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
        ${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 

-include ${DEPENDS}

.PHONY: clean

clean:
        rm ${OBJECTS} ${EXEC} ${DEPENDS}
~                                                   