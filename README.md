## Terminal IO

Terminal IO is a hard project, with a lot of legacy things to think about. Terminal is a term for a lot of things which are designed for the interactions between human and computers. TODO: more thing on legacy devices

There are a lot of old devices never used these days, but the terminal io library have to support them(because they used to support them). Therefore, a lot of properties set in `termio` struct, terminal information, are never used today. Setting them never makes sense any more.

Terminal IO gives the program a special way to do IO, more detailedly, terminal IO is a layer between the bare IO and the data read or written by the program. Some mechanisms, such as the most famous one, `line despline`, do some input and output processing for the program, changing the result of `read` and `write` syscall invoked by the program.

However, these days, terminal as a device is not usually accessed directly by developers and users. Even developers in most cases, just interact with __pseudo terminal__. That is because nowadays, we have more output devices like monitors and keyboards which is removable, not a part of terminal itself.

A more general thing is that, standard IO library provided by C, always the operating system dynamic link library, detects the type of a file, meaning that different type of devices result in different behavior of programs. `printf`, `scanf` and so on behaves differently in the case of a `pipe` or `fifo`, from a `terminal device`. The former causes the IO library to do `full buffered IO`, buffer never gets flushed when encountering a `linefeed` or `EOF`.

```shell

# do what you expect
stty -a > file
stty -a | less # pager works

# not what you expect
stty -a | nvimpager # pager not works

```

In the second case mentioned in the above program, `pseudo terminal` comes to help, because there is no way that we try to change the source code of one of the two program and re-compile them, to change their behaviors when piping.

## Pseudo Terminal

This is a general term, refering to applications making use of the pseudo terminal interface provided by the kernel. These apps always read and write multiple io stream.

For example, telnetd read from the network stream, pipe it to the shell it spawns, and then read back the output from the shell, finally write to the network stream again. 

Pseudo terminal is consist of slave side and master side, which do not refer to a specific process. It is just a interface to the process the app run. The app can read and write to it, like a real terminal.

Pseudo terminal can be nested!!! So when you try using `stty` to change the behavior of your terminal behaviors, a lot of things may affect the result. For example, `stty -echo` __can not__ disable echoing when you are using `fish` shell, but it is OK when you are using `bash`. Looking up the hierachy of program can help you find out which program gives you that pseudo terminal interface. `fish` automatically enable echoing when it starts. But when you spawn `bash` within fish, you are able to map `inrt` to `.`, and returning to `fish`. `fish` shares the same `pts` with `bash` it spawned, so pressing `.` can invoke `intr` in fish now.

## Inspecting

1. `who`, find out current log-in users and the terminal(including pseudo terminal) devices they are using respectively
2. `w`, telling you information about the users currently on the machine, and their processes. You can easily inspect which terminal device corresponds to which program. For example, `tty/2` may attach to `sddm`, if you are using KDE


### Applications List:

1. script
2. expect
3. telnetd
4. logind
5. terminal emulator

### Terminal Emulator

TODO: The architecture illustration in _Advanced Programming in Unix Enviornment here_


### TODO

1. Controlling Terminal
2. Group ID, User ID, real user ID


## References

0. Please refer to man page.
    - For utility: `tty`, `stty`
    - For interface: `pts`, `posix_openpt`, `grantpt`, `unlockpt`, `ptsname`
    - For applications: `xterm`, `sshd`
1. [Linux System Programming Techniques, Jack-Benny Persson](https://www.amazon.com/Linux-System-Programming-Techniques-proficient/dp/1789951283)
2. [Advanced Unix Programming, Marc Rochkind](https://www.amazon.com/Advanced-UNIX-Programming-Marc-Rochkind/dp/0131411543)
3. [Advanced Programming in the UNIX Environment, 3rd Edition 3rd Edition, W. Stevens, Stephen Rago](https://www.amazon.com/Advanced-Programming-UNIX-Environment-3rd/dp/0321637739)
