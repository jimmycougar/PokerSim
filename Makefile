PRODUCT = PokerSim
BUILDDIR = build
DESTDIR = bin
SRCDIR = src

MAINSRC = \
	main.cpp

MODELSRC = \
	card.cpp \
	deck.cpp \
	player.cpp \
	seat.cpp \
	regulator.cpp

VIEWSRC = \
	cardprinter.cpp

CONTROLSRC = \
	controller.cpp

MODELDIR = model
VIEWDIR = view
CONTROLDIR = controller

CC = g++
CFLAGS = -g -Wall -Werror -pedantic

SRC = $(MAINSRC)
SRC += $(addprefix $(MODELDIR)/, $(MODELSRC))
SRC += $(addprefix $(VIEWDIR)/, $(VIEWSRC))
SRC += $(addprefix $(CONTROLDIR)/, $(CONTROLSRC))

OBJ = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SRC))))

INCDIRS = $(SRCDIR)

LIBS =

all: clean builddirs $(DESTDIR) $(DESTDIR)/$(PRODUCT)

$(DESTDIR)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c -o $@ $^ $(CFLAGS) $(addprefix -I, $(INCDIRS))

builddirs:
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/$(MODELDIR)
	mkdir -p $(BUILDDIR)/$(VIEWDIR)
	mkdir -p $(BUILDDIR)/$(CONTROLDIR)

$(DESTDIR):
	mkdir -p $(DESTDIR)

clean:
	rm -rf $(BUILDDIR)
	rm -f $(DESTDIR)/$(PRODUCT)

