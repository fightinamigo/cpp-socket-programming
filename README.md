# 🔌 C++ Socket Programming — TCP & UDP Implementations

Low-level network programming in C++ using the **Winsock2 API** on Windows. This project demonstrates two classic client-server architectures built from scratch.

---

## 📡 Projects Included

### 1. UDP DNS Resolver
Simulates a basic DNS lookup system over UDP.

- Client sends a hostname (e.g. `google.com`)
- Server looks it up in a local DNS table and returns the IP address
- Uses `SOCK_DGRAM` (connectionless UDP)

**Hardcoded DNS Table:**
| Hostname | IP Address |
|---|---|
| google.com | 142.250.190.46 |
| youtube.com | 208.65.153.238 |
| facebook.com | 157.240.195.35 |
| local | 127.0.0.1 |

---

### 2. TCP Password Cracker Simulator
Simulates a password strength analyzer over TCP.

- Client sends a password to the server
- Server attempts a **dictionary attack** (common passwords list) then a **brute force attack** (0–999)
- Server responds with the result
- Uses `SOCK_STREAM` (connection-based TCP)

> ⚠️ **Educational purposes only.** This is a simulation to demonstrate TCP client-server communication and basic security concepts.

---

## 💡 Concepts Demonstrated

| Concept | Description |
|---|---|
| UDP Sockets | Connectionless `sendto`/`recvfrom` |
| TCP Sockets | Connection-based `connect`/`send`/`recv` |
| Winsock2 API | Windows socket initialization, cleanup |
| Client-Server Architecture | Separate client and server processes |
| `std::map` | Used for O(1) DNS table lookup |
| Dictionary Attack Simulation | Matching against common passwords |
| Brute Force Simulation | Iterating 0–999 numeric pins |
| Port Management | UDP on 8080, TCP on 8081 |

---

## 🛠️ Build & Run

**Requirements:** Windows, C++20, CMake 4.0+, Winsock2 (included with Windows SDK)

```bash
git clone https://github.com/YOUR_USERNAME/cpp-socket-programming
cd cpp-socket-programming
mkdir build && cd build
cmake ..
make
```

**Run UDP DNS:**
```bash
# Terminal 1
./udp_dns_server

# Terminal 2
./udp_dns_client
# Enter: google.com
```

**Run TCP Password Cracker:**
```bash
# Terminal 1
./tcp_crack_server

# Terminal 2
./tcp_crack_client
# Enter: admin
```

---

## 📁 Project Structure

```
├── udp_dns_server.cpp    # DNS server (UDP)
├── udp_dns_client.cpp    # DNS client (UDP)
├── tcp_crack_server.cpp  # Password cracker server (TCP)
├── tcp_crack_client.cpp  # Password cracker client (TCP)
└── CMakeLists.txt
```

---

## 📌 Notes

- Both implementations run on `127.0.0.1` (localhost)
- Server processes run in infinite loops, ready for multiple client connections
- TCP server closes the client socket after each request (stateless per request)
