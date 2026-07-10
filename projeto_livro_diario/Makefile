CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS  = -lsqlite3
TARGET   = livro_diario
SRCS     = main.cpp db.cpp utils.cpp entidade.cpp lancamento.cpp relatorio.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) livro_diario.db

.PHONY: all clean
