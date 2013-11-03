# ZeroSync Client

Linux, Mac and Windows file sync client

## About zeroclient

The clients primary task is to watch the file system for changes. Each operation system (Linux, Mac and Windows) has there own methods and functions for this. Therefore each OS needs an own watch implementation. But we don’t have to start from scratch here. Open source projects like owncloud already handling this pretty well. One idea could be to fork their client and only use the file system watch part. In case of an updated file the client will inform others about the change. And provide the data once another peer requests it.


## Want to contribute?

Absolutely everyone is welcome :+1: check the wiki for our coding conventions.

If you're not sure how to contribute? Write at mail@zerosync.org and we find something that fits your skill and our needs ;)

## Copying

Free use of this software is granted under the terms of the GNU Lesser General
Public License (LGPL). For details see the `LICENSE` file included with the ZeroSync distribution.

Neue Zeile
Neue 2
Neue Zeile 34
abc