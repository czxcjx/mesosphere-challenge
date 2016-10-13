CPPFLAGS=-g -Wall -Wextra -std=c++11 -iquote src/ -Wno-sign-compare
CXX=g++
SRCDIR=src
BINDIR=bin
OBJDIR=obj
LDFLAGS=
LIBS=

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(OBJDIR) $(BINDIR) main

main: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LIBS) $(OBJS) -o $(BINDIR)/main

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(LIBS) -c $< -o $@

clean:
	rm $(BINDIR)/* $(OBJDIR)/*.o
