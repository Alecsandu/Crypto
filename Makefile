CC = gcc
CFLAGS = -g -Wall -std=c99

INSTALLDIR = build

OUTPUTFILE = crypto
OUTPUT_TEST_FILE = crypto_ut
ENCRYPTED_IMAGE_NAME = encodedpeppers.bmp
DECRYPTED_IMAGE_NAME = decodedpeppers.bmp

# Compile & create build folder
.PHONY: all
all: $(OUTPUTFILE)
$(OUTPUTFILE): $(OUTPUTFILE).c
	$(CC) $(CFLAGS) -o $(OUTPUTFILE) $(OUTPUTFILE).c

.PHONY: install
install: all
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)


# Compile & run tests
.PHONY: build_tests
build_tests: $(OUTPUT_TEST_FILE)
$(OUTPUT_TEST_FILE): $(OUTPUT_TEST_FILE).c
	$(CC) $(CFLAGS) -o $(OUTPUT_TEST_FILE) $(OUTPUT_TEST_FILE).c

.PHONY: run_tests
run_tests: build_tests
	./$(OUTPUT_TEST_FILE)


# Clean generated files and directories
.PHONY: clean
clean:
	$(RM) -f $(OUTPUTFILE) $(INSTALLDIR)/$(OUTPUTFILE)
	$(RM) -f $(OUTPUT_TEST_FILE) $(INSTALLDIR)/$(OUTPUT_TEST_FILE)
	${RM} -rf $(INSTALLDIR)/
	${RM} -f $(ENCRYPTED_IMAGE_NAME)
	${RM} -f $(DECRYPTED_IMAGE_NAME)
