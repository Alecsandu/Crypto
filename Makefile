CC = gcc
CFLAGS = -g -Wall -std=c99

INSTALLDIR = build

OUTPUTFILE = crypto
OUTPUT_TEST_FILE = crypto_ut

# Default target
.PHONY: all
all: $(OUTPUTFILE)
$(OUTPUTFILE): $(OUTPUTFILE).c
	$(CC) $(CFLAGS) -o $(OUTPUTFILE) $(OUTPUTFILE).c

.PHONY: build_tests
build_tests: $(OUTPUT_TEST_FILE)
$(OUTPUT_TEST_FILE): $(OUTPUT_TEST_FILE).c
	$(CC) $(CFLAGS) -o $(OUTPUT_TEST_FILE) $(OUTPUT_TEST_FILE).c

# Run tests target
.PHONY: run_tests
run_tests: build_tests
	./$(OUTPUT_TEST_FILE)

# Install target
.PHONY: install
install: all
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

# Clean target
.PHONY: clean
clean:
	$(RM) -f $(OUTPUTFILE) $(INSTALLDIR)/$(OUTPUTFILE)
	$(RM) -f $(OUTPUT_TEST_FILE) $(INSTALLDIR)/$(OUTPUT_TEST_FILE)
