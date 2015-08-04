GDBM sample application
=======================

Simple C application to demonstrate basic GDBM functions (GDBM is simple key/value store). It consits from:
* gdbm_load - loads words database from stdin
* gdbm_query - queries specified word from database created by gdbm_load

Setup
-----
Tested on CentOS 7.1. Install:

	yum install make gcc binutils glibc-devel gdbm-devel valgrind words

Build
-----
Invoke:

	make

Run
---

	make run

After a while you can enter words to search

Valgrind
--------
To verify that there are no memory leaks, use:

	make valgrind


