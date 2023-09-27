CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -pedantic

BUILD_DIR = build

OUTPUTFILE = crypto
OUTPUT_TEST_FILE = crypto_ut
ENCRYPTED_IMAGE_NAME = encodedpeppers.bmp
DECRYPTED_IMAGE_NAME = decodedpeppers.bmp

.PHONY: all clean install build_tests run_tests

# Compile & create build folder
all: $(OUTPUTFILE)
$(OUTPUTFILE): $(OUTPUTFILE).c
	$(CC) $(CFLAGS) -o $(OUTPUTFILE) $(OUTPUTFILE).c

install: all
	mkdir -p $(BUILD_DIR)
	cp -p $(OUTPUTFILE) $(BUILD_DIR)


# Compile & run tests
build_tests: $(OUTPUT_TEST_FILE)
$(OUTPUT_TEST_FILE): $(OUTPUT_TEST_FILE).c
	$(CC) $(CFLAGS) -o $(OUTPUT_TEST_FILE) $(OUTPUT_TEST_FILE).c

run_tests: build_tests
	./$(OUTPUT_TEST_FILE)


# Clean generated files and directories
clean:
	$(RM) -f $(OUTPUTFILE) $(BUILD_DIR)/$(OUTPUTFILE)
	$(RM) -f $(OUTPUT_TEST_FILE) $(BUILD_DIR)/$(OUTPUT_TEST_FILE)
	${RM} -rf $(BUILD_DIR)/
	${RM} -f $(ENCRYPTED_IMAGE_NAME)
	${RM} -f $(DECRYPTED_IMAGE_NAME)
