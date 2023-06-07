# Start from a slim Ubuntu image
FROM ubuntu:latest

# Update the package list and install clang, lld, python3, and build-essential
RUN apt-get update && apt-get install -y \
    clang \
    lld \
    python3 \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /data

# Command to keep the container running
CMD ["/bin/bash"]

