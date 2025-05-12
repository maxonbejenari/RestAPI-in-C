# REST API IN C USING libmicrohttpd

libmicrohttpd is a light-weight library for http/web server

## Instalation

here is the docs for installing https://www.gnu.org/software/libmicrohttpd/

I use Fedora Workstation 42

```bash
sudo dnf install libmicrohttpd-devel
```

## BUILD AND RUN

```bash
gcc main.c -o api -lmicrohttpd
./api
```