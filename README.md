# Network namespace runner

Execute program in an existing network namespace.

**Warning:** This program needs elevated permissions to
do it's job. It also allows to join network namespaces
of other processes running as root and **also escape them
again**! It's not a tool to make your processes "secure"!

Make sure to understand the implications.

For most cases tools like firejail, nsenter and others may
be more capable.

## Why?

The main purpose of this tool is currently to run programs
within a different network namespace - for example a VPN
only namespace. This allows to contain the network traffic
for this program.


## Build
```
make
sudo chown root:nsrun nsrun
sudo chmod 4754 nsrun
```

Create a group nsrun and add yourself to group nsrun.


## Usage

Join a named network namespace:
```
NAMESPACE=/var/run/netns/mynamespace
./nsrun $NAMESPACE /usr/bin/bash -l
```

Join a namespace of another process

```
NAMESPACE=/proc/PID/ns/net
./nsrun $NAMESPACE /usr/bin/bash -l
```

