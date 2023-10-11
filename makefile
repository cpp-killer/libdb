compiler=c++
src=./src/
inc=./include/
target=libdb.a
flags=-DOS_UNIX

SRCS := $(wildcard $(src)*.cpp)
OBJS := $(patsubst %cpp,%o,$(SRCS))


$(target): $(OBJS)
	ar -r $(target) $(OBJS)

$(OBJS):%.o: %.cpp
	$(compiler) -Wall $(flags) -c $< -o $@ -I$(inc)

.PHONY:clean
clean:
	@rm -vrf $(OBJS)
	@rm -vrf $(target)