.PHONY: clean test

CC=gcc
CFLAGS= -g -Wall

TARGET=pl0
OBJS=lexer.o token.o utils.o
TESTS=token_test lexer_test


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) pl0.c $(OBJS) -o $(TARGET)

$(TESTS): $(OBJS)


test: $(TESTS)
	@$(foreach test, $(TESTS), ./$(test) && echo "";)
	@echo ">>> all tests passed! <<<"


clean:
	rm -rf *.o $(TARGET) $(TESTS)
