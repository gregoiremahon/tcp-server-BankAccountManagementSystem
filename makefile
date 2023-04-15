CC = gcc
CFLAGS = -Wall -Wextra -pthread
OUTPUT_DIR = ./app
TARGET_PREFIX = $(OUTPUT_DIR)/

TCP_SRC = ./src/TCP
UDP_SRC = ./src/UDP
MT_TCP_SRC = ./src/multi-thread_version/TCP
MT_UDP_SRC = ./src/multi-thread_version/UDP

all: create_output_dir $(TARGET_PREFIX)client_TCP $(TARGET_PREFIX)server_TCP_mono-client $(TARGET_PREFIX)client_UDP $(TARGET_PREFIX)server_UDP_mono-client $(TARGET_PREFIX)server_TCP_multithread $(TARGET_PREFIX)server_UDP_multithread

create_output_dir:
	mkdir -p $(OUTPUT_DIR)

$(TARGET_PREFIX)client_TCP: $(TCP_SRC)/client_TCP.c
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_PREFIX)server_TCP_mono-client: $(TCP_SRC)/server_TCP_mono-client.c $(TCP_SRC)/server.h
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET_PREFIX)client_UDP: $(UDP_SRC)/client_UDP.c
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_PREFIX)server_UDP_mono-client: $(UDP_SRC)/server_UDP_mono-client.c $(UDP_SRC)/server.h
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET_PREFIX)server_TCP_multithread: $(MT_TCP_SRC)/server_TCP_multithread.c $(MT_TCP_SRC)/server.h
	$(CC) $(CFLAGS) -o $@ $<

$(TARGET_PREFIX)server_UDP_multithread: $(MT_UDP_SRC)/server_UDP_multithread.c $(MT_UDP_SRC)/server.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OUTPUT_DIR)
