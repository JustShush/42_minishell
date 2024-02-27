<h1>
	<p align="center">42_minishell</p>
	<img align="right" alt="Project in progress" src="https://img.shields.io/badge/-%2095%20%2F%20100-success">
</h1>

<p align="center">
	<b><i>As beautiful as a shell</b></i>
</p>

<p align="center">
  <a href="#-about">About</a>
  •
  <a href="#-resource-links">Resource Links</a>
  •
  <a href="#-prerequisites">Prerequisites</a>
  •
  <a href="#-getting-started">Getting Started</a>
  •
  <a href="#-why-we-got-95">Why we got 95/100</a>
</p>

<br>

## 💡 About

> _Write a shell._

	This project is about creating a simple shell. Yes, your own little bash.
	You will learn a lot about processes and file descriptors.

<br>

## 🔗 Resource Links

- 📜 Project PDF: [PDF](https://github.com/JustShush/42_minishell/blob/main/minishell.pdf)
<br>

## 📦 Prerequisites

- [GCC Compiler](https://gcc.gnu.org/install/)
- [Make](https://gnuwin32.sourceforge.net/packages/make.htm)
- [Git](https://git-scm.com/downloads)

<br>

## 🚀 Getting Started

- Open the terminal and run the following commands

```
git clone git@github.com:JustShush/42_minishell.git
cd 42_minishell
make
./minishell
```
```
git clone git@github.com:JustShush/42_minishell.git ; cd 42_minishell ; make ; ./minishell
```

- To compile, run `make` at the root of the `42_minishell` directory.
- To start the project run the executable file at the root of the `42_minishell` directory. Example:
```Shell
$ ./minishell
```

## ❌ Why we got 95

Basically [execve](https://man7.org/linux/man-pages/man2/execve.2.html) creates a new process when when we changed the exit status in the child it doesn't get updated in the other process so when we tried the command: `env | <invalid_command>` and then `echo $?` it returns `0` instead of `127` for the command not found.

[some tests to check](./tester/tests)
