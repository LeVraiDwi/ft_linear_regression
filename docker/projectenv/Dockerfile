# Use an official Python runtime as a parent image
FROM ubuntu:latest

# Set the working directory to /app
WORKDIR /app

RUN apt update

RUN apt upgrade -y

RUN apt install -y cmake python3-full pip clang python3-venv python3-pip

ENTRYPOINT ["tail", "-f", "/dev/null"]