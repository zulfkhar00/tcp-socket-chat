# TCP Socket Chat 🗣️

`tcp-socket-chat` is a simple TCP client and server implementation using socket programming and the fork() function in C. This project provides practice in working with sockets, processes, and getting familiar with the TCP transport protocol.

## Table of Contents

- [Features](#features)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features ✨

- TCP client and server written in C
- Offers a simple chat system using TCP sockets and the fork() function
- Server listens on port 6000 for incoming connections
- Server replies to client messages with the received message
- Support for multiple simultaneously connected clients
- Great for learning and understanding socket programming, processes, and the TCP transport protocol

## Dependencies 📚

- A C compiler (such as GCC) and a Unix-based system (Linux, macOS, etc.) with standard C libraries

## Installation ⚙️

1. Clone this repository:

   `git clone https://github.com/zulfkhar00/tcp-socket-chat.git`

2. Compile both client and server programs using the provided Makefile:
   ```
   cd tcp-socket-chat
   make all
   ```

4. This will create two executables: `./client` and `./server`.

## Usage 🚀

Both the client and server programs should be run from two different terminal windows.

1. First, run the server program in one terminal:

   `./server`

   The TCP server opens a socket on port 6000, monitoring for incoming connections. Upon establishing a connection, it responds to the client using the received message. It can handle multiple connected clients concurrently by utilizing the fork() function to create child processes for each client. Child processes are terminated when the server receives a "BYE!" message from a client or if a message of length 0 is received (indicating closure of the socket or client termination via Ctrl+C). The server logs incoming and outgoing messages, providing client IP addresses and port numbers. Additionally, it logs client connection and disconnection events.

2. In another terminal window, run the client program:

   `./client`

   The TCP client application initiates a socket connection to the server at port 6000. It prompts the user to enter a message which, upon submission, is transmitted to the server. The client then awaits a response. Exiting the client occurs when the user inputs the message "BYE!"—this action closes the socket, thereby ending the connection.

## Contributing 🤝

1. Fork the Repository

2. Clone your fork

3. Create your feature branch (`git checkout -b feature/AmazingFeature`)

4. Commit your changes (`git commit -m 'Add some AmazingFeature'`)

5. Push to the branch (`git push origin feature/AmazingFeature`)

6. Open a Pull Request

## License 📄

This project is licensed under the MIT License. Please see the [LICENSE](LICENSE) file for more details.
