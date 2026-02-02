# Use a lightweight Ubuntu base
FROM --platform=linux/amd64 ubuntu:22.04

# Install compilers and the libraries we want to vendor
RUN apt-get update && apt-get install -y \
    build-essential \
    libsqlite3-dev \
    zlib1g-dev \
    file

# Set up the working directory
WORKDIR /app

# Copy our source code into the container
COPY . .

# --- VENDORING STEP ---
# We create local folders 
RUN mkdir -p lib include

# FIX: Use 'find' to locate the libraries automatically.
# This works on both Mac (ARM64) and Windows/Linux (x86_64).
RUN cp $(find /usr/lib -name "libsqlite3.so.0" | head -n 1) ./lib/libsqlite3.so
RUN cp $(find /usr/lib -name "libz.so.1" | head -n 1) ./lib/libz.so

# Run the build
RUN make
