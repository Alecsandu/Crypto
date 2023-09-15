CC = gcc

CFLAGS = -g -Wall

INSTALLDIR = build

OUTPUTFILE = crypto

# Default target
.PHONY: all
all: $(OUTPUTFILE)
$(ODIR)/$(OUTPUTFILE): $(OUTPUTFILE).c
	$(CC) $(CFLAGS) -o $(OUTPUTFILE) $(OUTPUTFILE).c

# Install target
.PHONY: install
install: 
	mkdir -p $(INSTALLDIR)
	cp -p $(OUTPUTFILE) $(INSTALLDIR)

# Clean target
.PHONY: clean
clean:
	$(RM) -f $(OUTPUTFILE) $(INSTALLDIR)/$(OUTPUTFILE)

