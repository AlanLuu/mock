install_path=/usr/local/bin
main_program_name=mock
CC?=cc
CFLAGS?=-Wall -Wextra -pedantic-errors -Wshadow -Wformat=2 -Wconversion -Wunused-parameter -O2

$(main_program_name): $(main_program_name).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(main_program_name) $(main_program_name).c

install: $(main_program_name)
	strip $(main_program_name)
	install $(main_program_name) $(install_path)

debug: $(main_program_name).c
	$(CC) -g -o $(main_program_name) $(main_program_name).c

run: $(main_program_name)
	./$(main_program_name)

clean:
	rm -f $(main_program_name)

uninstall:
	rm -f $(install_path)/$(main_program_name)
