<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->

<a name="readme-top"></a>
<br />

<div align="center">
  <a href="https://github.com/Volthai7us/IPC-Server/">
    <img src="https://avatars.githubusercontent.com/u/72819472?v=4" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">IPC Server</h3>

  <p align="center">
    Simple IPC Server implementation, using multithreading.
    <br /> <br />
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>
<br />

## Getting Started

This is actually an operating systems course assignment. But I will try to improve it by adding different features over time. In current version, you can use this project to send message between clients via server. To test it, run server and several clients ( with arg which is client's name). Then after writing message and receiver name, the receiver will get your message.

### Prerequisites

- A Linux based OS

- GCC Compiler

  1. Start by updating the packages list
     ```sh
     sudo apt update
     ```
  2. Install the build-essential package
     ```sh
     sudo apt install build-essential
     ```
  3. Validate that the GCC compiler is successfully installed
     ```sh
     gcc --version
     ```
     ```
     gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
     Copyright (C) 2019 Free Software Foundation, Inc.
     This is free software; see the source for copying conditions.  There is NO
     warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
     ```

  <p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Volthai7us/IPC-Server
   ```
2. Move to project folder
   ```sh
   cd IPC-Server
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Usage

1. Compile the scripts
   ```sh
   gcc -pthread client.c -o client
   gcc -pthread server.c -o server
   ```
2. Start server and clients
   ```sh
   ./server
   ./client username1
   ./client username2
   ./client username3
   ```
3. Print open mailboxes _(Optional)_
   ```sh
   ipcs -a | grep 0x
   ```
4. Remove all mailboxes after close server and clients _(Optional)_

   _Warning! Do not use -a if you are unsure how the software
   using the resources might react to missing objects. Some
   programs create these resources at startup and may not have
   any code to deal with an unexpected disappearance._

   ```sh
   ipcrm -a
   ```

Server

```console
Server is running. Waiting for users to connect...
emirsoyturk is connected
berfinozcubuk is connected
huseyinemre is connected
```

User 1

```console
Waiting server to accept registration...
You succesfully connected to server.
----------------
Write a message: Hello there.
Write a client id: berfinozcubuk
----------------
Write a message:
----------------
berfinozcubuk ----> Hi. How are you?
----------------
Write a message:
----------------
huseyinemre ----> Hello everyone
----------------
Write a message:
```

User 2

```console
Waiting to server accept registration...
You succesfully connected to server.
----------------
Write a message:
----------------
emirsoyturk ----> Hello there.
----------------
Write a message: Hi. How are you?
Write a client id: emirsoyturk
----------------
Write a message:
----------------
huseyinemre ----> Hello everyone
----------------
Write a message:
```

User 3

```console
Waiting to server accept registration...
You succesfully connected to server.
----------------
Write a message: Hello everyone
Write a client id: emirsoyturk
----------------
Write a message: Hello everyone
Write a client id: berfinozcubuk
----------------
Write a message:
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->

## Contact

Emir Soyturk - emirsytrk@gmail.com

<p align="right">(<a href="#readme-top">back to top</a>)</p>
