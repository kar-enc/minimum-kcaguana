#updated with gpt6.1 sol
PROGRAMS := minimum-user

.PHONY: all lib programs clean $(PROGRAMS)

all: programs

lib:
	$(MAKE) -C lib all

programs: $(PROGRAMS)

$(PROGRAMS): lib
	$(MAKE) -C prog/$@ all

clean:
	$(MAKE) -C lib clean
	@for program in $(PROGRAMS); do $(MAKE) -C prog/$$program clean; done