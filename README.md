[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/-socAj-J)
# datastructs
Implementations of classic data structures in C for CS580U.

[![Grading CI](https://github.com/bucs580u/datastructs-team-alpha/actions/workflows/grading-ci.yml/badge.svg)](https://github.com/bucs580u/datastructs-team-alpha/actions/workflows/grading-ci.yml)

<!-- MarkdownTOC -->

- [Team Members](#team-members)
- [Prerequisites](#prerequisites)
- [Build](#build)
- [Usage](#usage)

<!-- /MarkdownTOC -->

## Team Members

| Team Member | Email | B-Number |
|-------------|-------|----------|
| 1. Atharva Patil|apatil6@binghamton.edu|B01014288|
| 2. Sagar Pise|spise@binghamton.edu|B01039414|
| 3.

## Prerequisites

- [GNU C Library (glibc)](https://www.gnu.org/software/libc/)
- [CUnit](https://cunit.sourceforge.net/)

Note that all prerequisites have already been installed on Remote.

- To install on a Debian-like Linux, run `apt update && apt install libcunit1-dev valgrind`.
- To install on a Fedora-like Linux, run `yum install CUnit-devel valgrind`
- To install on MacOS, install [Homebrew](https://brew.sh/), then run `brew install cunit valgrind`

## Build

- To build the project, run `make all` from the top directory.
- To clean the project, run `make clean` from the top directory.

## Usage

Each subdirectory has a CUnit test contained in its **test.c**.

- To run these checks for the entire project, run `make check memcheck` from the top directory.
- To run the check for one data structure, navigate to its subdirectory and run `make check memcheck`.
