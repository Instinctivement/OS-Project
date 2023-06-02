CC = gcc
CFLAGS = -Wall -pthread
SRCDIR = src
OBJDIR = object

# Liste des fichiers source
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Liste des fichiers objet correspondants
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Règle de compilation pour les fichiers objet
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de construction de l'exécutable
app: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJDIR)/*.o app

